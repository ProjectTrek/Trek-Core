#include <kernel/types.h>
#include <kernel/monitor.h>

u16int *monitor_video_memory = (u32int*)0xB8000;
u32int monitor_cursorX, monitor_cursorY;

static void move_cursor(){
  u16int cursorLocation = monitor_cursorY * 80 + monitor_cursorX;

  outb(0x3D4, 14);
  outb(0x3D5, cursorLocation >> 8);
  outb(0x3D4, 15);
  outb(0x3D5, cursorLocation);
}

static void scroll(){
  u8int attributeByte = (0 << 4) | (15 & 0x0F);
  u16int blank = 0x20 | (attributeByte << 8);

  if(monitor_cursorY >= 25){
    int i;
    for(i = 0*80; i < 24*80; i++){
      monitor_video_memory[i] = monitor_video_memory[i+80];
    }

    for(i = 24*80; i < 25*80; i++){
      monitor_video_memory[i] = blank;
    }

    monitor_cursorY = 24;
  }
}

void monitor_put(char c){
  u8int backColor = 0;
  u8int foreColor = 15;

  u8int attributeByte = (backColor << 4) | (foreColor & 0x0F);
  u16int attribute = attributeByte << 8;
  u16int *location;

  if(c == 0x08 && monitor_cursorX){
    monitor_cursorX--;
  }else if(c == 0x09){
    monitor_cursorX = (monitor_cursorX + 4) & ~(4 - 1);
  }else if(c == '\r'){
    monitor_cursorX = 0;
  }else if(c == '\n'){
    monitor_cursorX = 0;
    monitor_cursorY++;
  }else if(c >= ' '){
    location = monitor_video_memory + (monitor_cursorY * 80 + monitor_cursorX);

    *location = c | attribute;
    monitor_cursorX++;
  }

  if(monitor_cursorX >= 80){
    monitor_cursorX = 0;
    monitor_cursorY++;
  }

  scroll();
  move_cursor();
}

void monitor_write(char *c){
  int i =0;

  while(c[i]){
    monitor_put(c[i++]);
  }
}

void monitor_clear(){
  int i;
  u8int attributeByte = (0 << 4) | (15 & 0x0F);
  u16int blank = 0x20 | (attributeByte << 8);

  for(i = 0*80; i < 25*80; i++){
    monitor_video_memory[i] = blank;
  }
}
