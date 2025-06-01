#ifndef MINISHELL_H
#define MINISHELL_H

#include <shellUtils.h>
#include <stdlib.h>
#include <pongis.h>

#define SHELL_PROMPT "miniShell > "
#define MAX_ARGS 16


void shellInit();
void shellUpdate();
void helpCommand();
void clearCommand();
void sleepCommand(int duration);
void gameCommand();
void timeCommand();
void beepCommand(int frequency, int duration);
void ticksCommand();
void echoCommand(char* arguments[MAX_ARGS], int cant);
void error();
void errorByArguments(char* command, int cant);
void errorInvalidArgument(char* argument);
#endif