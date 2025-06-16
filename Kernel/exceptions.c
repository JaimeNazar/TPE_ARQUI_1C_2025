#include<exceptions.h>

static int strlen(const char* str) {
	int count = 0;
	while (str[count++] != 0);
	return count;
}

// Outputs text into the STDERR file descriptor
static void printError(const char * str) {
	syscallWrite(STDERR, str, strlen(str));
}

static void exceptionMsg(const char* msg) {
	
	printError("Exception: ");
	printError(msg);
	syscallWrite(STDERR, "\n", 1);

	registersDump(STDERR);

	printError("\n\n Press enter to resume normal execution \n");
}

static void zeroDivision() {
	char *msg = "Division by zero";
	exceptionMsg(msg);
}


static void undefinedOpCode() {
	char *msg = "Undefined Operation Code";
	exceptionMsg(msg);
}

void exceptionDispatcher(int exception) {
	saveRegs();
	
	if (exception == ZERO_EXCEPTION_ID)
		zeroDivision();
	else if (exception == UNDEF_OP_CODE_EXCEPTION_ID)
		undefinedOpCode();
	
	videoDrawScreen();

	// Re-enable interrupts
	_sti();

	// Wait for user to press enter before resuming execution
	char c = keyboardGetChar();
	while (c != '\n') {
		c = keyboardGetChar();
	}

	// Go back to kernel
}

