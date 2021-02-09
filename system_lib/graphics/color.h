#ifndef COLOR_H
#define COLOR_H

#include "../../cpu/types.h"

#define COLOR_BLACK 0x000000
#define COLOR_WHITE 0xFFFFFF

#define COLOR_RED   0xFF0000
#define COLOR_GREEN 0x00FF00
#define COLOR_BLUE  0x0000FF

#define COLOR_OLIVE 0x808000

typedef struct rgb{
    u8 red;
    u8 green;
    u8 blue;
} rgb;

u32 rgbtohex(rgb in);
rgb hextorgb(u32 in);


#endif