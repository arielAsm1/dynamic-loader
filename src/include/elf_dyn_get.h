    #ifndef ELF_DYN_GET_H
    #define ELF_DYN_GET_H

    #include <stdint.h>
    #include "utilself.h"
    #include <elf.h>
    #include "sym.h"

    Elf64_Dyn * dyn_get_ent(Elf64_Dyn * dyn, int64_t tag);
    Elf64_Sym * dyn_get_symtab(Elf64_Dyn * dyn, char * base);
    char * dyn_get_strtab(Elf64_Dyn * dyn, char * base);
    uint64_t dyn_get_sym_ent(Elf64_Dyn * dyn);
    uint64_t dyn_get_strsz(Elf64_Dyn * dyn);
    struct elf_hash_table_t * dyn_get_elf_hash(Elf64_Dyn * dyn, char * base);
    struct gnu_hash_table_t * dyn_get_gnu_hash(Elf64_Dyn * dyn, char * base);
    Elf64_Rela * dyn_get_rela(Elf64_Dyn * dyn, char * base);
    Elf64_Rel * dyn_get_rel(Elf64_Dyn * dyn, char * base);
    uint64_t dyn_get_rela_sz(Elf64_Dyn * dyn);
    uint64_t dyn_get_rel_sz(Elf64_Dyn * dyn);
    uint64_t dyn_get_rela_ent(Elf64_Dyn * dyn);
    uint64_t dyn_get_rel_ent(Elf64_Dyn * dyn);
    void * dyn_get_pltgot(Elf64_Dyn * dyn, char * base);
    Elf64_Rela * dyn_get_jmprel(Elf64_Dyn * dyn, char * base);
    uint64_t dyn_get_pltrelsz(Elf64_Dyn * dyn);
    uint64_t dyn_get_pltrel(Elf64_Dyn * dyn);
    void * dyn_get_init(Elf64_Dyn * dyn, char * base);
    void * dyn_get_fini(Elf64_Dyn * dyn, char * base);
    int dyn_has_needed(Elf64_Dyn *dyn);

    #endif
