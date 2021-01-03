#include "string.h"

char lower_case(char letter)
{
    if(letter < 'A' || letter > 'Z')
        return 0;
    return 'a' + (letter - 'A');
}

char upper_case(char letter)
{
    if(letter < 'a' || letter > 'z')
        return 0;
    return 'A' + (letter - 'a'); 
}

int strlen(char s[])
{
    int i = 0;
    while(s[i] != 0)
        i++;
    return i;
}

// return 1 if both strings are equals 0 otherwise
int strcmp(char s1[], char s2[])
{
    for(int i = 0; s1[i] == s2[i];i++)
    {
        if(s1[i] == s2[i] && s1[i] == 0)
            return 1;
    }

    return 0;
}