#ifndef SCREEN_H
#define SCREEN_H

#include "../cpu/types.h"
#include "../drivers/low_level.h"
#include "../system_lib/system.h"

#define VIDEO_ADDRESS (char *)0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80

#define WHITE_ON_BLACK 0x0f
#define WHITE_ON_RED   0x0a

#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

void load_screen_driver();

void print_char(char,int,int,char);
void print(char*);
void print_at(char*,int,int);

void putch(char);

void print_byte(u8);
void print_word(u16);
void print_long(u32);
void print_number(u32);

void clear_screen();
int get_cursor_offset();
void set_cursor_offset(int);
int get_screen_offset(int col, int row);
int get_screen_offset_row(int offset);
int get_screen_offset_col(int offset);  
int handle_scrolling(int);

#endif