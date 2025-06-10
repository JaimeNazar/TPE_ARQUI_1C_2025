#include <soundDriver.h>

void soundPlay(uint32_t freq) {
    uint16_t divisor = (uint16_t)(PIT_FREQ / freq);

    // Setup PIT channel 2
    outb(0x43, 0xB6);                   //https://wiki.osdev.org/Programmable_Interval_Timer razonamiento de 0xB6
    outb(0x42, divisor & 0xFF);         
    outb(0x42, (divisor >> 8) & 0xFF);

    // Enable the speaker (bits 0 and 1 from port 0x61)
    uint8_t tmp = inb(0x61);
  	if (tmp != (tmp | 3)) 
 		outb(0x61, tmp | 3);
}

void soundStop() {
    uint8_t tmp = inb(0x61);
    outb(0x61, tmp & 0xFC);
}

static void wait (uint32_t count) {
    uint32_t end = ticks_elapsed() + count;
    while (ticks_elapsed()  < end);
}

void bell(uint32_t frequency, uint32_t duration) {
    soundPlay(frequency);
    wait(duration);
    soundStop();
}