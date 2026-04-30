#include <sys/mman.h>
#include "object.h"
#include "loader_util.h"
#include "memory.h"
#include "sys_calls.h"
#include "errors.h"

#define PAGE_SIZE 4096

int map_elf_segments(int fd, struct elf_object_s * obj)
{
    Elf64_Ehdr * ehdr = obj->ehdr;
    Elf64_Phdr * phdr = obj->phdr;
    int i = 0;
    int flag_set  = 0;
    
    for(i = 0; i < ehdr->e_phnum; i++)
    {
        if(phdr[i].p_type != PT_LOAD)
            continue;

        uint64_t start_page = align_down(phdr[i].p_vaddr);
        uint64_t end_page = align_up(phdr[i].p_vaddr + phdr[i].p_memsz);
        uint64_t size = end_page - start_page;

        int prot = phdr_to_prot(phdr[i].p_flags) | PROT_WRITE;

        void * addr = __mmap((void *)start_page, size, prot, 0x02 | 0x10, fd, align_down(phdr[i].p_offset));

        if ((int64_t)addr < 0)
        {
            return ERROR_ELF_MAP_FAILED;
        }

        if (!flag_set)
        {
            obj->base = addr;
            obj->ptr_load = (uintptr_t)addr - start_page;
            flag_set = 1;
        }

        if (phdr[i].p_memsz > phdr[i].p_filesz)
        {
            void *bss = (void*)(obj->ptr_load + phdr[i].p_vaddr + phdr[i].p_filesz);
            uint64_t bss_size = phdr[i].p_memsz - phdr[i].p_filesz;
            mem_zero(bss, bss_size);
        }
    }

    return 0;
}