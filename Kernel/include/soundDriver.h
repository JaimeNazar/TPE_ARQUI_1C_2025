#ifndef SOUNDDRIVER_H
#define SOUNDDRIVER_H

#include <stdint.h>

void sound_play(uint32_t freq);
void sound_stop(void);


void bell(uint32_t frequency, uint32_t duration);
#endif