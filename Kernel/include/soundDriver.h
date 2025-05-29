#ifndef SOUNDDRIVER_H
#define SOUNDDRIVER_H

#include <stdint.h>

void soundPlay(uint32_t freq);
void soundStop(void);


void bell(uint32_t frequency, uint32_t duration);
#endif