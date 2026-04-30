#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stdint.h>
#include <stddef.h>

struct chunk_s 
{
    struct chunk_s * next;
    struct chunk_s * prev;
    size_t size;
};

void * malloc(size_t size);
void free(void * ptr);

#endif