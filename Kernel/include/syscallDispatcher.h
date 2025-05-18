#ifndef SYSCALLDISPATCHER_H
#define SYSCALLDISPATCHER_H

#include <stdint.h>
#include <keyboard.h>
#include <naiveConsole.h>
#include <stdarg.h>

int write(int fd, const char * buff, int length);
int read(int fd, char * buff, int length);
void syscallDispatcher(uint64_t rax, ...);

#endif