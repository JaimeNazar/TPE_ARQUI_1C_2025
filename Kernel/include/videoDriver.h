#ifndef VIDEO_DRIVER_H
#define VIDEO_DRIVER_H

#include <stdint.h>
#include <lib.h>

void videoInitialize();
void putPixel(uint32_t hexColor, uint64_t x, uint64_t y);
void drawSquare(uint64_t x, uint64_t y, uint64_t size, uint32_t hexColor);
void drawScreen();
void clearBuffer();
void drawChar(char c, uint32_t hexColor);
void printText(char * str, int length, uint32_t hexColor);
void videoSetFontsize(uint8_t size);

#endif