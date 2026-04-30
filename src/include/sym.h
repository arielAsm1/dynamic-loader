#ifndef SYM_H
#define SYM_H

#include <stdint.h>
#include "utilself.h"
#include <elf.h>

struct elf_hash_table_t
{
    uint32_t num_buckets;
    uint32_t num_chains;
};

struct gnu_hash_table_t
{
    uint32_t num_buckets;
    uint32_t sym_offset;
    uint32_t bloom_size;
    uint32_t bloom_shift;
};

#endif