#ifndef MINISHELL_H
#define MINISHELL_H
#include <interpreter.h>
#include <stdlib.h>


#define SHELL_PROMPT "miniShell > "

void shellInit();
void shellUpdate();
void helpCommand();
void clearCommand();
void echoCommand();
void gameCommand();
void timeCommand();
void error(char* command);
#endif