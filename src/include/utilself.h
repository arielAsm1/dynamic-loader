#ifndef UTILSELF_H
#define UTILSELF_H

#include <stdint.h>
#include <stddef.h>
#include <elf.h>
#include "sys_calls.h"

int32_t elf_header_check(Elf64_Ehdr * header);
int32_t verfiy_dynamic(Elf64_Phdr * phdr, size_t phdrs, char * base);
int32_t dyn_verify_dynamic(Elf64_Dyn * dynamic, char * base);

Elf64_Phdr * phdr_get_ent(Elf64_Phdr * phdr, size_t size, uint32_t type);
Elf64_Dyn  * phdr_get_dyn(Elf64_Phdr * phdr, size_t phdrs, char * base);

size_t my_strlen(const char * s);
void my_memcpy(char * dest, const char * src, size_t n);
int my_strcmp(const char *str1, const char *str2);
void print(const char * s);
int my_strncmp(const char * str1, const char * str2, size_t n);

void __printf(const char *format, ...);

#endif
