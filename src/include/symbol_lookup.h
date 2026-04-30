#ifndef SYMBOL_LOOKUP_H
#define SYMBOL_LOOKUP_H

#include "object.h"

void * symbol_lookup(const char * name, struct elf_object_s * objects);
size_t get_symbol_count(struct elf_object_s *obj);

#endif