#ifndef MINISHELL_H
#define MINISHELL_H

#include <shellUtils.h>
#include <stdlib.h>
#include "../pongis/include/pongis.h"

#define MAX_ARGS 16

#define MIN_FONT_SIZE 8
#define UTC_OFFSET -3

void setFontSize(int size);

void shellInit();
void shellUpdate();
void helpCommand();
void clearCommand();
void sleepCommand(int duration);
void gameCommand(int players);
void timeCommand();
void beepCommand(int frequency, int duration);
void ticksCommand();
void echoCommand(char* arguments[MAX_ARGS], int cant);
void fontCommand(int size);
void testZeroCommand();
void invalidopcodeCommand();
void error();
void errorByArguments(char* command, int cant);
void errorInvalidArgument(char* argument);
#endif