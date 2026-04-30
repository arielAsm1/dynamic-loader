#include <asm/unistd.h>
#include "sys_calls.h"

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
        "mov %1, %%rax\n"   // syscall number = rax
        "mov %2, %%rdi\n"   // arg1 = rdi
        "mov %3, %%rsi\n"   // arg2 = rsi
        "mov %4, %%rdx\n"   // arg3 = rdx
        "mov %5, %%r10\n"   // arg4 = r10
        "mov %6, %%r8\n"    // arg5 = r8
        "mov %7, %%r9\n"    // arg6 = r9
        "syscall\n"
        "mov %%rax, %0\n"   // return value = ret
        : "=g"(ret)
        : "g"(syscall_num), "g"(arg1), "g"(arg2), "g"(arg3), "g"(arg4), "g"(arg5), "g"(arg6)
        : "rax", "rdi", "rsi", "rdx", "r10", "r8", "r9", "rcx", "memory"
    );

    return ret;
}

void * __mmap(void * addr, size_t length, int prot, int flags, int fd, off_t offset)
{
    return (void *)my_syscall(__NR_mmap, (int64_t)addr, length, prot, flags, fd, offset);
}

ssize_t __write(int fd, const void *buf, size_t count)
{
    return my_syscall(__NR_write, fd, (int64_t)buf, count, 0, 0, 0);
}

int __open(const char *path, int flags)
{
    return my_syscall(__NR_open, (int64_t)path, flags, 0, 0, 0, 0);
}

ssize_t __read(int fd, void *buf, size_t count)
{
    return my_syscall(__NR_read, fd, (int64_t)buf, count, 0, 0, 0);
}

off_t __lseek(int fd, off_t offset, int whence)
{
    return my_syscall(__NR_lseek, fd, offset, whence, 0, 0, 0);
}

void * __brk(void * addr)
{
    return (void *)my_syscall(__NR_brk, (int64_t)addr, 0, 0, 0, 0, 0);
}

