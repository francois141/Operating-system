#ifndef SHELL_H
#define SHELL_H

#include "../drivers/screen.h"
#include "../system_lib/string.h"
#include "../system_lib/system.h"
#include "../drivers/pci.h"
#include "../drivers/keyboard.h"
#include "../games/snake.h"
#include "../drivers/ata.h"

#define KEY_EXECUTE key_buffer[index-1] == 0x0a
#define NOT_KEY_EXECUTE key_buffer[index-1] != 0x0a

#define COMMAND(x) strcmp(x,key_buffer)

typedef struct{
    //char command;
    //function_pointer;
} shell_input;

static char key_buffer[256];
static int index;

static void clear_buffer();
static void parse_command();

void enter_shell();
void add_key(char input);


#endif