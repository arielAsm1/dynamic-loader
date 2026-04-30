#ifndef RELOCATIONS_H
#define RELOCATIONS_H

#include "object.h"

int relocate_object(struct elf_object_s * obj, struct elf_object_s * objects);

#endif