#include <kernel/types.h>
#include <kernel/mem.h>

void* memset(void* dest, int value, int size){
  u8int* buffer = (u8int*)dest;

  for(int i = 0; i < size; i++){
    buffer[i] = (u8int)value;
  }

  return dest;
}

void* memcpy(void* restrict dest, const void* restrict source, int size){
  u8int* dst = (u8int*)dest;
  const u8int* src = (const u8int*)source;

  for(int i = 0; i < size; i++){
    dst[i] = src[i];
  }

  return dest;
}
