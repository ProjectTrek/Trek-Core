#include <kernel/types.h>
#include <kernel/arch/x86/io.h>

void outb(u16int port, u8int value){
  __asm__ __volatile__("outb %1, %0" : : "dN" (port), "a" (value));
}

u8int inb(u16int port){
  u8int returnValue;

  asmv("inb %1, %0" : "=a" (returnValue) : "dN" (port));

  return returnValue;
}

u16int inw(u16int port){
  u16int returnValue;

  asmv("inw %1, %0" : "=a" (returnValue) : "dN" (port));

  return returnValue;
}
