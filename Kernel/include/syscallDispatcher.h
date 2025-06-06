#ifndef SYSCALLDISPATCHER_H
#define SYSCALLDISPATCHER_H

#include <stdint.h>
#include <keyboard.h>
#include <videoDriver.h>
#include <soundDriver.h>
#include <stdarg.h>

// Syscalls IDs
typedef enum{
    ID_WRITE=0,
    ID_READ,
    ID_CLEARBUFFER,
    ID_DRAWSCREEN,
    ID_TIMETICKS,
    ID_SLEEP,
    ID_TIME,
    ID_BEEP,
    ID_GETKEY,
    ID_DRAWBITMAP,
    ID_CONFIGBITMAP,
    ID_DUMP_REGS,
    ID_FONT_SIZE,
    ID_DRAWTEXT
};

#define COLOR_WHITE 0xFFFFFFFF
#define COLOR_AMBER 0x00FFBF00

int write(int fd, const char * buff, int length);
int read(int fd, char * buff, int length);
uint64_t syscallDispatcher(uint64_t rax, ...);
char saveKey();
char getNextKey(char* c);
void videoSetFontsize(uint8_t size);

#endif