#include <kernel/types.h>
#include <kernel/monitor.h>
#include <kernel/arch/x86/isr.h>

void isr_handler(registers_t *regs){
  monitor_write("Recieved interrupt");
}
