#include <interpreter.h>

//Add as necessary

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
};

int idHandler(char* command) {
    for (int i = 0; i < COMMANDS; i++)
    {
        if (strcmp(command, commandList[i]) == 0) {
        return i;} 
    }
    return -1; // error
}
void commandHandler(char* command) {
    sysWrite(2, "A", 1);
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
char **getCommandList(){
    return commandList;
}
//case sensitive

char **getCommandListDescription() {
    return commandListDescription;
}












