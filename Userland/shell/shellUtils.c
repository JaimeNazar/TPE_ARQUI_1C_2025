#include <shellUtils.h>

//Add as necessary

static char *commandList[] = {
    "help",     
    "clear",
    "sleep",
    "game",
    "time",
    "beep"
};

//TAMBIEN IR CAMBIANDO EL COMMNADS EN shellUtils.h
static char *commandListDescription[] = {
    " - Shows available commands",
    " - Clears the screen",
    " - puts the shell to sleep for a specified time",
    " - Starts a game",
    " - Displays the current time",
    " - Beeps with a frequency and duration"
};



typedef enum{
HELP = 0,
CLEAR,
SLEEP,
GAME,
TIME,
BEEP
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












