#include <kernel/monitor.h>
#include <kernel/types.h>

int kernel_early(struct multiboot *mboot_ptr){
  kernel_main(mboot_ptr);
}

int kernel_main(struct multiboot *mboot_ptr){
  monitor_clear();
  monitor_write("Hello world!\n");

  init_gdt();
  init_idt();

  asmv("int $0x3");
  asmv("int $0x4");

  monitor_write("sweet");
  for(;;);
  return 0xDEADC0DE;
}
