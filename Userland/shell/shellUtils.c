#include <shellUtils.h>

static char *commandList[] = {
    "help",
    "clear",
    "sleep",
    "game",
    "time",
    "beep",
    "ticks",
    "echo",
    "registers",
    "font-size"
};

char *commandListDescription[] = {
    " - Shows this help message",
    " - Clears the screen",
    " - Puts the system to sleep for a specified amount of ticks",
    " - Starts the game",
    " - Shows the current time",
    " - Makes a beep sound for a specified frecuency and time",
    " - Displays the number of ticks elapsed since system start",
    " - Echoes the input back to the user",
    " - Shows the current values of each register",
    " - Changes system font size, size must be greater than or equal 8"
};


static const int argumentsPerCommand[] = {
    0, // help
    0, // clear
    1, // sleep
    1, // game
    0, // time
    2, // beep
    0, // ticks
    0, // echo, special case
    0, // registers
    1  // font size
};


typedef enum{
    HELP = 0,
    CLEAR,
    SLEEP,
    GAME,
    TIME,
    BEEP,
    TICKS,
    ECHO,
    REGISTERS,
    FONT_SIZE
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

    //Separates the command into arguments
    int cant = commandToArguments(command, length, arguments);      

    //Get the command id
    int commandID = idHandler(arguments[0], strlen(arguments[0]));  


    //If it's a command id, checks for the right argument quantity
    if ( commandID != -1 && commandID != ECHO && argumentsPerCommand[commandID] != cant - 1 ) {      
        errorByArguments(arguments[0], argumentsPerCommand[commandID]);
    }
    else {                          
        //Given the commandID, executes the correct command/error
        switch (commandID) {
        case HELP: 
            helpCommand();
            break;
        case CLEAR: 
            sysClear();
            break;
        case SLEEP: 
            int arg = strToInt(arguments[1]);
            if (arg <= -1){
                errorInvalidArgument(arguments[1]);
            }
            else{sleepCommand(arg);}                  
            break;
        case GAME:
            int players = strToInt(arguments[1]);
            if (players != 1 && players != 2){
                errorInvalidArgument(arguments[1]);
            }
            gameCommand(players);
            break;
        case TIME: 
            timeCommand();
            break;
        case BEEP: 
            int arg1 = strToInt(arguments[1]);
            int arg2 = strToInt(arguments[2]);
            if (arg1 <= -1){
                errorInvalidArgument(arguments[1]);
            } else if (arg2 <= -1){
                errorInvalidArgument(arguments[2]);
            } else{beepCommand(arg1,arg2);}
            break;
        case TICKS: 
            ticksCommand();
            break;
        case ECHO: 
            echoCommand(arguments, cant);
            break;
        case REGISTERS: 
            registersCommand();
            break;
        case FONT_SIZE:
            int size = strToInt(arguments[1]);
            if (size <= MIN_FONT_SIZE){
                errorInvalidArgument(arguments[1]);
            } else {fontCommand(size);}
            break;
        default:
            error();
            break;
        }
    }
    return;
}


//used by the help command
char **getCommandList(){
    return commandList;
}

char **getCommandListDescription() {
    return commandListDescription;
}










