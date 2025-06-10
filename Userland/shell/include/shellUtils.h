#ifndef SHELL_UTILS_H
#define SHELL_UTILS_H

#include <stdlib.h>
#include <miniShell.h>

#define COMMANDS 12
#define MAX_ARGS 16

char **getCommandList();
char **getCommandListDescription();
void commandHandler(char* command, int length);
#endif
