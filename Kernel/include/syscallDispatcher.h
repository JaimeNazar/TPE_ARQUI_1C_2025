#ifndef SYSCALLDISPATCHER_H
#define SYSCALLDISPATCHER_H

#include <stdint.h>
#include <keyboard.h>
#include <videoDriver.h>
#include <soundDriver.h>
#include <stdarg.h>

#define ID_WRITE 0
#define ID_READ 1
#define ID_CLEARBUFFER 2
#define ID_DRAWSCREEN  3
#define ID_TIMETICKS 4
#define ID_SLEEP 5
#define ID_TIME 6
#define ID_BEEP 7
#define ID_GETKEY 8
#define ID_DRAWBITMAP 9
#define ID_CONFIGBITMAP 10
#define ID_DUMP_REGS 11

#define COLOR_WHITE 0xFFFFFFFF
#define COLOR_AMBER 0x00FFBF00

int write(int fd, const char * buff, int length);
int read(int fd, char * buff, int length);
uint64_t syscallDispatcher(uint64_t rax, ...);
char saveKey();
char getNextKey(char* c);

#endif