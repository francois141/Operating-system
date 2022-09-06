#ifndef MALLOC_H
#define MALLOC_H

#include "../cpu/types.h"

u32 malloc_aligned(u32 size);
u32 malloc(u32 size);
void free(u32 address);

#endif