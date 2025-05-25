#include <soundDriver.h>
#include <stdint.h>
#include <time.h>

#define PIT_FREQ 1193180

//funciones implementadas en libasm
extern void outb(uint16_t port, uint8_t value);
extern uint8_t inb(uint16_t port);


void sound_play(uint32_t freq) {
    uint16_t divisor = (uint16_t)(PIT_FREQ / freq);

    // Configura el canal 2 del PIT
    outb(0x43, 0xB6);                   //https://wiki.osdev.org/Programmable_Interval_Timer razonamiento de 0xB6
    outb(0x42, divisor & 0xFF);         // Byte bajo
    outb(0x42, (divisor >> 8) & 0xFF);  // Byte alto

    // Habilita el speaker (bits 0 y 1 del puerto 0x61)
    uint8_t tmp = inb(0x61);
    outb(0x61, tmp | 3);
}

void sound_stop() {
    uint8_t tmp = inb(0x61);
    outb(0x61, tmp & 0xFC);
}


void wait (uint32_t count) {
    uint32_t end = ticks_elapsed() + count;
    while (ticks_elapsed()  < end);
}

void bell(uint32_t frequency, uint32_t duration) {
    sound_start(frequency);
    wait(duration);
    sound_stop();
}