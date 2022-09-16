#include "timer.h"
#include "../cpu/isr.h"
#include "screen.h"
#include "low_level.h"
#include "../cpu/task.h"

u32 tick = 0;

static void timer_callback(registers_t regs)
{
    tick++;
    if(tick % 1000 == 0){
        print("Switch task");
        switch_task();
    }


}

void init_timer(u32 frequency)
{
    register_interrupt_handler(IRQ0, timer_callback);

    u32 divisor = 1193180 / frequency;

    port_byte_out(0x43, 0x36);

    u8 l = (u8)(divisor & 0xFF);
    u8 h = (u8)((divisor>>8) & 0xFF);

    port_byte_out(0x40, l);
    port_byte_out(0x40, h);
}