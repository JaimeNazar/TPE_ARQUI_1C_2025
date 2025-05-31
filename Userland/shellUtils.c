#include <shellUtils.h>

//Add as necessary
static char *commandList[] = {
    "help",     
    "clear",
    "sleep",
    "game",
    "time",
    "beep",
    "ticks"
};

char *commandListDescription[] = {
    " - Shows this help message",
    " - Clears the screen",
    " - Sleeps for 1 second",
    " - Starts the game",
    " - Shows the current time",
    " - Makes a beep sound",
    " - Displays the number of ticks elapsed since system start"
};




typedef enum{
HELP = 0,
CLEAR,
SLEEP,
GAME,
TIME,
BEEP,
TICKS
//COMPLETAR
};

int idHandler(char* command, int length) {
    for (int i = 0; i < COMMANDS; i++)
    {
        if (strcmp(command, commandList[i], length, strlen(commandList[i])) == 0) {
            return i;} 
    }
    return -1; // error
}
void commandHandler(char* command, int length) {
    
    int commandID = idHandler(command, length);

    switch (commandID) {
        case HELP: 
            helpCommand();
            break;
        case CLEAR: 
            sysClear();
            break;
        case SLEEP: 
            sleepCommand();
            break;
        case GAME:
           gameCommand();
            break;
        case TIME: 
            timeCommand();
            break;
        case BEEP: 
            beepCommand();
            break;
        case TICKS: 
            ticksCommand();
            break;
        default:
            error();
            break;
    }
    
}
char **getCommandList(){
    return commandList;
}
//case sensitive

char **getCommandListDescription() {
    return commandListDescription;
}












