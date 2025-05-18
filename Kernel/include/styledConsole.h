#ifndef STYLED_CONSOLE_H
#define STYLED_CONSOLE_H

#include <stdint.h>

void scPrint(const char * string, uint8_t color);
void scPrintChar(char character, uint8_t color);
void scNewline();
void scPrintDec(uint64_t value, uint8_t color);
void scPrintHex(uint64_t value, uint8_t color);
void scPrintBin(uint64_t value, uint8_t color);
void scPrintBase(uint64_t value, uint32_t base, uint8_t color);
void scClear();
void scScrollDown();
void scPrintCharAt(char character, uint8_t color, int x, int y);

#endif
