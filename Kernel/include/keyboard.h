#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>
#include <styledConsole.h>

#define BUFFER_SIZE 5


#define KEYS 58
#define ESC 0x01
#define ENTER 28
#define BACKSPACE 14
#define TAB 15	
#define L_SHIFT_PRESS 0x2A
#define L_SHIFT_RELEASE 0xAA
#define R_SHIFT_PRESS 0x36
#define R_SHIFT_RELEASE 0xB6
#define CAPS_LOCK_PRESS 0x3A
#define MAX_PRESS_KEY 0x70


extern uint8_t get_keyboard_status();
extern char get_keyboard_output();

uint8_t pollKeyboard();
void keyPress();

char canRead();
char getNextKey(char* c);
char saveKey();
#endif