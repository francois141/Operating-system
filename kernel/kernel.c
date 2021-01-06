#include "../cpu/idt.h"
#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../drivers/screen.h"
#include "../drivers/keyboard.h"
#include "../drivers/ata.h"
#include "../drivers/pci.h"
#include "shell.h"
#include "../drivers/font.h"


void main()
{
  load_screen_driver();

  print("francois \n");
  print("bonjour");

  print_byte(15);


  isr_install();
  init_keyboard();
  __asm__ __volatile__("sti");

  load_screen_driver();
  
  enter_shell();

  print("end of the kernel");
  __asm__ __volatile__("cli");
}
