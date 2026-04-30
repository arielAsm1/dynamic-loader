#include <elf.h>
#include "symbol_lookup.h"
#include "relocations.h"
#include "errors.h"

int apply_relocation(struct elf_object_s * obj, Elf64_Rela * rela, struct elf_object_s * objects)
{
    uint32_t type = ELF64_R_TYPE(rela->r_info);
    uint32_t sym_index = ELF64_R_SYM(rela->r_info);

    uint8_t * where = (uint8_t *)(obj->ptr_load + rela->r_offset);

    Elf64_Sym * sym = &obj->symtab[sym_index];
    void * sym_addr = 0;

    if(sym->st_name != 0)
    {
        const char * name = obj->strtab + sym->st_name;
        sym_addr = symbol_lookup(name, objects);

        if(!sym_addr)
        {
            return ERROR_DYN_UNRESOLVED_SYMBOL;
        }

        switch(type)
        {
           case R_X86_64_GLOB_DAT:
           case R_X86_64_JUMP_SLOT:
           {
               *(uint64_t *)where = (uint64_t)sym_addr + rela->r_addend;
               break;
           }
           case R_X86_64_RELATIVE:
           {
               *(uint64_t *)where = (uint64_t)(obj->ptr_load + rela->r_addend);
               break;
           }
           default:
                return ERROR_DYN_UNSUPPORTED_RELOC;
        }
    }
    return 0;
}

int relocate_object(struct elf_object_s * obj, struct elf_object_s * objects)
{
    size_t i = 0;
    for(i = 0; i < obj->rela_count; i++)
    {
        int err = apply_relocation(obj, &obj->rela[i], objects);
        if(err != 0)
        {
            return err;
        }
    }

    for(i = 0; i < obj->jmprela_count; i++)
    {
        int err = apply_relocation(obj, &obj->jmprel[i], objects);
        if(err != 0)
        {
            return err;
        }
    }

    return 0;
}