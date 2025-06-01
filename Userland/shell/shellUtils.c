#include <shellUtils.h>

#define MAX_ARGS 16

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


static const int argumentsPerCommand[] = {
    0, // help
    0, // clear
    1, // sleep
    0, // game
    1, // time
    1, // beep
    0  // ticks
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
    
    char *arguments[MAX_ARGS];
    int cant = commandToArguments(command, length, arguments);

    int test = cant;

    int commandID = idHandler(arguments[0], strlen(arguments[0]));

    if ( commandID != -1 && argumentsPerCommand[commandID] != cant - 1 ) {      //primero me fijo si dado el comando, la cantidad de argumentos es correcta
        errorByArguments(arguments[0], argumentsPerCommand[commandID]);
    }
    else {
        switch (commandID) {
        case HELP: 
            helpCommand();
            break;
        case CLEAR: 
            sysClear();
            break;
        case SLEEP:                                 //ALGO ASI DEBERIAN DE ESTAR IMPLEMENTADAS SI LE QUERES PASAR UN NUMERO
            int arg = strToInt(arguments[1]);
            if (arg == -1){
                errorInvalidArgument(arguments[1]);
            }
            else{sleepCommand();}                  
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
    return;
}

char **getCommandList(){
    return commandList;
}

char **getCommandListDescription() {
    return commandListDescription;
}










