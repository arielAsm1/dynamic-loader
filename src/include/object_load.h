#ifndef OBJECT_LOAD_H
#define OBJECT_LOAD_H

#include <elf.h>
#include "linking.h"

int object_load(struct elf_object_s * obj, int fd);

#endif