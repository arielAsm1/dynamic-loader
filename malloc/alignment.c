#include "alignment.h"

size_t alignment(size_t x)
{
    size_t remain = x % 8;

    if(remain == 0)
        return x;

    return x + (8 - remain);
}