#ifndef GDT_H
#define GDT_H

#include <kernel/types.h>

struct gdt_entry_struct{
  u16int limit_low;
  u16int base_low;
  u8int base_middle;
  u8int access;
  u8int granularity;
  u8int base_high;
} __attribute__((packed));

struct gdt_pointer_struct{
  u16int limit;
  u32int base;
} __attribute__((packed));

typedef struct gdt_entry_struct gdt_entry_t;
typedef struct gdt_pointer_struct gdt_pointer_t;

int init_gdt();
int init_idt();

#endif
