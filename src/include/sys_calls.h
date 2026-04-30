    #ifndef SYS_CALLS_H
    #define SYS_CALLS_H
    
    #include <stdint.h>
    #include <elf.h>
    #include <stddef.h> 
    #include <sys/types.h>
    #include "utilself.h"

int64_t my_syscall(
    int64_t syscall_num,   // sys call number
    int64_t arg1,          // rdi
    int64_t arg2,          // rsi
    int64_t arg3,          // rdx
    int64_t arg4,          // r10
    int64_t arg5,          // r8
    int64_t arg6           // r9
);

void * __mmap(void * addr, size_t length, int prot, int flags, int fd, off_t offset);
ssize_t __write(int fd, const void *buf, size_t count);
int __open(const char *path, int flags);
ssize_t __read(int fd, void *buf, size_t count);
off_t __lseek(int fd, off_t offset, int whence);


#endif