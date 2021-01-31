#ifndef GDT_H
#define GDT_H

#include "types.h"

struct gdt_entry
{
    u16 limit_low;
    u16 base_low;
    u8 base_middle;
    u8 access;
    u8 granularity;
    u8 base_high;
} __attribute__((packed));

struct gdt_structure_pointer
{
    u16 limit;
    u32 base;
} __attribute__((packed));

typedef struct gdt_entry gdt_entry;
typedef struct gdt_structure_pointer gdt_structure_pointer;

extern void gdt_flush(u32);

void init_flat_gdt();
static void create_entry(u32,u32,u32,u8,u8);

#endif