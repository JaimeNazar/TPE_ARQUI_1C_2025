#include <miniShell.h>
#include<pongis.h>

char buffer[128];
void shellInit() {

	int a = 0;
	char buf[12];
	scanf("%d %s", &a, buf);
	printf("\nRecieved number: %d and %s\n", a, buf);
	//Pongis();
	
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
    
    int realLen = sysRead(1, buffer, 128);

	sysWrite(1, "\n", 1);	// Move one line down
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
	sysSleep(duration);
}

void gameCommand() {
	sysWrite(1, "\nGame command not implemented yet\n", 34);
}

void timeCommand() {
	printf("Current time: %d : %d : %d\n", getHours(), getMinutes(), getSeconds());
}

//no me anda
void beepCommand(int frequency, int duration) {
	sysBeep(frequency, duration);
	sysWrite(1, "\n", 1);
}

void ticksCommand() {
	printf("Ticks: %d\n",sysTimeTicks());
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

void fontCommand(int size) {

	if (size < MIN_FONT_SIZE) {
		printf("\n Invalid font size, must be grater than %d \n", MIN_FONT_SIZE);
		return ;
	}
	sysClear();
	sysFontSize(size);
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



