#include "allocator.h"
#include "mmemory.h"
#include "alignment.h"
#include "flags.h"
#include "free_list.h"

void * malloc(size_t size)
{
    size = alignment(size);
    struct chunk_s * c = find_fit(size);

    if(!c)
    {
        if(!top_chunk || top_chunk->size < size)
        {
            if(!request_more_memory())
            {
                return NULL;
            }
            insert_to_bin(top_chunk);

            c = top_chunk;
        }
        else 
        {
             c = top_chunk;
        }
    }

    size_t required_total = size + sizeof(struct chunk_s);

    if(c->size >= size + sizeof(struct chunk_s) + 8) 
    {
        struct chunk_s * remainder = (struct chunk_s *)( (char*)c + sizeof(struct chunk_s) + size );
        remainder->size = c->size - size - sizeof(struct chunk_s);
    
        c->size = size;
        
        remove_from_bin(c);
        
        insert_to_bin(remainder);
        
        if (c == top_chunk) 
        {
            top_chunk = remainder;
        }
    }
    else
    {
        remove_from_bin(c);
    }

    set_used_flag(c);

    return (void *)(c + 1);
}

void free(void * ptr)
{
    if(!ptr) return;

    struct chunk_s * c = ((struct chunk_s *)ptr) - 1;

    c->size &= ~1;

    insert_to_bin(c);
}