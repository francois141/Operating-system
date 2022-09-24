#include "task.h"
#include "../system_lib/malloc.h"
#include "paging.h"

volatile task *current_task;
extern page_directory *current_directory;
extern page_directory *current_directory2;

void initialise_tasking()
{
    asm volatile("cli"); // Disable interruptions during this function

    current_task = (task *)malloc(sizeof(task));
    current_task->id = 1;
    current_task->esp = current_task->ebp = 0;
    current_task->eip = 0;
    current_task->page_directory = current_directory;
    current_task->next = 0;

    asm volatile("sti"); // We can interrupt the cpu again
}

int fork()
{
    asm volatile("cli");

    task *parent = (task *)current_task;
    page_directory *dir = clone_directory(current_directory);

    task *new_task = (task *)malloc(sizeof(task));

    // TODO : Update the id in the future
    new_task->id = 2;
    new_task->esp = 0;
    new_task->ebp = 0;
    new_task->eip = 0;
    new_task->page_directory = dir;

    u32 eip = read_eip();

    // if we are the parent
    if (current_task->id == 1)
    {
        u32 esp;
        asm volatile("mov %%esp, %0"
                     : "=r"(esp));
        u32 ebp;
        asm volatile("mov %%ebp, %0"
                     : "=r"(ebp));
        new_task->esp = esp;
        new_task->ebp = ebp;
        new_task->eip = eip;
        // All finished: Reenable interrupts.
        asm volatile("sti");
        print("I am the child");
        return current_task->id;
    }
    // if we are the child
    else
    {
        print("I am the father");
        return 0;
    }
}


// Right now the goal is to perform a single reading of the registers and set the read value again. 
// This is a first trivial step in multitasking
void switch_task()
{
    if (!current_task)
        return;

    // Read esp, ebp now for saving later on.
    u32 esp, ebp, eip;
    asm volatile("mov %%esp, %0"
                 : "=r"(esp));
    asm volatile("mov %%ebp, %0"
                 : "=r"(ebp));

    eip = read_eip();   

    if (eip == 0x12345)
        return;

    current_task->eip = eip;
    current_task->esp = esp;
    current_task->ebp = ebp;

    // TODO: Update current task

    esp = current_task->esp;
    ebp = current_task->ebp;

    asm volatile("cli");
    asm volatile("mov %0, %%ecx\n" :: "r"(eip));
    asm volatile("mov %0, %%esp\n" :: "r"(esp));
    asm volatile("mov %0, %%ebp\n" :: "r"(ebp));
    asm volatile("mov %0, %%cr3\n" :: "r"(current_directory2));
    asm volatile("sti");
    print("Switch done");
}
