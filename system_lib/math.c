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
    __asm__("fcos" : "=t"(ret) : "0"(x));
    return ret;
}