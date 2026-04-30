#include <stdint.h>
#include <stddef.h>
#include "sys_calls.h"
#include "object.h"
#include "object_load.h"
#include "linking.h"
#include "loader_deps.h"
#include "elf_dyn_parse.h"
#include "relocations.h"
#include "utilself.h"
#include "allocator.h"

char ** g_envp = 0;
#define BUF_SIZE 4096

static char buf[BUF_SIZE];

/*int main(int argc, char ** argv)
{
    if(argc < 2)
    {
        print("invalid number of parameters\n");
        return 1;
    }

    int fd = __open(argv[1], 0);
    if(fd < 0)
    {
        print("open failed\n");
        return 1;
    }

    if(__read(fd, buf, sizeof(Elf64_Ehdr)) != sizeof(Elf64_Ehdr))
    {
        print("reading failed\n");
        return 1;
    }

    Elf64_Ehdr * ehdr = (Elf64_Ehdr *)buf;

    int checker = elf_header_check(ehdr);

    if(checker)
    {
        print("ELF invalid\n");
        return 1;
    }

    print("ELF header ok!\n");

    __lseek(fd, ehdr->e_phnum, 0);

    size_t phsize = ehdr->e_phnum * sizeof(Elf64_Phdr);

    if(__read(fd, buf, phsize) != phsize)
    {
        print("reading failed");
        return 1;
    }

    Elf64_Phdr * phdr = (Elf64_Phdr *)buf;

    Elf64_Dyn * dyn = phdr_get_dyn(phdr, ehdr->e_phnum, 0);

    if(dyn)
    {
        print("dynamic segment not found\n");
    }

    print("PASSED!\n");

    return 0;
}*/

/*int main(int argc, char ** argv)
{
    for (int i = 0; i < argc; i++)
    {
        __write(1, argv[i], my_strlen(argv[i]));
        __write(1, "\n", 1);
    }

    return argc;
}*/


int main(int argc, char ** argv, char ** envp)
{
    g_envp = envp;
    
    if(argc < 2)
    {
        return 1;
    }

    int fd = __open(argv[1], 0);
    if(fd < 0)
    {
        print("open failed\n");
        return 1;
    }

    struct elf_object_s * obj = (struct elf_object_s *)malloc(sizeof(struct elf_object_s));

    if(!obj)
    {
        print("malloc failed\n");
        return 1;
    }

    obj->name = argv[1];
    obj->next = 0;

    print("loading object...\n");

    if(object_load(obj, fd) < 0)
    {
        print("object load failed\n");
        return 1;
    }

    object_add(obj);

    print("loading dependencies...\n");
    int hold = load_dependencies(obj);

    if(hold < 0)
    {
        print("1\n");
        return 1;
    }

    if(hold == -2)
    {
        print("2\n");
        return 1;
    }

    if(hold == -3)
    {
        print("3\n");
        return 1;
    }

    if(hold == -4)
    {
        print("4\n");
        return 1;
    }

    print("parsing dynamic section...\n");

    if(dyn_parse(obj) < 0)
    {
        print("dyn parse failed\n");
        return 1;
    }

    print("relocationg objects...\n");

    struct elf_object_s * current_to_relocate = object_first();
    while (current_to_relocate != 0)
    {
        if(relocate_object(current_to_relocate, object_first()) < 0)
        {
            print("relocation failed\n");
            return 1;
        }
        current_to_relocate = current_to_relocate->next;
    }

    print("PASSED!\n");

    uintptr_t entry = obj->ptr_load + obj->ehdr->e_entry;

    typedef void (*entry_point)(int, char **);

    entry_point start_program = (entry_point)entry;


    int ISHAMAN = 11231231;
    char * str1 = "amir shamen meod";
    char * str2 = "he weighs: ";
    char * str3 = "ton";

    __printf("amir is...\n%s\n%s\n%d %s\n", str1, str2, ISHAMAN, str3);

    start_program(argc, argv);

    return 0;
}