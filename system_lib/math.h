#ifndef MATH_H
#define MATH_H

#define MAX(a,b) a < b ? b : a;
#define MIN(a,b) a < b ? a : b;

#define ABS(a) MAX(a,-a)

#define PI 3.14
#define pi 3.14

float sin(float angle);
float cos(float angle);
float sqrt(float x); 
int pow(int base, int exp);

#endif