#include "elf_dyn_get.h"
#include "sym.h"
#include "types.h"
#include "errors.h"     

Elf64_Dyn * dyn_get_ent(Elf64_Dyn * dyn, int64_t tag) 
{
    Elf64_Dyn * d = dyn;

    while(d->d_tag != DT_NULL)
    {
        if (d->d_tag == tag)
        {
          return d;
        }

        d++;
    }

    return NULL;
}

Elf64_Sym * dyn_get_symtab(Elf64_Dyn * dyn, char * base) 
{
    Elf64_Dyn * ent = dyn_get_ent(dyn, DT_SYMTAB);

    if (ent == NULL)
    { 
        return NULL;
    }

    return (Elf64_Sym *)(base + ent->d_un.d_ptr);
}

char * dyn_get_strtab(Elf64_Dyn * dyn, char * base) 
{
    Elf64_Dyn * ent = dyn_get_ent(dyn, DT_STRTAB);

    if (ent == NULL) 
    {
        return NULL;
    }

    return base + ent->d_un.d_ptr;
}

uint64_t dyn_get_sym_ent(Elf64_Dyn * dyn) 
{
    Elf64_Dyn * ent = dyn_get_ent(dyn, DT_SYMENT);
    if (ent == NULL) 
    {
        return 0;
    }

    return ent->d_un.d_val;
}

uint64_t dyn_get_strsz(Elf64_Dyn * dyn) 
{
    Elf64_Dyn * ent = dyn_get_ent(dyn, DT_STRSZ);
    if (ent == NULL) 
    {
        return 0;
    }

    return ent->d_un.d_val;
}

struct elf_hash_table_t * dyn_get_elf_hash(Elf64_Dyn * dyn, char * base)
{
    Elf64_Dyn * ent = dyn_get_ent(dyn, DT_HASH);
    if (ent == NULL) 
    {
        return NULL;
    }

    return (struct elf_hash_table_t *)(base + ent->d_un.d_ptr);
}

struct gnu_hash_table_t * dyn_get_gnu_hash(Elf64_Dyn * dyn, char * base)
{
    Elf64_Dyn * ent = dyn_get_ent(dyn, DT_GNU_HASH);

    if (ent == NULL)
    {
         return NULL;
    }

    return (struct gnu_hash_table_t *)(base + ent->d_un.d_ptr);
}

Elf64_Rela * dyn_get_rela(Elf64_Dyn * dyn, char * base)
{
    Elf64_Dyn * ent = dyn_get_ent(dyn, DT_RELA);
    if (ent == NULL)
    {
         return NULL;
    }

    return (Elf64_Rela *)(base + ent->d_un.d_ptr);
}

Elf64_Rel * dyn_get_rel(Elf64_Dyn * dyn, char * base) 
{
    Elf64_Dyn * ent = dyn_get_ent(dyn, DT_REL);
    if (ent == NULL) 
    {
        return NULL;
    }

    return (Elf64_Rel *)(base + ent->d_un.d_ptr);
}

uint64_t dyn_get_rela_sz(Elf64_Dyn * dyn) 
{
    Elf64_Dyn * ent = dyn_get_ent(dyn, DT_RELASZ);
    if (ent == NULL)
    {
         return 0;
    }

    return ent->d_un.d_val;
}

uint64_t dyn_get_rel_sz(Elf64_Dyn * dyn) 
{
    Elf64_Dyn * ent = dyn_get_ent(dyn, DT_RELSZ);
    if (ent == NULL)
    { 
        return 0;
    }

    return ent->d_un.d_val;
}

uint64_t dyn_get_rela_ent(Elf64_Dyn * dyn) 
{
    Elf64_Dyn * ent = dyn_get_ent(dyn, DT_RELAENT);
    if (ent == NULL)
    {
        return 0;
    } 

    return ent->d_un.d_val;
}

uint64_t dyn_get_rel_ent(Elf64_Dyn * dyn) 
{
    Elf64_Dyn * ent = dyn_get_ent(dyn, DT_RELENT);
    if (ent == NULL)
    {
         return 0;
    }

    return ent->d_un.d_val;
}

void * dyn_get_pltgot(Elf64_Dyn * dyn, char * base) 
{
    Elf64_Dyn * ent = dyn_get_ent(dyn, DT_PLTGOT);
    if(ent == NULL)
    {
        return NULL;
    }

    return (void *)(base + ent->d_un.d_ptr);
}

Elf64_Rela * dyn_get_jmprel(Elf64_Dyn * dyn, char * base)
{
    Elf64_Dyn * ent = dyn_get_ent(dyn, DT_JMPREL);
    if(ent == NULL)
    {
         return NULL;
    }

    return (Elf64_Rela *)(base + ent->d_un.d_ptr);
}

uint64_t dyn_get_pltrelsz(Elf64_Dyn * dyn)
{
    Elf64_Dyn * ent = dyn_get_ent(dyn, DT_PLTRELSZ);
    if (ent == NULL) 
    {
        return 0;
    }

    return ent->d_un.d_val;
}

uint64_t dyn_get_pltrel(Elf64_Dyn * dyn) 
{
    Elf64_Dyn * ent = dyn_get_ent(dyn, DT_PLTREL);
    if (ent == NULL)
    {
        return 0;
    }

    return ent->d_un.d_val;
}

void * dyn_get_init(Elf64_Dyn * dyn, char * base) 
{
    Elf64_Dyn * ent = dyn_get_ent(dyn, DT_INIT);
    if (ent == NULL) 
    {
        return NULL;
    }

    return (void *)(base + ent->d_un.d_ptr);
}

void * dyn_get_fini(Elf64_Dyn * dyn, char * base) 
{
    Elf64_Dyn * ent = dyn_get_ent(dyn, DT_FINI);
    if (ent == NULL) 
    {
        return NULL;
    }

    return (void *)(base + ent->d_un.d_ptr);
}

int dyn_has_needed(Elf64_Dyn *dyn) 
{
    Elf64_Dyn * d = dyn;

    while(d->d_tag != DT_NULL)
    {
        if (d->d_tag == DT_NEEDED)
        {
            return 1;
        }

        d++;
    }

    return 0;
}
