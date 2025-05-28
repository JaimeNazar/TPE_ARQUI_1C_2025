#ifndef SYSCALLDISPATCHER_H
#define SYSCALLDISPATCHER_H

#include <stdint.h>
#include <keyboard.h>
#include <videoDriver.h>
#include <stdarg.h>

int write(int fd, const char * buff, int length);
int read(int fd, char * buff, int length);
uint64_t syscallDispatcher(uint64_t rax, ...);

#endif