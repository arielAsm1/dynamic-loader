#include <asm/unistd.h>
#include "mmemory.h"
#include "sys_calls.h"

struct chunk_s * top_chunk = 0;

int request_more_memory()
{
    void * current = __brk(0);
    void * new = (char *)current + 4096;

    if(__brk(new) != new)
    {
        return 0;
    }

    top_chunk = (struct chunk_s *)current;
    top_chunk->size = 4096 - sizeof(struct chunk_s);

    return 1;
}