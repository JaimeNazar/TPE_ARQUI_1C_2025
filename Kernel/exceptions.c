#include<stdint.h>
#include <syscallDispatcher.h>


#define ZERO_EXCEPTION_ID 0
#define UNDEF_OP_CODE_EXCEPTION_ID 6 //https://wiki.osdev.org/Interrupt_Descriptor_Table
#define CANT_REGISTERS 14 //POR AHORA CON LA FUNCION SON 14 PERO FALTAN LOS RAROS COMO RFLAGS, RSP, SS



static void zero_division();

void exceptionDispatcher(int exception) {
	if (exception == ZERO_EXCEPTION_ID)
		zero_division();
	else if (exception == UNDEF_OP_CODE_EXCEPTION_ID) {}
	
}


static void exceptionMsg(const char* msg, const int len) {
	
	write(2, "Excepcion: ", 11);
	write(2, msg, len);
	write(2, "\n", 1);


	write(2, "Instruction Pointer: ", 21);
	write(2, get_rip(), len);
	write(2, "\n", 1);


const char * registerString[] = {                               //todos con len = 8
    "RAX:    ", "RBX:    ", "RCX:    ", "RDX:    ",
    "RBP:    ", "RDI:    ", "RSI:    ",
    "R8:     ", "R9:     ", "R10:     ", "R11:    ", "R12:    ", "R13:    ", "R14:    ", "R15:    ",
    "RIP:    ", "CS:     ", "RFLAGS: ", "RSP:    ", "SS:     "
};
const uint64_t * registers = {1, 2, 3};	// FIX: lo deje asi para que compile
//const uint64_t * registers = getRegisters();


	write(2, "Registros: ", 11);
	write(2, "\n", 1);
	// Imprimir registros
	for (int i = 0; i < CANT_REGISTERS; i++) {
		write(2, registerString[i], 8);
		write(2, registers[i], 8); // QUE LONGITUD DEBERIAMOS DE PONER ACA??
		write(2, "\n", 1);

	}

	
 // ACA DEBERIA DE VOLVER A LA SHELL SEGUN LA CONSIGNA DEL TPE, TODAVIA NO ESTA IMPLEMENTADO

}

static void zero_division() {
	exceptionMsg("Division by zero", 17);
}


static void undefined_op_code() {
	exceptionMsg("Undefined operation code", 25);
}