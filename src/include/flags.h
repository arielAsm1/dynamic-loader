#ifndef FLAGS_H
#define FLAGS_H

#include "allocator.h"

void set_used_flag(struct chunk_s * c);
void set_prev_used_flag(struct chunk_s * c);

#endif