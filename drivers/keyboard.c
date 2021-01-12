#include "keyboard.h"
#include "low_level.h"
#include "../cpu/isr.h"
#include "../cpu/idt.h"


unsigned char key_codes[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'z', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'y', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    250,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    251,	/* Left Arrow */
    252,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    253,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
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

    if(scancode & 0x80)
    {
        // key release
    }
    else
    {
        add_key(key_codes[scancode]);
    }
}

void init_keyboard()
{
    register_interrupt_handler(IRQ1, keyboard_callback);
}