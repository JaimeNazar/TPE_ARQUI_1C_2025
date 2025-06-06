#ifndef PONGIS_H
#define PONGIS_H

#include <stdint.h>
#include "pongisUtils.h"

// Keycode + KeyRelease = scancode for that key release
#define KEYRELEASE 0x80

// Scancodes
#define KEYPRESS_W 0x11
#define KEYPRESS_S 0x1F
#define KEYPRESS_A 0x1E
#define KEYPRESS_D 0x20

#define KEYPRESS_I 0x17
#define KEYPRESS_K 0x25
#define KEYPRESS_J 0x24
#define KEYPRESS_L 0x26

#define KEYPRESS_BACKSPACE 0x0E

#define BREAK_KEY(c)  ((c) + KEYRELEASE)

void drawBall();
void play(void);
void pongis(int playerCount);

#endif // PONGIS_H