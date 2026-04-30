#include "free_list.h"

static struct chunk_s * free_list_head = 0;

#define SIZE_MASK (~0x7)

void insert_to_bin(struct chunk_s * c)
{
    c->next = free_list_head;
    c->prev = 0;

    if(free_list_head)
    {
        free_list_head->prev = c;
    }

    free_list_head = c;
}

void remove_from_bin(struct chunk_s * c)
{
    if(c->prev)
    {
        c->prev->next = c->next;
    }
    else
    {
        free_list_head = c->next;
    }

    if(c->next)
    {
        c->next->prev = c->prev;
    }
}

struct chunk_s * find_fit(size_t size)
{
    struct chunk_s * current = free_list_head;

    while(current)
    {
        if((current->size & SIZE_MASK) >= size)
        {
            return current;
        }

        current = current->next;
    }

    return 0;
}