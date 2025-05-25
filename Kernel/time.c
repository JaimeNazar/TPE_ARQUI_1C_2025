#include <time.h>
#define RTC_ADDRESS 0x70
#define RTC_DATA 0x71
#define RTC_SECONDS 0x00
#define RTC_MINUTES 0x02
#define RTC_HOURS 0x04
#define RTC_DAY 0x07
#define RTC_MONTH 0x08
#define RTC_YEAR 0x09


static unsigned long ticks = 0;

void timer_handler() {
	ticks++;
}

int ticks_elapsed() {
	return ticks;
}

int seconds_elapsed() {
	return ticks / 18;
}

void getTime(timeData *data) {
	
	uint8_t RTCNeeded[] = {RTC_SECONDS, RTC_MINUTES, RTC_HOURS, RTC_DAY, RTC_MONTH, RTC_YEAR};
	uint8_t Values[6];
	for (int i = 0; i < 6; i++) {
		Values[i] = rtc(RTCNeeded[i]);
	}

	data->seconds = Values[0];
	data->minutes = Values[1];
	data->hours = Values[2];
	data->day = Values[3];
	data->month = Values[4];
	data->year = Values[5];
}
void sleep(uint64_t ticks) {
    uint64_t end = ticks_elapsed() + ticks;

    while (ticks_elapsed() < end) {
        
    }

}

