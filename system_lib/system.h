#ifndef SYSTEM_H
#define SYSTEM_H

#include "../drivers/timer.h"

#define ZERO_BYTE 0x0

extern u32 tick; 

void memcpy(char*,char*,unsigned int);
void memset(char*,char,unsigned int);
void memclear(char*,unsigned int);
void int_to_ascii(int,char[]);
void sleep(int);
int random();

#endif