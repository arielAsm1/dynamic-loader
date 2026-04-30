#include "mmemory.h"
#include <asm/unistd.h>

struct chunk_s * top_chunk = 0;

int64_t my_syscall(
    int64_t syscall_num,
    int64_t arg1,
    int64_t arg2,
    int64_t arg3,
    int64_t arg4,
    int64_t arg5,
    int64_t arg6
)
{
    int64_t ret = 0;

    asm volatile(
        "mov %1, %%rax\n"
        "mov %2, %%rdi\n"
        "mov %3, %%rsi\n"
        "mov %4, %%rdx\n"
        "mov %5, %%r10\n"
        "mov %6, %%r8\n"
        "mov %7, %%r9\n"
        "syscall\n"
        "mov %%rax, %0\n"
        : "=g"(ret)
        : "g"(syscall_num), "g"(arg1), "g"(arg2), "g"(arg3), "g"(arg4), "g"(arg5), "g"(arg6)
        : "rax", "rdi", "rsi", "rdx", "r10", "r8", "r9", "rcx", "memory"
    );

    return ret;
}

void * __brk(void * addr)
{
    return (void *)my_syscall(__NR_brk, (int64_t)addr, 0, 0, 0, 0, 0);
}

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