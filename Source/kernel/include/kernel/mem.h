#ifndef MEM_H
#define MEM_H

void* memset(void* dest, int value, int size);
void* memcpy(void* restrict dest, const void* restrict source, int size);

#endif
