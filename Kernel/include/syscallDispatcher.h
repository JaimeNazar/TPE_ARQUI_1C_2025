#ifndef SYSCALLDISPATCHER_H
#define SYSCALLDISPATCHER_H

#include <stdint.h>
#include <stdarg.h>

#include <keyboard.h>
#include <videoDriver.h>
#include <soundDriver.h>
#include <time.h>
#include <registers.h>
#include <interrupts.h>

// Syscalls IDs
enum{
    ID_WRITE=0,
    ID_READ,
    ID_CLEAR_BUFFER,
    ID_DRAW_SCREEN,
    ID_DRAW_BITMAP,
    ID_CONFIG_BITMAP,
    ID_FONT_SIZE,
    ID_DRAW_TEXT,
    ID_VIDEO_WIDTH,
    ID_VIDEO_HEIGHT,
    ID_TIME_TICKS,
    ID_SLEEP,
    ID_TIME,
    ID_BEEP,
    ID_GET_CHAR,
    ID_PUT_CHAR,
    ID_GET_KEY_EVENT,
    ID_DUMP_REGS,
};

#define COLOR_WHITE 0xFFFFFFFF
#define COLOR_AMBER 0x00FFBF00

int syscallWrite(int fd, const char * buff, int length);
int syscallRead(int fd, char * buff, int length);
uint64_t syscallDispatcher(uint64_t rax, ...);

#endif