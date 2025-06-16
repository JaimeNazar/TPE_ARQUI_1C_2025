#include <time.h>
#include <stdint.h>
#include <keyboard.h>
#include <interrupts.h>

static void int_20() {
	timer_handler();
}

static void int_21() { 
	_registers_backup();
	keyboardSaveEvent();
}

void irqDispatcher(uint64_t irq) {
	switch (irq) {		// IRQ number to call
		case 0:
			int_20();	// Timer tick
			break;
		case 1:
			int_21();	// Keyboard interrupt
			break;
	}
	return;
}
