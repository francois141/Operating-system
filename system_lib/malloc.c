#include "malloc.h"

static u32 base_address = 0x40000000; 
static u32 end_address  = 0x80000000;

// Currently this is not a very powerful version but I will implement a better one in the future

u32 malloc_aligned(u32 size)
{
    // align the memory
    u32 ret_address = (base_address & 0xFFFFF000) + 0x1000;
    if(ret_address >= end_address)
        return 0; // fail
    base_address = (ret_address+size);
    return ret_address;
}

u32 malloc(u32 size)
{
    u32 ret_address = base_address;
    if(ret_address >= end_address)
        return 0; // fail
    base_address += size;
    return ret_address;
}