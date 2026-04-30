#include "mylib.h"


void my_exit(int code) 
{
    asm volatile (
        "syscall"
        : 
        : "a"(60), "D"(code)
        : "rcx", "r11", "memory"
    );
}

int main(int argc, char **argv)
{
    int a = 10, b = 5;

    int num1 = add(a, b);
    int num2 = sub(a, b);
    int num3 = mul(a, b);
    int num4 = divide(a, b);
    int num5 = power(a, b);

    print("AMIR SHAMEN MEOD\n");

    return 45;
}

void _start(int argc, char **argv)
{
    int ret = main(argc, argv);
    
    my_exit(ret);
}