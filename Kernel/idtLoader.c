#include <idtLoader.h>

#pragma pack(push)		/* Push the current alignment */
#pragma pack (1) 		  /* Align the following structures to 1 byte */

/* Interrupt descriptor */
typedef struct {
    uint16_t offset_l, selector;
    uint8_t cero, access;
  	uint16_t offset_m;
  	uint32_t offset_h, other_cero;
} DESCR_INT;

#pragma pack(pop)		/* Restore the current alignment */

DESCR_INT * idt = (DESCR_INT *) 0;	//IDT with 255 entries

static void setup_IDT_entry (int index, uint64_t offset) {
  idt[index].selector = 0x08;
  idt[index].offset_l = offset & 0xFFFF;
  idt[index].offset_m = (offset >> 16) & 0xFFFF;
  idt[index].offset_h = (offset >> 32) & 0xFFFFFFFF;
  idt[index].access = ACS_INT;
  idt[index].cero = 0;
  idt[index].other_cero = (uint64_t) 0;
}

void load_idt() {

  // Load interrupt rountines to IDT
  setup_IDT_entry (0x20, (uint64_t)&_irq00Handler); // Timer tick
  setup_IDT_entry (0x21, (uint64_t)&_irq01Handler); // Keyboard
  setup_IDT_entry (0x80, (uint64_t)&_syscallHandler);  // Syscall 
  setup_IDT_entry (0x06, (uint64_t)&_exception06Handler);  // Invalid op code
  setup_IDT_entry (0x00, (uint64_t)&_exception0Handler);  // Cero division

	// Allow only keyboard and timer tick interrupts from PIC
	picMasterMask(0xFC); 
	picSlaveMask(0xFF);
        
	_sti();
}
