#ifndef STDLIB_H
#define STDLIB_H

#include <stdint.h>

extern uint64_t syscall_wizard(uint64_t rax, uint64_t rdi, uint64_t rsi, uint64_t rdx);

// Syscalls
uint64_t sysWrite(int fd, char * buff, int length);
uint64_t sysRead(int fd, char * buff, int length);
uint64_t sysTimeTicks();
void sysClear();
void sysDraw();
void sysTime(int code);
int strcmp(char* str1, char* str2);
// Utils
int strlen(char* str);

#endif