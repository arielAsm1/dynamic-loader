#ifndef LOADER_UTIL_H
#define LOADER_UTIL_H

#include <stdint.h>
#include <elf.h>

uint64_t align_down(uint64_t v);
uint64_t align_up(uint64_t v);
int phdr_to_prot(int32_t flags);

#endif