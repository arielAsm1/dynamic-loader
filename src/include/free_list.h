#ifndef FREE_LIST_H
#define FREE_LIST_H

#include "allocator.h"

void insert_to_bin(struct chunk_s * c);
void remove_from_bin(struct chunk_s * c);
struct chunk_s * find_fit(size_t size);

#endif