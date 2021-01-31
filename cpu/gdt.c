#include "gdt.h"

static gdt_entry gdt_entries[3];
static gdt_structure_pointer  gdt_ptr;

void init_flat_gdt() // There is a gdt in the bootloader but it's more flexible in c if we want to change later
{
   gdt_ptr.limit = (sizeof(gdt_entry) * 3) - 1;
   gdt_ptr.base  = (u32)&gdt_entries;

    create_entry(0, 0, 0, 0, 0);                // Null segment
    create_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
    create_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment

    gdt_flush((u32)&gdt_ptr);
}

static void create_entry(u32 num, u32 base, u32 limit, u8 access, u8 gran)
{
   gdt_entries[num].base_low    = (base & 0xFFFF);
   gdt_entries[num].base_middle = (base >> 16) & 0xFF;
   gdt_entries[num].base_high   = (base >> 24) & 0xFF;

   gdt_entries[num].limit_low   = (limit & 0xFFFF);
   gdt_entries[num].granularity = (limit >> 16) & 0x0F;

   gdt_entries[num].granularity |= gran & 0xF0;
   gdt_entries[num].access      = access;
} 