#include "pc_speaker.h"

void beep(int milliseconds)
{
    u32 divisor = 1193180 / 350;

    port_byte_out(0x43,0xb6);
    port_byte_out(0x42,(u8)divisor);
    port_byte_out(0x42,(u8)(divisor >> 8));

    u8 tmp = port_byte_in(0x61);
    if(tmp != (tmp|3))
    {
        port_byte_out(0x61, tmp|3);
    }

    sleep(milliseconds);

    tmp = port_byte_in(0x61) & 0xFC;
    
    port_byte_out(0x61, tmp);
}