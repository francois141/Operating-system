#ifndef PAGING_H
#define PAGING_H

#include "../cpu/idt.h"
#include "../cpu/types.h"
#include "../cpu/isr.h"
#include "../system_lib/malloc.h"

#define FRAME_TO_ADDRESS(x) (x.aligned_address * 0x1000)
#define ADDRESS_TO_FRAME(x) ((int)x) >> 12

typedef struct page_directory_entry page_directory_entry;
typedef struct page_table_entry page_table_entry;
typedef struct page_directory page_directory;
typedef struct page_table page_table; 

static page_directory *current_directory;

struct page_directory_entry
{
    u8 present              :1;
    u8 rw                   :1;
    u8 user                 :1;
    u8 write_through        :1;
    u8 cache_disabled       :1;
    u8 accessed             :1;
    u8 zero                 :1;
    u8 page_size            :1;
    u8 ignored              :1;
    u8 free                 :3; // free for use (maybe later)
    u32 aligned_address     :20;
};

struct page_table_entry
{
    u8 present              :1;
    u8 rw                   :1;
    u8 user                 :1;
    u8 write_through        :1;
    u8 cache_disabled       :1;
    u8 accessed             :1;
    u8 dirty                :1;
    u8 zero                 :1;
    u8 global               :1;
    u8 free                 :3; // free for use (maybe later)
    u32 aligned_address     :20;
};

struct page_directory
{
    page_directory_entry entries[1024]; // 1024 page_directories entries
};

struct page_table
{
    page_table_entry entries[1024];
};

void page_fault(registers_t regs);
void switch_page_directory(void* dir);
void initialisePaging();
void identity_map_kernel();
void map_frame(u32 va,u32 pa);
page_directory *clone_directory(page_directory *src);
page_table *clone_table(page_table *src);

#endif