#include <kernel/types.h>
#include <kernel/monitor.h>
#include <kernel/arch/x86/isr.h>

isr_t interrupt_handlers[256];

void isr_handler(registers_t *regs){
  if(interrupt_handlers[regs->interrupt_no] != 0){
    isr_t handler = interrupt_handlers[regs->interrupt_no];
    handler(regs);
  }else{
    monitor_write("\n\nUnhandled interrupt: ");
    monitor_write_decimal(regs->interrupt_no);
    monitor_put('\n');
  }

  ENABLE_INTERRUPTS();
}

void irq_handler(registers_t *regs){
  if(regs->interrupt_no >= 40){
    outb(0xA0, 0x20);
  }

  outb(0x20, 0x20);

  if(interrupt_handlers[regs->interrupt_no] != 0){
    isr_t handler = interrupt_handlers[regs->interrupt_no];
    handler(regs);
  }

  ENABLE_INTERRUPTS();
}

void register_interrupt_handler(u8int n, isr_t handler){
  interrupt_handlers[n] = handler;
}
