#ifndef OBJECT_H
#define OBJECT_H

#include <stddef.h>
#include <stdint.h>
#include <elf.h>

struct elf_object_s
{
    /*identification*/
    char * name;

    /*  load info   */
    char * base;        // mapped base address
    uintptr_t ptr_load; // original load addr (p_vaddr)

    size_t mem_size;    // total mapped memory

    /*  elf structere   */
    Elf64_Phdr * phdr;
    Elf64_Ehdr * ehdr;
    uint16_t phnum;

    Elf64_Dyn * dyn;

    uintptr_t entry;   

    Elf64_Sym * symtab;
    char * strtab;

    Elf64_Rela * rela;
    size_t rela_count;

    Elf64_Rela * jmprel;
    size_t jmprela_count;


    struct elf_object_s * next;
};

#endif