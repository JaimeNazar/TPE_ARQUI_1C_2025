#ifndef STDLIB_H
#define STDLIB_H

#include <stdint.h>
#include <stdarg.h>

static char bufferBase[64] = { '0' };

extern uint64_t syscall_wizard(uint64_t rax, uint64_t rdi, uint64_t rsi, uint64_t rdx);

// Utils
int strcmp(char* str1, char* str2, int length1, int length2);
int strlen(char* str);
void intToStr(int value, char *str);

void printf(char* ftm, ...);
char * stoi(int value);

// Syscalls
uint64_t sysWrite(int fd, char * buff, int length);
uint64_t sysRead(int fd, char * buff, int length);
uint64_t sysTimeTicks();
void sysClear();
void sysDraw();
void sysTime(int code);

#endif