#include "system.h"

void memcpy(char *source, char *dest, unsigned int nbBytes)
{
    for(int i = 0; i < nbBytes;i++)
    {
        *(dest + i) = *(source + i);
    }
}

void memset(char *address,char value, unsigned int nbBytes)
{
    for(int i = 0; i < nbBytes;i++)
    {
        *(address + i) = value;
    }

}

void int_to_ascii(int n, char str[]) {
    int i, sign;
    if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';
}

void sleep(int milliseconds)
{
    int current = tick;
    while(tick-current < milliseconds){}
    return;
}

int random(){
    return tick; // just return the time stamp as random value
}



