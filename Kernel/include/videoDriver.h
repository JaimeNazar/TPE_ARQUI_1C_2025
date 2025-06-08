#ifndef VIDEO_DRIVER_H
#define VIDEO_DRIVER_H

#include <stdint.h>
#include <lib.h>

#define MAX_WIDTH 1920
#define MAX_HEIGHT 1080

#define DEFAULT_FONT_SIZE 8 // 8 pixels wide
#define CHAR_BITMAP_WIDTH 8
#define CHAR_BITMAP_HEIGHT 16


void videoInitialize();
void videoPutPixel(uint32_t hexColor, uint64_t x, uint64_t y);

void videoDrawSquare(uint64_t x, uint64_t y, uint64_t size, uint32_t hexColor);
void videoDrawScreen();
void videoClearBuffer();
void videoDrawTextAt(const char * str, int length, uint64_t x, uint64_t y, uint32_t hexColor);

int videoGetWidth();
int videoGetHeight();

// Bitmap utils
void videoDrawBitMap(uint64_t x, uint64_t y,uint32_t *bitmap);
void videoConfigBitmap(int size,uint32_t hexColor,int width);

// Text utils
void videoDrawChar(char c, uint32_t hexColor);
void videoPrintText(const char * str, int length, uint32_t hexColor);
void videoSetFontsize(uint8_t size);
void videoNextLine();
int videoCanErase();
#endif