#include <elf.h>
#include <stdint.h>
#include "elf_dyn_get.h"
#include "symbol_lookup.h"
#include "utilself.h"

void * lookup_in_object(const char * name, struct elf_object_s * obj)
{
    if(!obj->symtab || !obj->strtab)
    {
        return 0;
    }

    Elf64_Sym * sym = obj->symtab;
    char * strtab = obj->strtab;

    size_t num_symbols = 0;
    struct elf_hash_table_t * hash = dyn_get_elf_hash(obj->dyn, (char *)obj->ptr_load);
    if (hash)
    {
        num_symbols = hash->num_chains;
    }
    else if (strtab > (char *)sym)
    {
        num_symbols = ((uintptr_t)strtab - (uintptr_t)sym) / sizeof(Elf64_Sym);
    }

    if (num_symbols == 0)
    {
        return 0;
    }

    for (size_t i = 0; i < num_symbols; i++)
    {
        if(sym[i].st_name == 0)
        {
            continue;
        }

        const char * symname = strtab + sym[i].st_name;

        if(my_strcmp(name, symname) == 0)
        {
            if(sym[i].st_shndx == SHN_UNDEF)
            {
                continue;
            }

            return (void *)(obj->ptr_load + sym[i].st_value);
        }
    }

    return 0;
}

void * symbol_lookup(const char * name, struct elf_object_s * objects)
{
    struct elf_object_s * current = objects;

    while(current)
    {
        void * addr = lookup_in_object(name, current);

        if(addr)
        {
            return addr;
        }

        current = current->next;
    }

    return 0;
}