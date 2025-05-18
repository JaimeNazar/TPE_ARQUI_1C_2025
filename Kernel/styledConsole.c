#include <styledConsole.h>

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base);

static char buffer[64] = { '0' };
static uint8_t * const video = (uint8_t*)0xB8000;
static uint8_t * currentVideo = (uint8_t*)0xB8000;
static const uint32_t width = 80;
static const uint32_t height = 25 ;

void scPrint(const char * string, uint8_t color)
{
	int i;

	for (i = 0; string[i] != 0; i++)
		scPrintChar(string[i], color);
}

void scScrollDown() {

	int width_char = width*2;

	for (int i = 0; i < height - 1; i++) {
		for (int j = 0; j < width_char; j++) {
			video[(i * width_char) + j] = video[((i+1) * width_char) + j];
		}
	}

	for (int i = 0; i < width_char - 1; i++) {
		video[width_char*height + i] = ' ';
	}

	currentVideo = video + (height-2) * width_char;
}

void scPrintChar(char character, uint8_t color)
{

	if (currentVideo >= video + (height-1) * width*2)
		scScrollDown();

	*currentVideo = character;
	currentVideo++;
	*currentVideo = color;
	currentVideo++;
}

void scPrintCharAt(char character, uint8_t color, int x, int y)
{
	if (currentVideo >= video + (height-1) * width*2)
		scScrollDown();

	video[y*width*2 + x*2] = character;
	video[y*width*2 + x*2 + 1] = color;
}

void scNewline()
{
	do
	{
		scPrintChar(' ', 0x00);
	}
	while((uint64_t)(currentVideo - video) % (width * 2) != 0);
}

void scPrintDec(uint64_t value, uint8_t color)
{
	scPrintBase(value, 10, color);
}

void scPrintHex(uint64_t value, uint8_t color)
{
	scPrintBase(value, 16, color);
}

void scPrintBin(uint64_t value, uint8_t color)
{
	scPrintBase(value, 2, color);
}

void scPrintBase(uint64_t value, uint32_t base, uint8_t color)
{
    uintToBase(value, buffer, base);
    scPrint(buffer, color);
}

void scClear()
{
	int i;

	for (i = 0; i < height * width*2; i++) {
		video[i] = 0;
	}

	currentVideo = video;
}

static uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base)
{
	char *p = buffer;
	char *p1, *p2;
	uint32_t digits = 0;

	//Calculate characters for each digit
	do
	{
		uint32_t remainder = value % base;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	}
	while (value /= base);

	// Terminate string in buffer.
	*p = 0;

	//Reverse string in buffer.
	p1 = buffer;
	p2 = p - 1;
	while (p1 < p2)
	{
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return digits;
}
