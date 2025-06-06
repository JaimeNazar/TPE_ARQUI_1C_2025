#include <time.h>
#include <stdint.h>
#include <keyboard.h>

static void int_20();
static void int_21();
static void syscallDispatcher();

void irqDispatcher(uint64_t irq) {
	switch (irq) {	// IRQ number to call
		case 0:
			int_20();	// Timer tick
			break;
		case 1:
			int_21();	// Keyboard interrupt
			break;
	}
	return;
}

void int_20() {
	timer_handler();
}

void int_21() { 
	keyboardSaveEvent();
}
