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
    "font-size",
    "zero-division",
    "undefined-op-code"
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
    " - Changes system font size, size must be greater than or equal 8",
    " - Tests the division by zero exception",
    " - Tests the invalid operation code Exception"
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
    1,  // font size
    0,  // test zero
    0  // test operation code
};


enum{
    HELP = 0,
    CLEAR,
    SLEEP,
    GAME,
    TIME,
    BEEP,
    TICKS,
    ECHO,
    REGISTERS,
    FONT_SIZE,
    ZERO_DIVISION,
    INVALID_OPCODE
};

static int commandToArguments(char *command, int length, char *arguments[MAX_ARGS]) {
    static char buffer[MAX_CMD_LEN];
    int argCount = 0;
    int i = 0, j = 0;

    //Eliminate '\n' if needed
    if (length > 0 && (command[length - 1] == '\n')) {
        command[--length] = '\0';
    }

    while (i < length && argCount < MAX_ARGS - 1) {
        // Saves the pointer of the current argument
        arguments[argCount] = &buffer[j];

        // Copy characters until the next space
        while (i < length && command[i] != ' ') {
            buffer[j++] = command[i++];
        }

        buffer[j++] = '\0'; // End of argument
        argCount++;

        // Skips all the spaces until the next argument
        while (i < length && command[i] == ' '){
            i++;
        }
            
        }

        return argCount;    //Returns argument quantity
}

static int idHandler(char* command, int length) {
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
            } else {
                setFontSize(size); // Update font size 
                fontCommand(size);
            }
            break;
        case ZERO_DIVISION: 
            testZeroCommand();
            break;
        case INVALID_OPCODE: 
            invalidopcodeCommand();
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










