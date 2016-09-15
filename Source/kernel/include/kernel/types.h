#ifndef TYPES_H
#define TYPES_H

typedef unsigned int u32int;
typedef unsigned short u16int;
typedef unsigned char u8int;
typedef unsigned long long u64int;

typedef signed int s32int;
typedef signed short s16int;
typedef signed char s8int;
typedef signed long long s64int;

#define asmv(x) __asm__ __volatile__(x)

#endif
