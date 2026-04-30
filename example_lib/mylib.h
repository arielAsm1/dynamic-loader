#ifndef MYLIB_H
#define MYLIB_H

#include <stdint.h>
#include <stddef.h>
#include <sys/syscall.h>

int add(int a, int b);
int sub(int a, int b);
int mul(int a, int b);
int divide(int a, int b);
int power(int a, int b);


int64_t my_syscall(
    int64_t syscall_num,
    int64_t arg1,
    int64_t arg2,
    int64_t arg3,
    int64_t arg4,
    int64_t arg5,
    int64_t arg6
);

size_t __write(int fd, const void *buf, size_t count);
void print(const char * s);

size_t my_strlen(const char * s);

#endif
