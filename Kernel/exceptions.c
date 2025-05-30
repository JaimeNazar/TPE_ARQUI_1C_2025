#include <stdint.h>
#include <syscallDispatcher.h>
#include <registers.h>
#include <interrupts.h>

#define ZERO_EXCEPTION_ID 0
#define UNDEF_OP_CODE_EXCEPTION_ID 6 //https://wiki.osdev.org/Interrupt_Descriptor_Table
#define GENERAL_REGISTERS 15 
#define MSG_LENGTH 8

static int strlen(char* str) {
	int count = 0;
	while (str[count++] != 0);
	return count;
}

static void printError(char * str) {
	write(2, str, strlen(str));
}

static void printHex(uint64_t value) {
	do
	{
		uint32_t remainder = value % 16;
		write(2, (remainder < 10) ? remainder + '0' : remainder + 'A' - 10, 1);
	}
	while (value /= 16);
}

static void exceptionMsg(const char* msg, const int len) {
	
	printError("Excepcion: ");
	write(2, msg, len);
	write(2, "\n", 1);

	printError("Instruction Pointer: ");
	write(2, get_rip(), len);
	write(2, "\n", 1);


	drawScreen();
	const char * registerString[] = {                               //todos con len = 8
		"RAX:    ", "RBX:    ", "RCX:    ", "RDX:    ",
		"RBP:    ", "RDI:    ", "RSI:    ",
		"R8:     ", "R9:     ", "R10:     ", "R11:    ", "R12:    ", "R13:    ", "R14:    ", "R15:    ",
		"RIP:    ", "CS:     ", "RFLAGS: ", "RSP:    ", "SS:     "
	};

	const uint64_t * registers = get_registers();


	write(2, "Registers: ", 11);
	write(2, "\n", 1);
	// Imprimir registros
	for (int i = 0; i < GENERAL_REGISTERS; i++) {
		write(2, registerString[i], MSG_LENGTH);
		printHex(registers[i]);
		write(2, "\n", 1);

	}

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

