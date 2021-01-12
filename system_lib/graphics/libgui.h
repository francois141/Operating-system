#ifndef LIBGUI_H
#define LIBGUI_H

#include "cpu/types.h"
#include "drivers/screen.h"

typedef struct{
    int width;
    int height;
} Screen_parameters; 

Screen_parameters screen_parameters;

void initialiseLib();

void drawRectangle(u8 y1,u8 x1,u8 y2,u8 x2,u8 width);
void drawCircle(u8 y, u8 x, float radius, u8 width );

void drawFilledRectangle(u8 y,u8 x1,u8 y2,u8 x2);
void drawFilledCircle(u8 y,u8 x,float radius);

void drawText(u8 startX, u8 startY,char *message);

#endif