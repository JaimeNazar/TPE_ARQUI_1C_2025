#ifndef VIDEO_DRIVER_H
#define VIDEO_DRIVER_H

#include <stdint.h>
#include <lib.h>

#define MAX_WIDTH 1920
#define MAX_HEIGHT 1080

#define DEFAULT_FONT_SIZE 8 // 8 pixels wide
#define CHAR_BITMAP_WIDTH 8
#define CHAR_BITMAP_HEIGHT 16

#define DIRTY_RECTANGLE_SIZE 64
#define DIRTY_RECTANGLE_SIZE_SHIFT 6
#define DIRTY_HEIGHT (MAX_HEIGHT/DIRTY_RECTANGLE_SIZE)
#define DIRTY_WIDTH (MAX_WIDTH/DIRTY_RECTANGLE_SIZE)

/* Gets basic screen information */
void videoInitialize();

/* Places pixel in the frame buffer */
void videoPutPixel(uint32_t hexColor, uint64_t x, uint64_t y);

/* Draws a square, the top-left corner has the position specified */
void videoDrawSquare(uint64_t x, uint64_t y, uint64_t size, uint32_t hexColor);

/* Draw buffer, only dirty rectangles */
void videoDrawScreen();

/* Clear the buffer, set all its bytes to 0 */
void videoClearBuffer();

/* Draws text starting at provided coordinates(top-left corner of text) */
void videoDrawTextAt(const char * str, int length, uint64_t x, uint64_t y, uint32_t hexColor);

int videoGetWidth();
int videoGetHeight();

// --- Bitmap utils ---

/* Set bitmap config, allows to draw multiple bitmaps with the same config */
void videoDrawBitMap(uint64_t x, uint64_t y,uint32_t *bitmap);
void videoConfigBitmap(int size,uint32_t hexColor,int width);

// --- Text utils ---

/* Draw char using text grid */
void videoDrawChar(char c, uint32_t hexColor);

/* Prints a string continiously on screen using a grid */
void videoPrintText(const char * str, int length, uint32_t hexColor);
void videoSetFontsize(uint8_t size);
void videoNextLine();
int videoCanErase();
#endif