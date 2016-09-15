#ifndef MONITOR_H
#define MONITOR_H

#include <kernel/types.h>

void monitor_put(char c);
void monitor_clear();
void monitor_write(char *c);
void monitor_write_decimal(u32int number);
void monitor_write_hex(u32int number);

#endif
