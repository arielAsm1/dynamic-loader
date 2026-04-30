#ifndef MMEMORY_H
#define MMEMORY_H

#include "allocator.h"

extern struct chunk_s * top_chunk; 
int64_t my_syscall(
    int64_t syscall_num,
    int64_t arg1,
    int64_t arg2,
    int64_t arg3,
    int64_t arg4,
    int64_t arg5,
    int64_t arg6
);
int request_more_memory();

#endif