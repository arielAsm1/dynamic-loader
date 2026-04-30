#include <stdarg.h> // כאן אנחנו מייבאים את המאקרואים של הקומפיילר
#include "utilself.h"
#include "sys_calls.h"

size_t my_strlen(const char * s)
{
    size_t i = 0;
    while(s[i])
    {
        i++;
    }

    return i;
}

void my_memcpy(char * dest, const char * src, size_t n)
{
    size_t i = 0;

    for(i = 0;i < n; i++)
    {
        dest[i] = src[i];
    }
}

int my_strcmp(const char *str1, const char *str2)
{
    while (*str1 && (*str1 == *str2)) 
    {
        str1++;
        str2++;
    }
    return *(const unsigned char*)str1 - *(const unsigned char*)str2;
}

int my_strncmp(const char *str1, const char *str2, size_t n)
{
    while (n && *str1 && (*str1 == *str2)) 
    {
        str1++;
        str2++;
        n--;
    }

    if (n == 0)
    { 
        return 0;
    }

    return *(const unsigned char *)str1 - *(const unsigned char *)str2;
}

void print(const char * s)
{
    __write(1, s, my_strlen(s));
}

// ==========================================
// Custom printf Implementation (using stdarg.h)
// ==========================================

static void print_char(char c)
{
    __write(1, &c, 1);
}

static void print_string(const char *s)
{
    if (!s)
    {
        s = "(null)";
    }
    
    while (*s)
    {
        print_char(*s);
        s++;
    }
}

static void print_int(int num)
{
    if (num == 0)
    {
        print_char('0');
        return;
    }

    int64_t n = num;
    if (n < 0)
    {
        print_char('-');
        n = -n;
    }

    char buf[32];
    int i = 0;

    while (n > 0)
    {
        buf[i] = (n % 10) + '0';
        n = n / 10;
        i++;
    }

    while (i > 0)
    {
        i--;
        print_char(buf[i]);
    }
}

void __printf(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    int i = 0;
    while (format[i] != '\0')
    {
        if (format[i] == '%')
        {
            i++; 
            
            if (format[i] == 'd')
            {
                int val = va_arg(args, int);
                print_int(val);
            }
            else if (format[i] == 's')
            {
                char *val = va_arg(args, char *);
                print_string(val);
            }
            else if (format[i] == '%')
            {
                print_char('%'); 
            }
            else if (format[i] == '\0')
            {
                break; 
            }
            else
            {
                print_char('%');
                print_char(format[i]);
            }
        }
        else
        {
            print_char(format[i]);
        }

        i++;
    }

    va_end(args);
}