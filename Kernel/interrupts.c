#include<interrupts.h>

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

/*
 * Prints hex representaiton of 64 bit value
 * NOTE: The for doesnt stop if the raminder is 0 because it need to rewrite 
 * any previoud character left on the template in an earlier call
*/
static void printHex(uint64_t value) {
	char* template = HEX_64_TEMPLATE;	// Template for the hex representation of a 64 bit value

	// Fill in template with actual hex values
	for (int i = HEX_64_TEMPLATE_LENGHT - 1; i >= HEX_64_TEMPLATE_OFFSET; i--) {
		value /= HEX_BASE;
		uint32_t remainder = value % HEX_BASE;
		template[i] = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
	}

	write(2, template, HEX_64_TEMPLATE_LENGHT);
}

/* Prints a map, in this case, used the registers mapped to their values 
 * TODO: It prints them in columns of 3
 */
static void printMap(const char** keys, uint64_t* values, int lenght)  {
	for (int i = 0 ; i < lenght; i++) {
		write(2, keys[i], MSG_LENGTH);
		printHex(values[i]);
		write(2, "\n", 1);
	}
}

void interruptsDumpRegisters(){
    char *general = "General Registers: \n";
	write(2, general, strlen(general));

	// Print general purpose registers
	printMap(generalRegisterString, get_registers(), GENERAL_REGISTERS_COUNT);

	char *special = "Special Registers: \n";
	write(2, special, strlen(special));

	// Print special registers
	printMap(specialRegisterString, get_special_registers(), SPECIAL_REGISTERS_COUNT);

}