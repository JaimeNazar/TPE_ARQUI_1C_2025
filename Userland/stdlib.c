#include<stdlib.h>

// ------ UTILS ------

int strlen(char* str) {
	int count = 0;
	while (str[count++] != 0);
	return count;
}

int strcmp(char* str1, char* str2, int length1, int lenght2) {
    //Helps with cases like clearrrr or helppp
    if(length1 != lenght2) {                                    
        return length1 - lenght2;
    }

    int i = 0;
    //Compares each caracter
    while (str1[i] != '\0' && str2[i] != '\0') {                
        if (str1[i] != str2[i]) {
            return str1[i] - str2[i];
        }
        i++;
    }

    return 0;   //Both strings are equal
}

void intToStr(int value, char *str) {
    int i = 0;
    int isNegative = 0;
    
    //If value equals 0, return '0'
    if (value == 0) {  
        str[i++] = '0';
        str[i] = '\0';
        return;
    }

    //If the value is negative we will have to add an '-' later
    if (value < 0) {        
        isNegative = 1;
        value = -value;
    }

    //Converts the number to a string from the back to the front
    while (value != 0) {        
        int digit = value % BASE_TEN;
        str[i++] = digit + '0';
        value /= BASE_TEN;
    }

    if (isNegative)
        str[i++] = '-';

    str[i] = '\0';

    //Rotates the string using a tmp to the correct order
    for (int j = 0, k = i - 1; j < k; j++, k--) {       
        char tmp = str[j];
        str[j] = str[k];
        str[k] = tmp;
    }
}

int strToInt(const char *str) {
    int result = 0;
    int i = 0;

    int sign = 1;  

    // Verify if its negative
    if (str[i] == '-') {
        sign = -1;
        i++; // Skip neg symbol
    }

    // Convert digits, stop if next character isn't a digit
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * BASE_TEN + (str[i] - '0');
        i++;
    }

    result *= sign;

    if (str[i] < '0' || str[i] > '9') {
        if(str[i] == '\0' || str[i] == '\n') {
             return result;
        }
        
        return -1;  //If it's not a digit return 1
    }
    return result;
}

void floatToStr(float value, char *str, int decimals) {

    // Integer part, truncate and reuse function
    intToStr((int)value, str);

    // Start at the end of string
    int i = strlen(str);    
    
    // Add dot
    str[i++] = '.';

    float decPart = value - (int)value; // Truncate and subtract it

    // Do decimal part
    for (int j = 0; j < decimals; j++) {
        decPart *= BASE_TEN;

        str[i++] = (int)decPart + '0'; 
    }

    // Null terminated
    str[i] = '\0';
}

float strToFloat(const char *str) {

    // Get Integer part
    float result = (float)strToInt(str);

    // Get the decimal part starting index
    int i = 0;
    while (str[i++] != '.');

    int decimals = 0; // Decimal counter
    int decimalPart = 0;

    while (str[i] >= '0' && str[i] <= '9') {
        decimals++;
        decimalPart += decimals * (str[i] - '0');

        i++;
    }

    result += (float)decimalPart / (decimals*BASE_TEN);
    
    return result;
}


