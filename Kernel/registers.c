#include<registers.h>

const char * generalRegisterString[] = {                               //every entry with a lenght of 8
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
 * NOTE: The for doesnt stop if the raminder is 0 because it needs to rewrite 
 * any previoud character left on the template in an earlier call
*/
static void printHex(uint64_t value, int fd) {
	char* template = HEX_64_TEMPLATE;	// Template for the hex representation of a 64 bit value

	// Fill in template with actual hex values
	for (int i = HEX_64_TEMPLATE_LENGHT - 1; i >= HEX_64_TEMPLATE_OFFSET; i--) {
		uint32_t remainder = value % HEX_BASE;
		template[i] = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		value /= HEX_BASE;
	}

	syscallWrite(fd, template, HEX_64_TEMPLATE_LENGHT);
}

/* Prints a map, in this case, used the registers mapped to their values */
static void printMap(const char** keys, uint64_t* values, int lenght, int fd)  {
	for (int i = 0 ; i < lenght; i++) {
		syscallWrite(fd, keys[i], MSG_LENGTH);
		printHex(values[i], fd);
		syscallWrite(fd, "\n", 1);
	}
}

void registersDump(int fd){
    char *general = "General Registers: \n";
	syscallWrite(fd, general, strlen(general));

	// Print general purpose registers
	printMap(generalRegisterString, get_registers(), GENERAL_REGISTERS_COUNT, fd);

	char *special = "Special Registers: \n";
	syscallWrite(fd, special, strlen(special));

	// Print special registers
	printMap(specialRegisterString, get_special_registers(), SPECIAL_REGISTERS_COUNT, fd);

}