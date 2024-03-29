#include "../cpu/idt.h"
#include "../cpu/isr.h"
#include "../drivers/timer.h"
#include "../drivers/screen.h"
#include "../drivers/keyboard.h"
#include "../drivers/pci.h"
#include "shell.h"
#include "../system_lib/graphics/libgui.h"
#include "../drivers/pc_speaker.h"
#include "../cpu/paging.h"
#include "../system_lib/malloc.h"
#include "../cpu/gdt.h"
#include "early_memory.h"
#include "../cpu/task.h"

void main()
{
  isr_install();
  init_keyboard();
  __asm__ __volatile__("sti");
  init_timer(1000);

  init_flat_gdt();

  load_screen_driver();

  initialisePaging();

  enter_shell();

  // Working on the tasking system
  initialise_tasking();
  fork();

  while(1) {
    //print("okay");
  }
}