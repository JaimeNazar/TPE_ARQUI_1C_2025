#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>
#include <styledConsole.h>

extern uint8_t get_keyboard_status();
extern char get_keyboard_output();

uint8_t pollKeyboard();
void keyPress();
char getNextKey(char* c);
char characterFilter(char c);
char canRead();
#endif