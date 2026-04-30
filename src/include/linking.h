#ifndef LINKING_H
#define LINKING_H

#include "object.h"

void object_add(struct elf_object_s * obj);
struct elf_object_s * object_first();
struct elf_object_s * object_find(const char * name);

#endif