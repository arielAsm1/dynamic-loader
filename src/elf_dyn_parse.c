#include <elf.h>
#include "object.h"
#include "errors.h"

int dyn_parse(struct elf_object_s * obj)
{
    Elf64_Dyn * dyn = obj->dyn;
    if(!dyn)
    {
        return ERROR_DYN_NOT_PRESENT;
    }

    while(dyn->d_tag != DT_NULL)
    {
        switch(dyn->d_tag)
        {
            case DT_STRTAB:
                obj->strtab = (char *)(obj->ptr_load + dyn->d_un.d_ptr);
                break;

            case DT_SYMTAB:
                obj->symtab = (Elf64_Sym *)(obj->ptr_load + dyn->d_un.d_ptr);
                break;

            case DT_RELA:
                obj->rela = (Elf64_Rela *)(obj->ptr_load + dyn->d_un.d_ptr);
                break;

            case DT_RELASZ:
                obj->rela_count = dyn->d_un.d_val / sizeof(Elf64_Rela);
                break;

            case DT_JMPREL:
                obj->jmprel = (Elf64_Rela *)(obj->ptr_load + dyn->d_un.d_ptr);
                break;

            case DT_PLTRELSZ:
                obj->jmprela_count = dyn->d_un.d_val / sizeof(Elf64_Rela);
                break;
        }

        dyn++;
    }

    return 0;
}