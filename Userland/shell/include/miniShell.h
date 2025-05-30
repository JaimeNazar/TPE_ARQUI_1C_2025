#ifndef MINISHELL_H
#define MINISHELL_H

#include <shellUtils.h>
#include <stdlib.h>
#include "../../Wii Pong resort/Pongis.h"

#define SHELL_PROMPT "miniShell > "

void shellInit();
void shellUpdate();
void helpCommand();
void clearCommand();
void sleepCommand();
void gameCommand();
void timeCommand();
void beepCommand();
void ticksCommand();
void error();
#endif