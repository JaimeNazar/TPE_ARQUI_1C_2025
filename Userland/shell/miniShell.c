#include <miniShell.h>
#include<pongis.h>

char buffer[128];
void shellInit() {

	Pongis();

	sysWrite(1, "miniShell > ", strlen("miniShell > "));
	sysDraw();
	
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
    
    int realLen = sysRead(1, buffer, 128);
	sysDraw();

    commandHandler(buffer, realLen);
    
    sysWrite(1, "miniShell > ", strlen("miniShell > "));
    
    sysDraw();
}

//Commands
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
	sysSleep(duration); // Sleep for 1 second
	sysWrite(1, "\n", 1);
}

void gameCommand() {
	sysWrite(1, "\nGame command not implemented yet\n", 34);
}

void timeCommand() {
	sysWrite(1, "\nTime command not implemented yet\n", 34);
}

//no me anda
void beepCommand(int frequency, int duration) {
	sysBeep(frequency, duration);
	sysWrite(1, "\n", 1);
}

void ticksCommand() {
	uint64_t ticks = sysTimeTicks();
	char buffer[32];
	intToStr(ticks, buffer);
	sysWrite(1, "\nTicks: ", strlen("\nTicks: "));
	sysWrite(1, buffer, strlen(buffer));
	sysWrite(1, "\n", 1);
}


void echoCommand(char* arguments[MAX_ARGS], int cant) {

	sysWrite(1, "\n", 1);
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

void error() {
	sysWrite(1, "\nCommand not found \n", 22);
	sysWrite(1, " \ntype 'help' for a list of commands\n", 37);
}

void errorByArguments(char* command, int cant){
	sysWrite(1, "\nInvalid number of arguments for command: ", 42);
        sysWrite(1, command, strlen(command));
        sysWrite(1, "\n", 1);
        sysWrite(1, "Expected ", 9);
        char buffer[10];  // espacio suficiente para el número
    	intToStr(cant, buffer);
   		sysWrite(1, buffer, strlen(buffer));
        sysWrite(1, "\n", 1);
}

void errorInvalidArgument(char* argument) {
	sysWrite(1, "\nInvalid argument: ", 19);
	sysWrite(1, argument, strlen(argument));
	sysWrite(1, "\n", 1);
}



