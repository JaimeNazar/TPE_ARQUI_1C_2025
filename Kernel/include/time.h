#ifndef _TIME_H_
#define _TIME_H_

#include <stdint.h>

#define PIT_FREQ 1193180

typedef struct
{
    uint8_t seconds;
    uint8_t minutes;
    int8_t hours;
    uint16_t year;
    uint8_t month;
    uint8_t day;
} timeData;

extern void outb(uint16_t port, uint8_t value);
extern uint8_t inb(uint16_t port);

extern uint8_t rtc(uint8_t selection);

void timer_set(int ms);
void timer_handler();
int ticks_elapsed();
int seconds_elapsed();
void getTime(timeData *data);
void sleep(uint64_t ticks);



#endif
