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

void monitor_write_decimal(u32int n){
  if(n == 0){
    monitor_put('0');
    return;
  }

  s32int acc = n;
  char c[32];
  int i =0;

  while(acc > 0){
    c[i] = '0' + acc % 10;
    acc /= 10;
    i++;
  }

  c[i] = 0;

  char c2[32];

  c2[i--] = 0;
  int j = 0;

  while(i >= 0){
    c2[i--] = c[j++];
  }

  monitor_write(c2);
}

void monitor_write_hex(u32int n){
  s32int tmp;
  char noZeros = 1;
  monitor_write("0x");

  for(int i = 28; i > 0; i -= 4){
    tmp = (n >> i) & 0xF;

    if(tmp == 0 && noZeros != 0){
      continue;
    }

    if(tmp >= 0xA){
      noZeros = 0;
      monitor_put(tmp - 0xA + 'a');
    }else{
      noZeros = 0;
      monitor_put(tmp + '0');
    }
  }

  tmp = n & 0xF;

  if(tmp >= 0xA){
    monitor_put(tmp - 0xA + 'a');
  }else{
    monitor_put(tmp + '0');
  }
}
