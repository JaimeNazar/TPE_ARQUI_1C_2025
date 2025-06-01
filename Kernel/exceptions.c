#include<exceptions.h>

static int strlen(char* str) {
	int count = 0;
	while (str[count++] != 0);
	return count;
}

// Outputs text into the STDERR file descriptor
static void printError(char * str) {
	write(2, str, strlen(str));
}

static void exceptionMsg(const char* msg) {
	
	printError("Excepcion: ");
	printError(msg);
	write(2, "\n", 1);

	interruptsDumpRegisters();

	printError("\n\n Press enter to resume normal execution \n");
}

static void zeroDivision() {
	char *msg = "Division by zero";
	exceptionMsg(msg);
}


static void undefinedOpCode() {
	char *msg = "Division by zero";
	exceptionMsg(msg);
}

void exceptionDispatcher(int exception) {
	
	if (exception == ZERO_EXCEPTION_ID)
		zeroDivision();
	else if (exception == UNDEF_OP_CODE_EXCEPTION_ID)
		undefinedOpCode();
	
	drawScreen();

	// Re-enable interrupts
	_sti();

	// Wait for user to press enter before resuming execution
	char c = 0;
	while (c != '\n') {
		while(!canRead());
		getNextKey(&c);
	}
}

