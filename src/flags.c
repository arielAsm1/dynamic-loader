#include "flags.h"

#define USED_FLAG 1
#define PREV_USED_FLAG 2

void set_used_flag(struct chunk_s * c)
{
    c->size += USED_FLAG;
}

void set_prev_used_flag(struct chunk_s * c)
{
    c->size += PREV_USED_FLAG;
}