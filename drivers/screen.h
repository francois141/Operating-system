#ifndef SCREEN_H
#define SCREEN_H

#include "../cpu/types.h"
#include "../drivers/low_level.h"
#include "../system_lib/system.h"


#define VIDEO_ADDRESS (char *)0xa0000
#define MAX_ROWS 28
#define MAX_COLS 45

#define ROW_SIZE 320
#define COLUMN_SIZE 200

#define CHAR_SIZE 7

typedef struct
{
    u8 cursorX;
    u8 cursorY;
} Screen_settings;

static Screen_settings screen_settings;

void load_screen_driver();
void clear_screen();

int get_cursor_offset();
void set_cursor_offset(int);

int get_screen_offset(int col, int row);
int get_screen_offset_row(int offset);
int get_screen_offset_col(int offset);  
int handle_scrolling();

void print(char*);

static void new_line();

void remove_last_char();

void putch(char);

void print_byte(u8);
void print_word(u16);
void print_long(u32);
void print_number(u32);



#endif