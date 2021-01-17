#ifndef LIBGUI_H
#define LIBGUI_H

#include "../../cpu/types.h"
#include "../../drivers/screen.h"
#include "../math.h"

#define ROW_SIZE 320
#define COLUMN_SIZE 200


typedef struct{
    u16 width;
    u16 height;
} Screen_parameters;

Screen_parameters screen_parameters;

void initialiseLib();

void drawLine(u16 y1,u16 x1,u16 y2,u16 x2);

void drawRectangle(u16 y1,u16 x1,u16 y2,u16 x2,u16 width);
void drawCircle(u16 y, u16 x, float radius, u16 width );

void drawFilledRectangle(u16 y,u16 x1,u16 y2,u16 x2);
void drawFilledCircle(u16 y,u16 x,float radius);

void drawText(u16 startX, u16 startY,char *message);

void clear();

#endif
