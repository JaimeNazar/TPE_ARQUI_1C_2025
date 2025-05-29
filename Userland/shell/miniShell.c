#include <miniShell.h>

char buffer[128];
void shellInit() {

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


void sleepCommand() {
	sysSleep(10); // Sleep for 1 second
}

void gameCommand() {
	sysWrite(1, "\nGame command not implemented yet\n", 34);
}

void timeCommand() {
	sysWrite(1, "\nTime command not implemented yet\n", 34);
}

//no me anda
void beepCommand() {
	sysBeep(400, 20);
}



void error() {
	sysWrite(1, "\nCommand not found \n", 22);
	sysWrite(1, " \ntype 'help' for a list of commands\n", 37);
}







