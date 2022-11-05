float sin(float angle)
{
    float ret = 0.0;
    __asm__("fsin" : "=t"(ret) : "0"(angle));
    return ret;
}

float cos(float angle)
{
    float ret = 0.0;
    __asm__("fcos" : "=t"(ret) : "0"(angle));
    return ret;
}

float sqrt(float x)
{
    float ret = 0.0;
    __asm__("fsqrt" : "=t"(ret) : "0"(x));
    return ret;
}

int pow(int base, int exp)
{
    int result = 1;
    
    while(1)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        if (!exp)
            break;
        base *= base;
    }

    return result;
}