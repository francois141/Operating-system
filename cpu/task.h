#ifndef TASK_H
#define TASK_H

#include "paging.h"
#include "types.h"

typedef struct task
{
   int id;                
   u32 esp;
   u32 ebp;       
   u32 eip;           
   page_directory *page_directory; 
   struct task *next;    
} task;

void initialise_tasking();

void task_switch();

int fork();

void move_stack(void *new_stack_start, u32 size);

int getpid();

#endif