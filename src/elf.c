#include <elf.h>
#include "elf.h"
#include "sym.h"
#include "types.h"
#include "errors.h"

int32_t elf_header_check(Elf64_Ehdr * header)
{   
    if(header == NULL)
    {
        return ERROR_ELF_NULL_HEADER;
    }

    if (header->e_ident[EI_MAG0] != ELFMAG0 ||
        header->e_ident[EI_MAG1] != ELFMAG1 ||
        header->e_ident[EI_MAG2] != ELFMAG2 ||
        header->e_ident[EI_MAG3] != ELFMAG3) 
    {
        return ERROR_ELF_BAD_MAGIC;
    }

    if(header->e_ident[EI_CLASS] != ELFCLASS64)
    {
        return ERROR_ELF_BAD_CLASS;
    }
    
    if (header->e_ident[EI_DATA] != ELFDATA2LSB)
    {
        return ERROR_ELF_BAD_ENDIAN;
    }

    if (header->e_ident[EI_VERSION] != EV_CURRENT)
        return ERROR_ELF_BAD_VERSION;

    if (header->e_ident[EI_OSABI] != ELFOSABI_SYSV &&
        header->e_ident[EI_OSABI] != ELFOSABI_LINUX)
    {
        return ERROR_ELF_BAD_OSABI;
    }

    if (header->e_ident[EI_ABIVERSION] != 0)
    {
        return ERROR_ELF_BAD_ABI_VERSION;
    }

    if (header->e_type != ET_EXEC && header->e_type != ET_DYN)
    {
        return ERROR_ELF_BAD_TYPE;
    }

    if (header->e_machine != EM_X86_64)
    {
        return ERROR_ELF_BAD_MACHINE;
    }

    if (header->e_version != EV_CURRENT)
    {
        return ERROR_ELF_BAD_VERSION;
    }

    if (header->e_ehsize != sizeof(Elf64_Ehdr))
    {
        return ERROR_ELF_BAD_EHSIZE;
    }

    return 0;
}


Elf64_Phdr * phdr_get_ent(Elf64_Phdr * phdr, size_t size, uint32_t type) 
{
    uint32_t i = 0;

    for (i = 0; i < size; i++)
    {
        if (phdr[i].p_type == type) 
        {
            return &phdr[i];
        }
    }

    return NULL; // didnt find the type of header that we wanted (the elf doesnt contain that segment) 
}

Elf64_Dyn * phdr_get_dyn(Elf64_Phdr * phdr, size_t phdrs, char * base) 
{
    Elf64_Phdr * ent = phdr_get_ent(phdr, phdrs, PT_DYNAMIC);

    if (ent == NULL) 
    {
        return NULL; // return null if elf is static
    }

    return (Elf64_Dyn *)(base + ent->p_vaddr);
}

int32_t verfiy_dynamic(Elf64_Phdr * phdr, size_t size, char * base)
{
    if(phdr == NULL)
    {
        return ERROR_ELF_NO_PROGRAM_HEADERS;
    }

    Elf64_Dyn * dynamic = phdr_get_dyn(phdr, size, base);

    if(dynamic == NULL)
    {
        return ERROR_DYN_NOT_PRESENT;
    }

    return dyn_verify_dynamic(dynamic, base);
}


int32_t dyn_verify_dynamic(Elf64_Dyn * dyn, char * base)
{
    if (dyn == NULL)
    {
        return ERROR_DYN_NOT_PRESENT;
    }

    if (dyn_get_symtab(dyn, base) == NULL)
    {
        return ERROR_DYN_NO_SYMTAB;
    }

    if (dyn_get_strtab(dyn, base) == NULL)
    {
        return ERROR_DYN_NO_STRTAB;
    }

    if (dyn_get_sym_ent(dyn) == 0)
    {
        return ERROR_DYN_NO_SYMENT;
    }

    if (dyn_get_strsz(dyn) == 0)
    {
        return ERROR_DYN_NO_STRSZ;
    }

    if (dyn_get_elf_hash(dyn, base) == NULL &&
        dyn_get_gnu_hash(dyn, base) == NULL)
    {
        return ERROR_DYN_NO_HASH;
    }

    if (dyn_get_rela(dyn, base) == NULL &&
        dyn_get_rel(dyn, base) == NULL)
    {
        return ERROR_DYN_NO_RELOCATIONS;
    }

    if (dyn_get_rela_sz(dyn) == 0 &&
        dyn_get_rel_sz(dyn) == 0)
    {
        return ERROR_DYN_NO_RELOC_SIZE;
    }

    if (dyn_get_rela_ent(dyn) == 0 &&
        dyn_get_rel_ent(dyn) == 0)
    {
        return ERROR_DYN_NO_RELOC_ENTSIZE;
    }

    if (dyn_get_pltgot(dyn, base) == NULL)
    {
        return ERROR_DYN_NO_PLTGOT;
    }

    if (dyn_get_jmprel(dyn, base) == NULL)
    {
        return ERROR_DYN_NO_JMPREL;
    }

    if (dyn_get_pltrelsz(dyn) == 0)
    {
        return ERROR_DYN_NO_PLTRELSZ;
    }

    if (dyn_get_pltrel(dyn) == 0)
    {
        return ERROR_DYN_NO_PLTREL_TYPE;
    }

    if (dyn_get_init(dyn, base) == NULL)
    {
        return ERROR_DYN_NO_INIT;
    }

    if (dyn_get_fini(dyn, base) == NULL)
    {
        return ERROR_DYN_NO_FINI;
    }

    if (!dyn_has_needed(dyn))
    {
        return ERROR_DYN_NO_NEEDED;
    }

    return 0; /* dynamic ELF verified */
}

