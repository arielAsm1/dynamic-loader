#include <sys/mman.h>
#include "loader_util.h"

#define PAGE_SIZE 4096

int phdr_to_prot(int32_t flags)
{
    int prot = 0;

    if(flags & PF_R) prot |= PROT_READ;
    if(flags & PF_W) prot |= PROT_WRITE;
    if(flags & PF_X) prot |= PROT_EXEC;

    return prot;
}

uint64_t align_down(uint64_t v)
{
    return v & ~(PAGE_SIZE -1);
}

uint64_t align_up(uint64_t v)
{
    return (v + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1);
}

    
