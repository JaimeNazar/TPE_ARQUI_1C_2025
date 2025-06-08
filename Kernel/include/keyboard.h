#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>
#include <styledConsole.h>

#define BUFFER_SIZE 5

#define ESC 0x01
#define ENTER 28
#define BACKSPACE 14
#define TAB 15	
#define L_SHIFT_PRESS 0x2A
#define R_SHIFT_PRESS 0x36
#define CAPS_LOCK_PRESS 0x3A
#define MAX_PRESS_KEY 0x70

#define KEYS_START 0
#define KEYS_END 58

#define KEYRELEASE 0x80
#define BREAK_KEY(c)  ((c) + KEYRELEASE)

extern uint8_t get_keyboard_status();
extern char get_keyboard_output();

uint8_t keyboardPoll();
uint8_t keyboardGetKeyEvent();
char keyboardGetChar();
char keyboardHasEvent();
void keyboardSaveEvent();
#endif