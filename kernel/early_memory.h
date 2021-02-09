#ifndef EARLY_MEMORY_H
#define EARLY_MEMORY_H

#include "../cpu/types.h"

typedef unsigned short uint16;
typedef unsigned char  uint8;
typedef unsigned int   uint32;



typedef struct vbe_info_signature{
	char signature[4];	
	uint16 version;			
	uint32 oem;			
	uint32 capabilities;		
	uint32 video_modes;		
	uint16 video_memory;		
	uint16 software_rev;		
	uint32 vendor;			
	uint32 product_name;		
	uint32 product_rev;		
	char reserved[222];		
	char oem_data[256];		
} __attribute__((packed)) vbe_info_signature;

typedef struct vbe_mode_info_structure {
	uint16 attributes;		// deprecated, only bit 7 should be of interest to you, and it indicates the mode supports a linear frame buffer.
	uint8 window_a;			// deprecated
	uint8 window_b;			// deprecated
	uint16 granularity;		// deprecated; used while calculating bank numbers
	uint16 window_size;
	uint16 segment_a;
	uint16 segment_b;
	uint32 win_func_ptr;		// deprecated; used to switch banks from protected mode without returning to real mode
	uint16 pitch;			// number of bytes per horizontal line
	uint16 width;			// width in pixels
	uint16 height;			// height in pixels
	uint8 w_char;			// unused...
	uint8 y_char;			// ...
	uint8 planes;
	uint8 bpp;			// bits per pixel in this mode
	uint8 banks;			// deprecated; total number of banks in this mode
	uint8 memory_model;
	uint8 bank_size;		// deprecated; size of a bank, almost always 64 KB but may be 16 KB...
	uint8 image_pages;
	uint8 reserved0;
 
	uint8 red_mask;
	uint8 red_position;
	uint8 green_mask;
	uint8 green_position;
	uint8 blue_mask;
	uint8 blue_position;
	uint8 reserved_mask;
	uint8 reserved_position;
	uint8 direct_color_attributes;
 
	uint32 framebuffer;		// physical address of the linear frame buffer; write here to draw to the screen
	uint32 off_screen_mem_off;
	uint16 off_screen_mem_size;	// size of memory in the framebuffer but not being displayed on the screen
	uint8 reserved1[206];
} __attribute__ ((packed)) vbe_mode_info_structure;

typedef struct e820_info_block{


}__attribute__((packed)) e820_info_block;

#endif