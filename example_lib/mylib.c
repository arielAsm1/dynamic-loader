#include "mylib.h"


int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }
int divide(int a, int b) { return b ? (a / b) : 0; }
int power(int a, int b) 
{
    for(int i = 0; i < b; i++)
    {
        a *= a;
    }

    return a;
}


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
    int64_t ret;
    register int64_t r10 asm("r10") = arg4;
    register int64_t r8  asm("r8")  = arg5;
    register int64_t r9  asm("r9")  = arg6;
    
    asm volatile(
        "syscall"
        : "=a"(ret)
        : "a"(syscall_num), "D"(arg1), "S"(arg2), "d"(arg3), "r"(r10), "r"(r8), "r"(r9)
        : "rcx", "r11", "memory"
    );

    return ret;
}

size_t __write(int fd, const void *buf, size_t count)
{
    return my_syscall(__NR_write, fd, (int64_t)buf, count, 0, 0, 0);
}

void print(const char * s)
{
    __write(1, s, my_strlen(s));
}

size_t my_strlen(const char * s)
{
    size_t i = 0;
    while(s[i])
    {
        i++;
    }

    return i;
}