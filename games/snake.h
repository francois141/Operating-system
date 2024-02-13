#ifndef SNAKE_H
#define SNAKE_H

#include "../system_lib/graphics/libgui.h"
#include "../system_lib/system.h"
#include "../drivers/pc_speaker.h"
#include "../drivers/keyboard.h"
#include "../system_lib/math.h"

void start_snake();

static void draw_arena();
static void step();
static void draw_snake();
static void spawn_food();
static void draw_food();
static int check_collision();
static void set_snake_direction();

typedef struct{
    u16 size;
    u16 width;
    u16 maxSize;
    u16 dataX[20];
    u16 dataY[20];
    u8  direction;
} Snake;

typedef struct{
    u16 x;
    u16 y;
} Food;

static Snake snake;
static Food food;

#endif