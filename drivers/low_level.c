// some low level assembly routines to communicate with the hardware

unsigned char port_byte_in(unsigned short port)
{
    unsigned char result;
    __asm__("in %%dx, %%al" : "=a"(result):"d"(port));
    return result;
}

void port_byte_out(unsigned short port, unsigned char data)
{
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port) );
}

unsigned short port_word_in(unsigned short port)
{
    unsigned short result;
    __asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
    return result;
}

void port_word_out(unsigned short port, unsigned short data)
{
    __asm__("out %%ax, %%dx" : : "a" (data), "d" (port));
}

unsigned short port_long_in(unsigned short port)
{
    unsigned int result;
    __asm__("inl %%edx, %%eax" : "=a" (result) : "d" (port));
    return result;
}

void port_long_out(unsigned short port, unsigned int data)
{
    __asm__("outl %%eax, %%edx" : : "a" (data), "d" (port)); 
}

