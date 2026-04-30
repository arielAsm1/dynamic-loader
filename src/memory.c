#include "memory.h"

void mem_zero(void *ptr, uint64_t size)
{
    unsigned char *p = ptr;
    uint64_t i = 0;
    
    for (i = 0; i < size; i++)
    {
        p[i] = 0;
    }

}