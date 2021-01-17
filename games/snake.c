#include "snake.h"

void start_snake()
{

    load_screen_driver(); 

    initialiseLib();

    KEYAPRESSED = 0;
    KEYDPRESSED = 0;
    KEYSPRESSED = 0;
    KEYWPRESSED = 0;

    snake.size      = 1;
    snake.maxSize   = 20;
    snake.width     = 5;
    snake.direction = 0x01;

    for(u16 i = 1; i < snake.maxSize;i++)
    {
        snake.dataX[i] = 0;
        snake.dataY[i] = 0;
    }

    snake.dataX[0] = 40;
    snake.dataY[0] = 40;

    food.x = 100;
    food.y = 100;

    spawn_food();

    while(1)
    {
        clear();
        set_snake_direction();
        step();
        draw_arena();
        draw_snake();
        draw_food();

        if(check_collision())
        {
            beep(100);
            sleep(300);
            load_screen_driver();
            return;
        }

        sleep(100);
    }

}

static void set_snake_direction()
{
    if(KEYAPRESSED)
    {
        snake.direction = 0b00001000;
    }
    else if(KEYSPRESSED)
    {
        snake.direction = 0b00000010;
    }
    else if(KEYDPRESSED)
    {
        snake.direction = 0b00000001;
    }
    else if(KEYWPRESSED)
    {
        snake.direction = 0b00000100;
    }

    KEYAPRESSED = 0;
    KEYDPRESSED = 0;
    KEYSPRESSED = 0;
    KEYWPRESSED = 0;
}

static int check_collision()
{

    if(snake.dataX[0] < 0 || snake.dataX[0] > screen_parameters.width)
    {
        return 1;
    }
    if(snake.dataY[0] < 0 || snake.dataY[0] > screen_parameters.height)
    {
        return 1;
    }

    for(int i = 1; i < snake.size;i++)
    {
        if(snake.dataX[0] == snake.dataX[i] && snake.dataY[0] == snake.dataY[i])
        {
            return 1;
        }
    }

    // now check for food

    if(snake.dataX[0] == food.x && snake.dataY[0] == food.y)
    {
        snake.size++;
        if(snake.size == 6)
        {
            drawText(100,100,"WIN WIN WIN !!!");
            beep(700);
            return 1;
        }

        spawn_food();
    }

    return 0;
}

static void step()
{
    for(int i = snake.size-1; i >= 0; i--)
    {
        snake.dataX[i+1] = snake.dataX[i];
        snake.dataY[i+1] = snake.dataY[i];
    }

    if(snake.direction & 0x1)
    {
        snake.dataX[0] = snake.dataX[1] + snake.width;
        snake.dataY[0] = snake.dataY[1];
    }

    if(snake.direction & 0x2)
    {
        snake.dataX[0] = snake.dataX[1];
        snake.dataY[0] = snake.dataY[1] + snake.width;
    }

    if(snake.direction & 0x4)
    {
        snake.dataX[0] = snake.dataX[1];
        snake.dataY[0] = snake.dataY[1] - snake.width;
    }

    if(snake.direction & 0x8)
    {
        snake.dataX[0] = snake.dataX[1] - snake.width;
        snake.dataY[0] = snake.dataY[1];
    }
}

static void spawn_food()
{
    u16 positionX = 5*random() % 310 + 5;
    u16 positionY = 5*random() % 190 + 5;

    food.x = positionX;
    food.y = positionY;
}

static void draw_food()
{
    u16 positionX = food.x;
    u16 positionY = food.y;

    drawFilledRectangle(positionY,positionX,positionY+5,positionX+5);
}

static void draw_snake()
{
    for(u16 i = 0; i < snake.size;i++)
    {
        u16 y = snake.dataY[i];
        u16 x = snake.dataX[i];
        drawFilledRectangle(y,x,y+snake.width,x+snake.width);
    }
}

static void draw_arena()
{
    const u16 width = screen_parameters.width;
    const u16 height = screen_parameters.height;
    
    drawFilledRectangle(0,0,height,5);  
    drawFilledRectangle(0,width-5,height,width);  

    drawFilledRectangle(0,0,5,width);
    drawFilledRectangle(height-5,0,height,width);
}