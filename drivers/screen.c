#include "screen.h"

int offset = 0;

void load_screen_driver()
{
    clear_screen();
    set_cursor_offset(get_screen_offset(0,0));
}

void print_at(char* message, int col, int row)
{
    if(col >= 0 && row >= 0)
    {
        set_cursor_offset(get_screen_offset(col,row));
    }

    int i = 0;
    while(message[i] != 0)
    {
        print_char(message[i++], col, row, WHITE_ON_RED);
    }
}

void print(char* message)
{
    print_at(message,-1,-1);
}


void putch(char letter)
{
    char *message = "Z";
    *message = letter;
    print(message);
}   

void print_char(char character, int col, int row, char attribute_byte)
{
    unsigned char *vidmem = (unsigned char *) VIDEO_ADDRESS;

    if(!attribute_byte)
    {
        attribute_byte = WHITE_ON_BLACK;
    }

    int offset;
    if(col >= 0 && row >= 0)
    {
        offset = get_screen_offset(col,row);
    }
    else
    {
        offset = get_cursor_offset();
    }

    if(character == '\n')
    {
        int rows = offset / (2*MAX_COLS);
        offset = get_screen_offset(79,rows);
    }
    else
    {
        vidmem[offset] = character;
        vidmem[offset+1] = attribute_byte;
    }

    offset += 2;
    offset = handle_scrolling(offset);
    set_cursor_offset(offset);
}

static void print_hex(u8 _byte)
{
    int value;
    if(_byte < 10)
    {
        value = '0' + _byte;
    }
    else
    {
        _byte -= 10;
        value = 'a' + _byte;
    }
    print((char *)&value);
}

void print_byte(u8 _byte)
{
    print_hex((_byte >> 4) & 0xF);
    print_hex(_byte & 0xF);
} 

void print_word(u16 _word)
{
    print_byte((_word >> 8));
    print_byte(_word & 0xFF);
}

void print_long(u32 _long)
{
    print_word((_long >> 16) & 0xFFFF);
    print_word((_long) & 0xFFFF);
}

void print_number(u32 number)
{
    char output[15];
    memset(output,0,15);
    int i = 0;
    while(number != 0)
    {
        output[i] = '0' + (number % 10);
        number /= 10;
        i++;
    }
    for(;i >= 0;i--)
    {
        print(&output[i]);
    }
}

int get_cursor_offset()
{
    port_byte_out(REG_SCREEN_CTRL, 14);
    int offset = port_byte_in(REG_SCREEN_DATA) << 8;
    port_byte_out(REG_SCREEN_CTRL, 15);
    offset += port_byte_in(REG_SCREEN_DATA);
    return offset * 2;
}

void set_cursor_offset(int offset)
{
    offset /= 2;
    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}

void clear_screen()
{
    int screen_size = MAX_COLS * MAX_ROWS;
    char *screen = VIDEO_ADDRESS;
    for(int i = 0; i < screen_size;i++)
    {
        screen[i*2] = ' ';
        screen[i*2+1] = WHITE_ON_BLACK;
    }
    set_cursor_offset(get_screen_offset(0,0));
}

int get_screen_offset(int col, int row) { return 2 * (row * MAX_COLS + col);}
int get_screen_offset_row(int offset)   { return offset / (2*MAX_COLS);}
int get_screen_offset_col(int offset)   { return (offset - get_screen_offset_row(offset)*2*MAX_COLS)/2;}  

int handle_scrolling(int cursor_offset)
{
    if(cursor_offset < MAX_COLS * MAX_ROWS * 2)
    {
        return cursor_offset;
    }

    for(int i = 1; i < MAX_ROWS;i++)
    {
        memcpy(get_screen_offset(0,i) + VIDEO_ADDRESS, get_screen_offset(0,i-1) + VIDEO_ADDRESS,MAX_COLS*2);
    }

    char* last_line = get_screen_offset(0,MAX_ROWS-1) + VIDEO_ADDRESS;
    for(int i = 0; i < MAX_COLS*2;i++){
        last_line[i] = 0;
    }

    cursor_offset -= 2*MAX_COLS;

    return cursor_offset;
}