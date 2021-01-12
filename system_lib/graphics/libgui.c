#include "libgui.h"



void initialiseLib()
{
    screen_parameters.height = getHeight();
    screen_parameters.width  = getWidth();
}

void drawLine(u8 y1,u8 x1, u8 y2, u8 x2)
{
  int dx=x2-x1; 
  int dxabs=ABS(dx); 
  int sdx= dx >= 0 ? 1 : -1;

  int dy=y2-y1;    
  int dyabs=ABS(dy);
  int sdy= dy >= 0 ? 1 : -1;

  if (dxabs>=dyabs) 
  {
    float slope=(float)dy / (float)dx;

    for(int i=0; i!=dx ; i += sdx)
    {
      int px = i+x1;
      int py = slope*i+y1;
      put_pixel(py,px,12);
    }
  }

  else 
  {
    float slope=(float)dx / (float)dy;
    for(int i=0; i != dy; i += sdy)
    {
      int px = slope*i+x1;
      int py = i+y1;
      put_pixel(py,px,15);
    }
  }

}

void drawRectangle(u8 y1,u8 x1,u8 y2,u8 x2,u8 width)
{
    drawLine(y1,x1,y1,x2);
    drawLine(y2,x1,y2,x2);
    drawLine(y1,x1,y2,x1);
    drawLine(y1,x2,y2,x2);
}

void drawCircle(u8 y, u8 x, float radius, u8 width)
{
#define SAMPLES 250
    for(int i = 0; i < SAMPLES;i++)
    {
        float x1 = cos(i/(float)SAMPLES * 2 * pi);
        float y1 = sin(i/(float)SAMPLES * 2 * pi);

        put_pixel(y + (u8)radius*y1,x + (u16)radius*x1,12);
    }
}

void drawFilledRectangle(u8 y1,u8 x1,u8 y2,u8 x2)
{
    for(int i = x1; i <= x2;i++)
    {
        for(int j = y1; j < y2;j++)
        {
            if(0 <= i && i < ROW_SIZE && 0 <= j && j <= COLUMN_SIZE)
                put_pixel(j,i,13);
        }
    }
}
void drawFilledCircle(u8 y,u8 x,float radius)
{
    #define SAMPLES 250
    for(int j = 0; j < radius;j++)
    {
        for(int i = 0; i < SAMPLES;i++)
        {
            float x1 = cos(i/(float)SAMPLES * 2 * pi);
            float y1 = sin(i/(float)SAMPLES * 2 * pi);

            put_pixel(y + j*y1,x + j*x1,12);
        }
    }

}

void drawText(u8 startX, u8 startY, char *message)
{   
    int i = 0;
    while(message[i] != 0)
    {
        write_char(startY,startX + 7*i,ascii_to_array(message[i]));
        i++;
    }
}