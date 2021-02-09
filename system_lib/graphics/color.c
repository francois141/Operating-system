#include "color.h"

u32 rgbtohex(rgb in)
{
    return ((in.red << 16) & 0xFF) | ((in.green << 8) & 0xFF) | ((in.blue) & 0xFF);
}

rgb hextorgb(u32 in)
{
    rgb out;
    out.blue = in & 0xFF;
    out.green = (in << 8) & 0xFF;
    out.red = (in << 16) & 0xFF;
}