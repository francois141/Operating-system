#ifndef PAGING_H
#define PAGING_H

#include "../cpu/idt.h"
#include "../cpu/types.h"
#include "../cpu/isr.h"

u32 page_directory[1024] __attribute__((aligned(4096)));
u32 first_page_table[1024] __attribute__((aligned(4096)));

void page_fault(registers_t regs);
void switch_page_directory(void* dir);
void initialisePaging();

#endif