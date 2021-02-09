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

void main()
{
  load_screen_driver();
  isr_install();
  init_keyboard();
  __asm__ __volatile__("sti");
  init_timer(1000);

  load_screen_driver();

  init_flat_gdt();

  vbe_mode_info_structure *vbe= 0x2000;


  for(int i = 0; i < 10000;i++)
  {
     u8 *a = vbe->framebuffer + 3*i;
     *a = 0xFF;
  }

  //initialisePaging();
  //enter_shell();  
}