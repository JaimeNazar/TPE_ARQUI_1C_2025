#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <stdlib.h>
#include <miniShell.h>


#define COMMANDS 5

char **getCommandList();
char **getCommandListDescription();
void commandHandler(char* command);
#endif
