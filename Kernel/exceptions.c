#include <stdint.h>
#include <syscallDispatcher.h>
#include <registers.h>
#include <interrupts.h>

#include <videoDriver.h>

#define ZERO_EXCEPTION_ID 0
#define UNDEF_OP_CODE_EXCEPTION_ID 6 //https://wiki.osdev.org/Interrupt_Descriptor_Table
#define GENERAL_REGISTERS_COUNT 15 
#define SPECIAL_REGISTERS_COUNT 5 
#define MSG_LENGTH 8

const char * generalRegisterString[] = {                               //todos con len = 8
	"RAX:    ", "RBX:    ", "RCX:    ", "RDX:    ",
	"RBP:    ", "RDI:    ", "RSI:    ",
	"R8:     ", "R9:     ", "R10:     ", "R11:    ", "R12:    ", "R13:    ", "R14:    ", "R15:    "
};

const char * specialRegisterString[] = {
	"RIP:    ", "CS:     ", "RFLAGS: ", "RSP:    ", "SS:     "
};

static int strlen(char* str) {
	int count = 0;
	while (str[count++] != 0);
	return count;
}

static void printError(char * str) {
	write(2, str, strlen(str));
}

uint64_t* spec_reg;

// TODO: End up using the getChar method from sycallDispatcher
static void printHex(uint64_t value) {
	do
	{
		uint32_t remainder = value % 16;
		drawChar((remainder < 10) ? remainder + '0' : remainder + 'A' - 10, 0xFFFFFFFF);
	}
	while (value /= 16);
}

/* Prints a map, in this case, used the registers mapped to their values */
static void printMap(const char** keys, uint64_t* values, int lenght)  {
	for (int i = 0 ; i < lenght; i++) {
		write(2, keys[i], MSG_LENGTH);
		printHex(values[i]);
		write(2, "\n", 1);
	}
}

static void exceptionMsg(const char* msg, const int len) {
	
	printError("Excepcion: ");
	write(2, msg, len);
	write(2, "\n", 1);

	printError("Instruction Pointer: ");
	printHex(get_rip());
	write(2, "\n", 1);

	write(2, "Registers: ", 11);
	write(2, "\n", 1);

	// Print general purpose registers
	printMap(generalRegisterString, get_registers(), GENERAL_REGISTERS_COUNT);

	// Print special registers
	printMap(specialRegisterString, get_special_registers(), SPECIAL_REGISTERS_COUNT);


	drawScreen();
	
 // ACA DEBERIA DE VOLVER A LA SHELL SEGUN LA CONSIGNA DEL TPE, TODAVIA NO ESTA IMPLEMENTADO

}

static void zero_division() {
	_sti();	// Re-enable hardware interrupts
	exceptionMsg("Division by zero", 17);
}


static void undefined_op_code() {
	_sti();
	exceptionMsg("Undefined operation code", 25);
}

void exceptionDispatcher(int exception) {
	
	if (exception == ZERO_EXCEPTION_ID)
		zero_division();
	else if (exception == UNDEF_OP_CODE_EXCEPTION_ID) {}
	
}

