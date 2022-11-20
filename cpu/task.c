#include "task.h"
#include "../system_lib/malloc.h"
#include "paging.h"

volatile task *current_task;

extern page_directory *current_directory;

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

    new_task->id = 2;
    new_task->esp = 0;
    new_task->ebp = 0;
    new_task->eip = 0;
    new_task->page_directory = dir;
    new_task->next = 0;

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
        current_task->next = new_task;
        // All finished: Reenable interrupts.
        asm volatile("sti");
        print("I am the father\n");
        return current_task->id;
    }
    // if we are the child
    else
    {
        asm volatile("sti");
        print("I am the child");
        return 0;
    }
}

// Right now the goal is to perform a single reading of the registers and set the read value again.
// This is a first trivial step in multitasking
void switch_task()
{
    if (!current_task)
        return;

    println("Switching task now");

    // Read esp, ebp now for saving later on.
    u32 esp, ebp, eip;
    asm volatile("mov %%esp, %0"
                 : "=r"(esp));
    asm volatile("mov %%ebp, %0"
                 : "=r"(ebp));

    eip = read_eip();

    if (eip == 0x12345) {
        println("0x12345");
        asm volatile("sti");
        return;
    }
        
    current_task->eip = eip;
    current_task->esp = esp;
    current_task->ebp = ebp;

    if (current_task->next != 0)
    {
        println("Next available");
        current_task = current_task->next;
    }

    esp = current_task->esp;
    ebp = current_task->ebp;

    println("Before switch");
    asm volatile("cli");
    asm volatile (
			"mov %0, %%ebx\n"
			"mov %1, %%esp\n"
			"mov %2, %%ebp\n"
			"mov $0x12345, %%eax\n"
			"jmp *%%ebx"
			: : "r" (eip), "r" (esp), "r" (ebp)
			: "%ebx", "%esp", "%eax");
}
    


