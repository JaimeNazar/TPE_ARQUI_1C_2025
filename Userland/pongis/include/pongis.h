#ifndef PONGIS_H
#define PONGIS_H

#include <stdint.h>
#include <pongisUtils.h>

#define MAXVEL 50
#define GAME_OVER 1
#define WIN 2
#define MAX_STR_LENGTH 32

#define B 0x000000
#define G 0x00FF00
#define R 0xFF0000
#define Y 0xFFFF00
#define C 0x00FFFF
#define M 0xFF00FF
#define P 0x800080
#define GRAY 0x808080
#define DG 0x404040
#define LG 0xC0C0C0
#define BLUE 0x0000FF
#define AQUA 0x00FFFF
#define W 0xFFFFFF

#define DRAG 0.9f
#define VELOCITY_INCREASE 3
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

#define KEYPRESS_R 0x13

#define KEYPRESS_BACKSPACE 0x0E

#define BREAK_KEY(c)  ((c) + KEYRELEASE)

// Constant
#define INITIAL_LIVES 5

void pongis(int playerCount);

#endif // PONGIS_H