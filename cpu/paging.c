#include "paging.h"

void page_fault(registers_t regs)
{
    while(1){};
}

void switch_page_directory(void* dir)
{
    register_interrupt_handler(14, page_fault);

    __asm__ volatile("mov %0, %%cr3"::"r"(dir));
    u32 cr0;
    __asm__ volatile("mov %%cr0, %0": "=r"(cr0));
    cr0 |= 0x80000000; 
    __asm__ volatile("mov %0, %%cr0":: "r"(cr0));
}

void initialisePaging()
{
    int i;
    for(i = 0; i < 1024; i++)
    {
        page_directory[i] = 0x00000002;
    }
    for(i = 0; i < 1024; i++)
    {

        first_page_table[i] = (i * 0x1000) | 3; 
    }
    page_directory[0] = ((unsigned int)first_page_table) | 3;
    switch_page_directory(page_directory);
}