#include "keyboard.h"
#include "low_level.h"
#include "../cpu/isr.h"
#include "../cpu/idt.h"

static int key_shift = 0;



unsigned char scan_codes_CH[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', /* 9 */
  '9', '0', '\'', '=', '\b', /* Backspace */
  '\t',         /* Tab */
  'q', 'w', 'e', 'r',   /* 19 */
  't', 'z', 'u', 'i', 'o', 'p', 'e', '!', '\n', /* Enter key */
    0,          /* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', /* 39 */
 'a', '`',   0,        /* Left shift */
 '$', 'y', 'x', 'c', 'v', 'b', 'n',            /* 49 */
  'm', ',', '.', '-',   0,              /* Right shift */
  '*',
    0,  /* Alt */
  ' ',  /* Space bar */
    0,  /* Caps lock */
    0,  /* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,  /* < ... F10 */
    0,  /* 69 - Num lock*/
    0,  /* Scroll Lock */
    '7',
    '8',
    '9',
    '-',
    '4',
    '5',
    '6',
    '+',
    '1',
    '2',
    '3',
    '0',
    '.',  /* Delete Key */
    0,   0,   '<',
    0,  /* F11 Key */
    0,  /* F12 Key */
    0,  /* All other keys are undefined */
};

unsigned char scan_codes_shift_CH[128] = {
    0,  27, '+', '"', '*', 'c', '%', '&', '/', '(', /* 9 */
  ')', '=', '?', '`', '\b', /* Backspace */
  '\t',         /* Tab */
  'Q', 'W', 'E', 'R',   /* 19 */
  'T', 'Z', 'U', 'I', 'O', 'P', '[', ']', '\n', /* Enter key */
    0,          /* 29   - Control */
  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', /* 39 */
 '{', '`',   0,        /* Left shift */
 '}', 'Y', 'X', 'C', 'V', 'B', 'N',            /* 49 */
  'M', ';', ':', '_',   0,              /* Right shift */
  '*',
    0,  /* Alt */
  ' ',  /* Space bar */
    0,  /* Caps lock */
    0,  /* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,  /* < ... F10 */
    0,  /* 69 - Num lock*/
    0,  /* Scroll Lock */
    '7',
    '8',
    '9',
    '-',
    '4',
    '5',
    '6',
    '+',
    '1',
    '2',
    '3',
    '0',
    0,  /* Delete Key */
    0,   0,   '>',
    0,  /* F11 Key */
    0,  /* F12 Key */
    0,  /* All other keys are undefined */
};

u8 read_onboard_register()
{
  return port_byte_in(KEYBOARD_ONBOARD_STATUS_REGISTER);
}

void send_onboard_command(u8 command)
{
  while((read_onboard_register() & STATUS_MASK_OUT_BUFFER) == 1){}

  port_byte_out(KEYBOARD_ONBOARD_COMMAND_REGISTER,command);
}

u8 read_encoder_register()
{
  return port_byte_in(KEYBOARD_ENCODER_STATUS_BUFFER);
}

void send_encoder_command(u8 command)
{
  while((read_onboard_register() & STATUS_MASK_OUT_BUFFER) == 1){}

  port_byte_out(KEYBOARD_ENCODER_COMMAND_REG,command);
}

static void keyboard_callback(registers_t r)
{
    u8 scancode = port_byte_in(0x60);

    const int debug = 0;
    if(debug)
    {
      print_byte(scancode);
      return;
    }


    if(scancode == KEY_SHIFT_UP || scancode == KEY_SHIFT_DOWN)
    {
      key_shift = 1 - key_shift;
      return;
    }

    if(scancode & 0x80)
    {
      
    }
    else
    { 
        add_key(key_shift == 0 ? scan_codes_CH[scancode] : scan_codes_shift_CH[scancode]);
    }
 
}

void init_keyboard()
{
    register_interrupt_handler(IRQ1, keyboard_callback);
}