int commandToArguments(char *command, int length, char *arguments[MAX_ARGS]) {
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



/* Recieves null terminated string, parse it and read specified args */
void scanf(char* ftm, ...) {

    // Variable arguments list
    va_list args;
    va_start(args,  ftm);

    // Get user input
    char buffer[MAX_CMD_LEN];
    sysRead(STDIN, buffer, MAX_CMD_LEN);

    int index = 0;  // Index for traversing the user input

    // Process input based on format
    for (int i = 0; ftm[i] != '\0'; i++) {

        if (ftm[i] == '%') {
            char parseBuffer[MAX_CMD_LEN];  // For parsing operations
            int parseIndex = 0;

            i++;
            char next = ftm[i];

            switch(next){
                case 's':
                    char *toRead = va_arg(args, char*);
                    int toReadIdx = 0;

                    // Read until whitespace or end of input
                    while(buffer[index] != ' ' && buffer[index] != '\n' && index < MAX_CMD_LEN) {
                        toRead[toReadIdx++] = buffer[index++];
                    }

                    // Null terminated
                    toRead[toReadIdx] = '\0';

                    break;
                case 'f':
                    parseIndex = 0;
                    int dot = 0;    // Keeps track of the dot

                    // Only read numbers or a minus symbol at the start and one dot
                    while((parseIndex == 0 && buffer[index] == '-') || (!dot && buffer[index] == '.')
                        || (buffer[index] >= '0' && buffer[index] <= '9' && index < MAX_CMD_LEN)) {

                        if (buffer[index] == '.')
                            dot = 1;

                        parseBuffer[parseIndex++] = buffer[index++];
                    }

                    // Null terminated
                    parseBuffer[parseIndex] = '\0';

                    float *toReadFloat = va_arg(args, float*);

                    *toReadFloat = strToFloat(parseBuffer); // Parse to int

                    break;

                case 'd':
                    parseIndex = 0;

                    // Only read numbers or a minus symbol at the start
                    while((parseIndex == 0 && buffer[index] == '-') 
                        || (buffer[index] >= '0' && buffer[index] <= '9' && index < MAX_CMD_LEN)) {
                        parseBuffer[parseIndex++] = buffer[index++];
                    }

                    // Null terminated
                    parseBuffer[parseIndex] = '\0';

                    int *toReadInt = va_arg(args, int*);

                    *toReadInt = strToInt(parseBuffer); // Parse to int

                    break;

                default:
                    break;
            }

        } else {
            // If pattern its not whats expected, return
            if (buffer[index++] != ftm[i])
                return ;
        }
    }

    // End
    va_end(args);
}

/* Recieves null terminated string, parse it and print it */
void printf(char* ftm, ...) {

    // Variable arguments list
    va_list args;
    va_start(args,  ftm);

    for (int i = 0; ftm[i] != '\0'; i++) {

        if (ftm[i] == '%') {
            char buffer[MAX_CMD_LEN];   // For parsing operations
        
            char next = ftm[i+1];
            char *toAppend;
            switch(next){
                case 's':
                    toAppend = va_arg(args, char*);
                    sysWrite(STDOUT, toAppend, strlen(toAppend));
                    break;
                case 'c':
                    sysPutChar(va_arg(args, char));
                    break;
                case 'f':   // TODO: Allow user to selec amonut of decimals
                    double fvalue = va_arg(args, double);
                    floatToStr(fvalue, buffer, 4); // Parse to float
                    toAppend = buffer;
                    break;
                case 'd':
                    intToStr(va_arg(args, int), buffer); // Parse to string
                    toAppend = buffer;
                    break;

                default:
                    break;
            }

            i++;
        } else {
            sysWrite(STDOUT, ftm + i, 1);
        }
    }

    // End
    va_end(args);
}

// ------ TIME ------

int getSeconds() {
    return sysTime(TIME_SECONDS);
}

int getMinutes() {
    return sysTime(TIME_MINUTES);
}

int getHours() {
    return sysTime(TIME_HOURS);
}

// ------ SYSCALLS ------

uint64_t sysWrite(int fd, const char * buff, int length) {
    return syscall_wizard(0, fd, (uint64_t)buff, length, NO_ARG, NO_ARG);
}

uint64_t sysRead(int fd, char * buff, int length) {
    return syscall_wizard(ID_READ, fd, (uint64_t)buff, length, NO_ARG, NO_ARG);
}

uint64_t sysTimeTicks(){
    return syscall_wizard(ID_TIME_TICKS, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG);
}

void sysClear() {
    syscall_wizard(ID_CLEAR_BUFFER, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG);
}

void sysDraw() {
    syscall_wizard(ID_DRAW_SCREEN, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG);
}

uint64_t sysTime(int arg) {
    return syscall_wizard(ID_TIME, arg, NO_ARG, NO_ARG, NO_ARG, NO_ARG);
}

char sysGetChar() {
    return (char)syscall_wizard(ID_GET_CHAR,NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG);
}

void sysSleep(int duration) {
    syscall_wizard(ID_SLEEP, duration, NO_ARG, NO_ARG, NO_ARG, NO_ARG);
}

void sysBeep(int freq, int duration) {
    syscall_wizard(ID_BEEP, freq, duration, NO_ARG, NO_ARG, NO_ARG);
}

void sysDrawBitmap(uint64_t x, uint64_t y,uint32_t *bitmap) {
    syscall_wizard(ID_DRAW_BITMAP, x, y, (uint64_t)bitmap, NO_ARG, NO_ARG);
}

void sysConfigBitmap(int bitmapSize,uint32_t hexColor,int width){
    syscall_wizard(ID_CONFIG_BITMAP, bitmapSize, hexColor, width, NO_ARG, NO_ARG);
}

uint64_t sysGetScreenWidth() {
    return syscall_wizard(ID_VIDEO_WIDTH, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG);
}

uint64_t sysGetScreenHeight() {
    return syscall_wizard(ID_VIDEO_HEIGHT, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG);
}

void sysRegisters(int fd) {
    syscall_register_dump();
}

void sysFontSize(int size) {
    syscall_wizard(ID_FONT_SIZE, size, NO_ARG, NO_ARG, NO_ARG, NO_ARG);
}

void sysDrawTextAt(const char * str, int length, uint64_t x, uint64_t y, uint32_t hexColor) {
    syscall_wizard(ID_DRAW_TEXT, (uint64_t)str, length, x, y, hexColor);
}

void sysPutChar(const char c) {
    syscall_wizard(ID_PUT_CHAR, c, NO_ARG, NO_ARG, NO_ARG, NO_ARG);
}

uint8_t sysGetKeyEvent() {
    return syscall_wizard(ID_GET_KEY_EVENT, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG);
}