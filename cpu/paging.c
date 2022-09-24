#include "paging.h"


void page_fault(registers_t regs)
{
    print("PAGE FAULT\nSYSTEM IS NOW IN AN INFINITE LOOP");
    while(1){};
}

void initialisePaging()
{
    current_directory = malloc_aligned(sizeof(page_directory));

    identity_map_kernel(); // a big identity map for the moment

    register_interrupt_handler(14,page_fault);
    switch_page_directory(current_directory);

    current_directory2 = clone_directory(current_directory);
}

void identity_map_kernel()
{
    for(int i = 0; i < 10000000; i++)
    {
        map_frame(i*NB_ENTRIES,i*NB_ENTRIES);
    }
}

void switch_page_directory(void* dir)
{
    register_interrupt_handler(PAGE_FAULT_INTERRUPT_CODE, page_fault);

    __asm__ volatile("mov %0, %%cr3"::"r"(dir));
    u32 cr0;
    __asm__ volatile("mov %%cr0, %0": "=r"(cr0));
    cr0 |= 0x80000000;
    __asm__ volatile("mov %0, %%cr0":: "r"(cr0));
}

void map_frame(u32 va, u32 pa)
{
    // nothing for the moment
    u32 base    = (va >> BITS_OFFSET_IN_PAGE) / NB_ENTRIES;
    u32 offset  = (va >> BITS_OFFSET_IN_PAGE) % NB_ENTRIES;

    if(current_directory->entries[base].present == 0)
    {
        // we need to get some free space
        u32 aligned_address = malloc_aligned(sizeof(page_table));
        current_directory->entries[base].present = 1;
        current_directory->entries[base].rw      = 1;
        current_directory->entries[base].aligned_address = ADDRESS_TO_FRAME(aligned_address);
    }

    page_table* page_table_location = FRAME_TO_ADDRESS(current_directory->entries[base].aligned_address);

    page_table_location->entries[offset].present = 1;
    page_table_location->entries[offset].rw      = 1;
    page_table_location->entries[offset].aligned_address = ADDRESS_TO_FRAME(pa);
}


page_directory *clone_directory(page_directory *src) {

    page_directory *dir = (page_directory*)malloc_aligned(sizeof(page_directory));

    memset(dir,0,sizeof(page_directory));

    for(int i = 0; i < NB_ENTRIES;i++) {

        if(!src->entries[i].present) {
            continue;
        }

        dir->entries[i] = src->entries[i];

        page_table *src_page_table = (page_table*) FRAME_TO_ADDRESS(src->entries[i].aligned_address);
        page_table *copied = clone_table(src_page_table);

        dir->entries[i].aligned_address = ADDRESS_TO_FRAME(copied);
    }

    return dir;
}


page_table *clone_table(page_table *src) {

    page_table *table = (page_table*)malloc_aligned(sizeof(page_table));

    memset(table,0,sizeof(page_table));

    for(int i = 0; i < NB_ENTRIES; i++) {
        if(!src->entries[i].present) {
            continue;
        }

        table->entries[i] = src->entries[i];
    }

    return table;
}