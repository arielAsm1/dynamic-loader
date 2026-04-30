#include <elf.h>
#include <stdint.h>
#include <sys/mman.h>

#include "object_load.h"
#include "object.h"
#include "allocator.h"
#include "sys_calls.h"
#include "loader.h"
#include "loader_util.h"
#include "errors.h"

#define PAGE_SIZE 4096

int object_load(struct elf_object_s * obj, int fd)
{
    Elf64_Ehdr * ehdr = (Elf64_Ehdr *)malloc(sizeof(Elf64_Ehdr));
    if(!ehdr)
    {
        return ERROR_DYN_NOT_ENOGUH_SPACE;
    }

    if(__read(fd, ehdr, sizeof(Elf64_Ehdr)) != sizeof(Elf64_Ehdr))
    {
        return ERROR_READING_ELF_FILE;
    }

    obj->ehdr = ehdr;

    size_t phdr_size = ehdr->e_phnum * sizeof(Elf64_Phdr);
    Elf64_Phdr * phdr = (Elf64_Phdr *)malloc(phdr_size);
    if(!phdr)
    {
        return ERROR_DYN_NOT_ENOGUH_SPACE;
    }

    if(__lseek(fd, ehdr->e_phoff, 0) < 0)
    {
        return ERROR_READING_ELF_FILE;
    }

    if(__read(fd, phdr, phdr_size) != phdr_size)
    {
        return ERROR_READING_ELF_FILE;
    }

    obj->phdr = phdr;

    uintptr_t min_vaddr = (uintptr_t)-1;
    uintptr_t max_vaddr = 0;
    int i = 0;

    for(i = 0;i < ehdr->e_phnum; i++)
    {
        if(phdr[i].p_type != PT_LOAD)
        {
            continue;
        }

        if(phdr[i].p_vaddr < min_vaddr)
        {
            min_vaddr = phdr[i].p_vaddr;
        }

        uintptr_t end = phdr[i].p_memsz + phdr[i].p_vaddr;
        if(end > max_vaddr)
        {
            max_vaddr = end;
        }
    }

    min_vaddr = (uintptr_t)align_down(min_vaddr);
    max_vaddr = (uintptr_t)align_up(max_vaddr);
    size_t total_size = max_vaddr - min_vaddr;

    void * mapping = __mmap(0, total_size, PROT_WRITE | PROT_EXEC | PROT_READ, MAP_PRIVATE | MAP_ANON, -1, 0);
    if((intptr_t)mapping < 0)
    {
        return ERROR_ELF_MAP_FAILED;
    }

    obj->base = (char*)mapping;
    obj->ptr_load = (uintptr_t)mapping - min_vaddr;

    for(i = 0; i< ehdr->e_phnum; i++)
    {
        Elf64_Phdr * ph = &phdr[i];
        if(ph->p_type != PT_LOAD)
        {
            continue;
        }

        void * seg_addr = (void *)(obj->ptr_load + ph->p_vaddr);

        if(__lseek(fd, ph->p_offset, 0) < 0)
        {
            return ERROR_READING_ELF_FILE;
        }

        if(__read(fd, seg_addr, ph->p_filesz) != ph->p_filesz)
        {
            return ERROR_READING_ELF_FILE;
        }
    }

    obj->dyn = 0;
    for(i = 0; i < ehdr->e_phnum; i++)
    {
        if(phdr[i].p_type == PT_DYNAMIC)
        {
            obj->dyn = (Elf64_Dyn *)(obj->ptr_load + phdr[i].p_vaddr);
            break;
        }
    }

    return 0;
}