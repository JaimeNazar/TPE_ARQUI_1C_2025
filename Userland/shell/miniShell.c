#include <miniShell.h>

char buffer[128];
void shellInit() {

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
    
uint32_t currentCommandLength = 0;
void shellUpdate() {
    
    sysRead(1, buffer, 128);

	commandHandler(buffer);
	
	sysWrite(1, "miniShell > ", strlen("miniShell > "));
	
	sysDraw();
}

//Commands
void helpCommand() {
	char **commandList = getCommandList();
	char **commandListDescription = getCommandListDescription();
	sysWrite(1, "Available commands:\n", 20);
	for (int i = 0; i < COMMANDS; i++) {
		sysWrite(1, commandList[i], strlen(commandList[i]));
		sysWrite(1, commandListDescription[i], strlen(commandListDescription[i]));
		sysWrite(1, "\n", 1);
	}
}

void clearCommand() {
	sysClear();
}


//me parece que no se va a poder implementar porque el strcmp marcaria algo como "echo Hola Mundo como un error"
void echoCommand() {
	sysWrite(1, "Echo command not implemented yet\n", 33);
}

void gameCommand() {
	sysWrite(1, "Game command not implemented yet\n", 33);
}

void timeCommand() {
	sysWrite(1, "Time command not implemented yet\n", 33);
}

void error() {
	sysWrite(1, "Command not found \n", 21);
	sysWrite(1, " type 'help' for a list of commands\n", 36);
}





