#ifndef LOADER_H
#define LOADER_H

#include "object.h"

int map_elf_segments(int fd, struct elf_object_s * obj);

#endif