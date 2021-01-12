#ifndef KEYBOARD_H
#define KEYBOARD_H

#define UP_ARROW    250
#define LEFT_ARROW  251
#define RIGHT_ARROW 252
#define DOWN_ARROW  253

#define KEY_SHIFT_UP    0x2A
#define KEY_SHIFT_DOWN  0xAA

#define KEYBOARD_ENCODER_STATUS_BUFFER 0x60
#define KEYBOARD_ENCODER_COMMAND_REG      0x60

#define KEYBOARD_ONBOARD_STATUS_REGISTER  0x64
#define KEYBOARD_ONBOARD_COMMAND_REGISTER 0x64

#define STATUS_MASK_OUT_BUFFER 0x1 // dont read now if 0 1 read
#define STATUS_MASK_IN_BUFFER 0x2  // if 0 write now 1 dont write
#define STATUS_MASK_SYSTEM_FLAG 0x4 // system flag
#define STATUS_MASK_COMMAND_DATA 0x8 // 0 if last write was data 1 if it was a command

#include "../drivers/screen.h"
#include "../kernel/shell.h"

unsigned char key_pressed[256];

void init_keyboard();

#endif