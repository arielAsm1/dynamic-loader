#include <elf.h>
#include <fcntl.h>
#include "loader_deps.h"
#include "memory.h"
#include "sys_calls.h"
#include "linking.h"
#include "elf_dyn_get.h"
#include "allocator.h"
#include "utilself.h"
#include "object_load.h"
#include "elf_dyn_parse.h"
#include "relocations.h"
#include "errors.h"

extern char ** g_envp;

char * get_env(const char * name) 
{
    if (!g_envp)
    {
        return 0;
    }
    
    size_t len = my_strlen(name);
    int i = 0;
    
    print("\nsearching for environment variable: ");
    print(name);
    print("\n");

    while (g_envp[i] != 0) 
    {
        if ((my_strncmp(g_envp[i], name, len) == 0) && (g_envp[i][len] == '=')) 
        {
            print("found: ");
            print(g_envp[i]);
            print("\n");
            
            print("path: ");
            print(g_envp[i] + len + 1);
            print("\n\n");
            
            return g_envp[i] + len + 1;
        }
        i++;
    }
    return 0;
}

int open_library(const char * libname) 
{
    int i = 0;
    int has_slash = 0;

    while(libname[i]) 
    {
        if (libname[i] == '/')
        {
            has_slash = 1;
        }
        i++;
    }

    if (has_slash)
    {
        return __open(libname, O_RDONLY);
    }

    char * ld_lib_path = get_env("LD_LIBRARY_PATH");
    
    if (ld_lib_path) 
    {
        char filepath[200];
        const char * p = ld_lib_path;
        
        while (*p) 
        {
            const char * end = p;
            while (*end && *end != ':')
            {
                end++;
            }

            size_t dir_len = end - p;
            
            if ((dir_len > 0) && (dir_len + my_strlen(libname) + 2 < 512)) 
            {
                char * dest = filepath;
                size_t j = 0;
            
                for(j = 0; j < dir_len; j++)
                {
                    *dest++ = p[j];
                }
                *dest++ = '/';
                
                const char * src = libname;
                while(*src)
                {
                    *dest++ = *src++;
                }
                *dest = '\0';

                int fd = __open(filepath, O_RDONLY);
                if (fd >= 0)
                {
                    return fd;
                }
            }

            p = end;
            if (*p == ':')
            {
                p++;
            }
        }
    }
    return __open(libname, O_RDONLY);
}

int load_dependencies(struct elf_object_s * obj)
{
    Elf64_Dyn * dyn = obj->dyn;
    if(!dyn)
    {
        return 0;
    }

    char * strtab = dyn_get_strtab(dyn, (char *)obj->ptr_load);
    if(!strtab)
    {
        return ERROR_DYN_NO_STRTAB;
    }

    while(dyn->d_tag != DT_NULL)
    {
        if(dyn->d_tag == DT_NEEDED)
        {
            char * libname = strtab + dyn->d_un.d_val;
            if(object_find(libname))
            {
                dyn++;
                continue;
            }

            int fd = open_library(libname); 

            if(fd < 0)
            {
                print("failed to find lib: ");
                print(libname);
                print("\n");
                return ERROR_READING_ELF_FILE;
            }

            struct elf_object_s * new_obj = (struct elf_object_s *)malloc(sizeof(struct elf_object_s));
            if(!new_obj)
            {
                return ERROR_DYN_NOT_ENOGUH_SPACE;
            }

            size_t len = my_strlen(libname) + 1;
            new_obj->name = (char *)malloc(len);
            my_memcpy(new_obj->name, libname, len);

            int load_err = object_load(new_obj, fd);
            if(load_err != 0)
            {
                print("failed to load segments: ");
                print(new_obj->name);
                print("\n");
                return load_err;
            }

            int parse_err = dyn_parse(new_obj);
            if(parse_err != 0)
            {
                print("failed to parse dynamic: ");
                print(libname);
                print("\n");
                return parse_err;
            }

            object_add(new_obj);

            int deps_err = load_dependencies(new_obj);
            if(deps_err != 0)
            {
                return deps_err;
            }
        }
        
        dyn++;
    }

    return 0;
}