#ifndef _TIME_H_
#define _TIME_H_
#include <stdint.h>

typedef struct
{
    uint8_t seconds;
    uint8_t minutes;
    int8_t hours;
    uint16_t year;
    uint8_t month;
    uint8_t day;
} timeData;

extern uint8_t rtc(uint8_t selection);

void timer_handler();
int ticks_elapsed();
int seconds_elapsed();
void getTime(timeData *data);
void sleep(uint64_t ticks);



#endif
