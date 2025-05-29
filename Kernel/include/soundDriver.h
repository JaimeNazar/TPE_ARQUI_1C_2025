#ifndef SOUNDDRIVER_H
#define SOUNDDRIVER_H

#include <stdint.h>

#define PIT_FREQ 1193180

//funciones implementadas en libasm
extern void outb(uint16_t port, uint8_t value);
extern uint8_t inb(uint16_t port);

void soundPlay(uint32_t freq);
void soundStop(void);

void bell(uint32_t frequency, uint32_t duration);

#endif