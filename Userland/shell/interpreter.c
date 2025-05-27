#include <stdlib.h>
#include <miniShell.h>

//Add as necessary
#define COMMANDS 5
static char *commandList[] = {
    "help",
    "clear",
    "echo",
    "game",
    "time"
};


static char *commandListDescription[] = {
    " - Shows available commands",
    " - Clears the screen",
    " - Echoes input back to the user",
    " - Starts a game",
    " - Displays the current time"
};



typedef enum{
HELP = 0,
CLEAR,
ECHO,
GAME,
TIME,
//COMPLETAR
}


void commandHandler(char* command) {

    if (command == NULL) {
        return;
    }
    
    int commandID = idHandler(command);


    switch (commandID) {
        case HELP: 
            helpCommand();
            break;
        case CLEAR: 
            sysClear();
            break;
        case ECHO: 
            echoCommand();
            break;
        case GAME:
           gameCommand();
            break;
        case TIME: 
            timeCommand();
            break;
        default:
            error(command);
            break;
    }
    
}


//case sensitive
int idHandler(char* command) {
    for (size_t i = 0; i < COMMANDS; i++)
    {
        if (strcmp(command, commandList[i]) == 0) {
        return i;} 
    }
    return -1; // error
}













