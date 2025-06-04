#ifndef STDLIB_H
#define STDLIB_H

#include <stdint.h>
#include <stdarg.h>

#define STDOUT 0x1
#define STDIN 0x1

#define NO_ARG 0x0

#define BASE_TEN 10

#define MAX_CMD_LEN 128
#define MAX_ARGS 16

// Syscalls IDs
#define ID_WRITE 0
#define ID_READ 1
#define ID_CLEARBUFFER 2
#define ID_DRAWSCREEN 3
#define ID_TIMETICKS 4
#define ID_SLEEP 5
#define ID_TIME 6
#define ID_GETKEY 8
#define ID_BEEP 7
#define ID_DRAWBITMAP 9
#define ID_CONFIGBITMAP 10
#define ID_DUMPREGS 11
#define ID_FONT_SIZE 12

#define TIME_SECONDS 0
#define TIME_MINUTES 2
#define TIME_HOURS 4

extern uint64_t syscall_wizard(uint64_t rax, uint64_t rdi, uint64_t rsi, uint64_t rdx);

// Utils
int strcmp(char* str1, char* str2, int length1, int length2);
int strlen(char* str);
void intToStr(int value, char *str);
void floatToStr(float value, char *str, int decimals);
int strToInt(const char *str);
float strToFloat(const char *str);

void printf(char* ftm, ...);
void scanf(char* ftm, ...);

int getSeconds();
int getMinutes();
int getHours();

// Syscalls
uint64_t sysWrite(int fd, char * buff, int length);
uint64_t sysRead(int fd, char * buff, int length);
uint64_t sysTimeTicks();
void sysClear();
void sysDraw();
uint64_t sysTime(int arg);
void sysConfigBitmap(int bitmapSize,uint32_t hexColor,int width);
void sysDrawBitmap(uint64_t x, uint64_t y,uint32_t *bitmap);
void sysRegisters(int fd);
char sysKey();
void sysFontSize(int size);

#endif