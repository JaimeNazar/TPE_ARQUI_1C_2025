#include <shellUtils.h>

//Add as necessary

static char *commandList[] = {
    "help",     
    "clear",
    "echo",
    "game",
    "time"
};

//TAMBIEN IR CAMBIANDO EL COMMNADS EN shellUtils.h
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












