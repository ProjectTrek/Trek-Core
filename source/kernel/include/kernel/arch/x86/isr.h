#ifndef ISR_H
#define ISR_H

#include <kernel/types.h>

typedef struct registers{
  u32int ds;
  u32int edi, esi, ebp, esp, ebx, edx, ecx, eax;
  u32int interrupt_no, error_code;
  u32int eip, cs, eflags, useresp, ss;
} registers_t;

#endif
