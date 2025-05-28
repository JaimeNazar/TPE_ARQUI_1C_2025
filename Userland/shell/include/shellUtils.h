#ifndef SHELL_UTILS_H
#define SHELL_UTILS_H

#include <stdlib.h>
#include <miniShell.h>


#define COMMANDS 5

char **getCommandList();
char **getCommandListDescription();
void commandHandler(char* command);
#endif
