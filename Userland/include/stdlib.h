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

#define TIME_SECONDS 0
#define TIME_MINUTES 2
#define TIME_HOURS 4

extern uint64_t syscall_wizard(uint64_t rax, uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t r8, uint64_t r9);
extern void syscall_register_dump();

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
uint64_t sysWrite(int fd, const char * buff, int length);
uint64_t sysRead(int fd, char * buff, int length);

void sysClear();
void sysDraw();
void sysConfigBitmap(int bitmapSize,uint32_t hexColor,int width);
void sysDrawBitmap(uint64_t x, uint64_t y,uint32_t *bitmap);
void sysFontSize(int size);
uint64_t sysGetScreenWidth();
uint64_t sysGetScreenHeight();

void sysSleep(int duration);
void sysBeep(int freq, int duration);
uint64_t sysTimeTicks();
uint64_t sysTime(int arg);
void sysRegisters(int fd);
char sysGetChar();
void sysPutChar(const char c);

void sysDrawTextAt(const char * str, int length, uint64_t x, uint64_t y, uint32_t hexColor);
uint8_t sysGetKeyEvent();

#endif