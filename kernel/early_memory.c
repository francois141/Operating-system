#include "early_memory.h"

const vbe_info_signature*      VESA_information_address = 0x1000;
const vbe_mode_info_structure* VESA_block_address       = 0x2000;

const e820_info_block* e820_address = 0x3000;

const u32* kernel_loader_address    = 0x8000;
const u32* kernel_address           = 0x100000;

const u32* malloc_start_address     = 0x40000000;
const u32* malloc_end_address       = 0x80000000;