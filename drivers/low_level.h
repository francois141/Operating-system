#ifndef LOW_LEVEL_H
#define LOW_LEVEL_H

unsigned char port_byte_in(unsigned short);
void port_byte_out(unsigned short,unsigned char);

unsigned short port_word_in(unsigned short);
void port_word_out(unsigned short, unsigned short);

unsigned int port_long_in(unsigned short);
void port_long_out(unsigned short,unsigned int);

#endif