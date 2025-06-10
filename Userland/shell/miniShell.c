#include <miniShell.h>
extern test_Invalid_OpCode();

static int fontSize = MIN_FONT_SIZE;
static char buffer[128];

void shellInit() {

	sysFontSize(fontSize);

    sysWrite(1, "miniShell > ", strlen("miniShell > "));
    
    sysDraw();

	int lastTime = sysTimeTicks();
	int deltaTime = 0;
	
	while(1) {

		if (deltaTime >= 1) {

            shellUpdate();

	        lastTime = sysTimeTicks();
		}

		deltaTime = sysTimeTicks() - lastTime;
	}

}
    
void shellUpdate() {
    
    int realLen = sysRead(1, buffer, 128);	//Reads 128 caracter

	sysWrite(1, "\n", 1);	// Move one line down
	sysDraw();

    commandHandler(buffer, realLen);	//Checks if it's a command and executes it

    sysWrite(1, "miniShell > ", strlen("miniShell > "));
    
    sysDraw();
}


void setFontSize(int size) {
	fontSize = size;
}

// ------ COMMANDS ------

void helpCommand() {
	char **commandList = getCommandList();
	char **commandListDescription = getCommandListDescription();
	sysWrite(1, "\nAvailable commands:\n", 21);
	for (int i = 0; i < COMMANDS; i++) {
		sysWrite(1, commandList[i], strlen(commandList[i]));
		sysWrite(1, commandListDescription[i], strlen(commandListDescription[i]));
		sysWrite(1, "\n", 1);
	}
}

void clearCommand() {
	sysClear();
}


void sleepCommand(int duration) {
	sysSleep(duration);
}

void gameCommand(int players) {
	pongis(players);

	// Restore font size
	sysFontSize(fontSize);
}

void timeCommand() {
	int hours = getHours();

	if (hours == 0 || hours == 1 || hours == 2){
		hours += 24;
	}
	hours += UTC_OFFSET;

	printf("Current time: %d:%d:%d\n", hours, getMinutes(), getSeconds());
}

void beepCommand(int frequency, int duration) {
	sysBeep(frequency, duration);
	sysWrite(1, "\n", 1);
}

void ticksCommand() {
	printf("Ticks: %d\n",sysTimeTicks());
}


void echoCommand(char* arguments[MAX_ARGS], int cant) {
	for (int i = 1; i < cant; i++) {
		sysWrite(1, arguments[i], strlen(arguments[i]));
		sysWrite(1, " ", 1); 
	}
	sysWrite(1, "\n", 1);
}


void registersCommand(){
	sysWrite(1, "\n", 1);
	sysRegisters(1);
}

void fontCommand(int size) {
	sysClear();

	sysFontSize(size);

}


void testZeroCommand() {
	float a = 10 / 0;
}

void invalidopcodeCommand() {
	test_Invalid_OpCode();
}

void error() {
	sysWrite(1, "\nCommand not found \n", 22);
	sysWrite(1, " \ntype 'help' for a list of commands\n", 37);
}

void errorByArguments(char* command, int cant){

	printf( "\nInvalid number of arguments for command: %s", command);
	printf("\n Expected: %d\n", cant);
}

void errorInvalidArgument(char* argument) {
	printf("\nInvalid argument: %s\n", argument);
	sysWrite(1, "\n", 1);
}



