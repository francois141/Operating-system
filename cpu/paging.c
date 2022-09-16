#include "paging.h"


void page_fault(registers_t regs)
{
    print("PAGE FAULT");
    while(1){};
}

void initialisePaging()
{
    current_directory = malloc_aligned(sizeof(page_directory));

    identity_map_kernel(); // a big identity map for the moment

    register_interrupt_handler(14,page_fault);
    switch_page_directory(current_directory);
}

void identity_map_kernel()
{
    for(int i = 0; i < 10000000; i++)
    {
        map_frame(i*0x1000,i*0x1000);
    }
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

void map_frame(u32 va, u32 pa)
{
    // nothing for the moment
    u32 base    = (va >> 12) / 1024;
    u32 offset  = (va >> 12) % 1024;

    if(current_directory->entries[base].present == 0)
    {
        // we need to get some free space
        u32 alligned_address = malloc_aligned(sizeof(page_table));
        current_directory->entries[base].present = 1;
        current_directory->entries[base].rw      = 1;
        current_directory->entries[base].aligned_address = alligned_address >> 12;
    }

    page_table* page_table_location = current_directory->entries[base].aligned_address << 12;

    page_table_location->entries[offset].present = 1;
    page_table_location->entries[offset].rw      = 1;
    page_table_location->entries[offset].aligned_address = pa >> 12;
}


page_directory *clone_directory(page_directory *src) {

    u32 phys;
    page_directory *dir = (page_directory*)malloc_aligned(sizeof(page_directory));

    memset(dir,0,sizeof(page_directory));

    for(int i = 0; i < 1024;i++) {

        if(!src->entries[i].present) {
            continue;
        }

        page_table *src_page_table = (page_table*) FRAME_TO_ADDRESS(src->entries[i]);
        page_table *copied = clone_table(src_page_table);

        page_directory_entry entry = src->entries[i];
        entry.aligned_address = ADDRESS_TO_FRAME(copied);
        
        dir->entries[i] = entry;
    }

    return dir;
}


page_table *clone_table(page_table *src) {

    page_table *table = (page_table*)malloc_aligned(sizeof(page_table));

    memset(table,0,sizeof(page_table));

    for(int i = 0; i < 1024; i++) {
        if(!table->entries[i].present) {
            continue;
        }

        table->entries[i] = src->entries[i];
    }

    return table;
}