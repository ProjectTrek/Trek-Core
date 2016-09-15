#include <kernel/monitor.h>
#include <kernel/arch/x86/pit.h>
#include <kernel/types.h>

int kernel_early(struct multiboot *mboot_ptr){
  kernel_main(mboot_ptr);
}

int kernel_main(struct multiboot *mboot_ptr){
  monitor_clear();
  monitor_write("Hello world!\n");

  if(init_gdt()){
    monitor_write("[Success] GDT Initialized\n");
  }

  if(init_idt()){
    monitor_write("[Success] IDT Initialized\n");
  }

  if(init_timer(50)){
    monitor_write("[Success] Timer Initialized\n");
  }

  monitor_write("sweet");

  for(;;);
  return 0xDEADC0DE;
}
