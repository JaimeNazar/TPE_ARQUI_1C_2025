#include<stdlib.h>

// TODO: move constants to header
#define STDOUT 0x1
#define STDIN 0x1

#define NO_ARG 0x0

#define BASE_TEN 10

#define MAX_CMD_LEN 128
#define MAX_ARGS 16

// Syscalls IDs
#define ID_WRITE 0
#define ID_READ 1
#define ID_CLEARBUFFER 2
#define ID_DRAWSCREEN 3
#define ID_TIMETICKS 4
#define ID_SLEEP 5
#define ID_TIME 6
#define ID_GETKEY 8
#define ID_BEEP 7
#define ID_DRAWBITMAP 9
#define ID_CONFIGBITMAP 10
#define ID_DUMPREGS 11
#define ID_FONT_SIZE 12

// ------ UTILS ------

int strlen(char* str) {
	int count = 0;
	while (str[count++] != 0);
	return count;
}

int strcmp(char* str1, char* str2, int length1, int lenght2) {
    if(length1 != lenght2) {                                    //helps with cases like clearrrr or helppp
        return length1 - lenght2;
    }
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return str1[i] - str2[i];
        }
        i++;
    }
}


void intToStr(int value, char *str) {
    int i = 0;
    int isNegative = 0;

    // Manejo del 0
    if (value == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }

    // Si es negativo
    if (value < 0) {
        isNegative = 1;
        value = -value;
    }

    // Convertir los dígitos al revés
    while (value != 0) {
        int digit = value % BASE_TEN;
        str[i++] = digit + '0';
        value /= BASE_TEN;
    }

    if (isNegative)
        str[i++] = '-';

    str[i] = '\0';

    // Invertir el string, salteandose el null terminated
    for (int j = 0, k = i - 1; j < k; j++, k--) {
        char tmp = str[j];
        str[j] = str[k];
        str[k] = tmp;
    }
}



int commandToArguments(char *command, int length, char *arguments[MAX_ARGS]) {
    static char buffer[MAX_CMD_LEN];
    int argCount = 0;
    int i = 0, j = 0;

    // Eliminar \n o \r al final
    if (length > 0 && (command[length - 1] == '\n' || command[length - 1] == '\r')) {
        command[--length] = '\0';
    }

    // Saltar espacios iniciales
    while (i < length && command[i] == ' ')
        i++;

    while (i < length && argCount < MAX_ARGS - 1) {
        // Guardar puntero al argumento actual
        arguments[argCount] = &buffer[j];

        // Copiar caracteres hasta próximo espacio
        while (i < length && command[i] != ' ') {
            buffer[j++] = command[i++];
        }

        buffer[j++] = '\0'; // fin del argumento
        argCount++;

        // Saltar espacios entre argumentos
        while (i < length && command[i] == ' ')
            i++;}


        arguments[argCount] = 0; // terminador estilo argv

        return argCount; // devolver cantidad de argumentos encontrados
}


int strToInt(const char *str) {
    int result = 0;
    int i = 0;

    int sign = 1;   // Positive

    // Verify that its negative
    if (str[i] == '-') {
        sign = -1;  // Negative
        i++; // Skip neg symbol
    }

    // Convert digits, stop if next character isnt a digit
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * BASE_TEN + (str[i] - '0');
        
        i++;
    }

    result *= sign;

    if (str[i] < '0' || str[i] > '9') {
        if(str[i] == '\0' || str[i] == '\n' || str[i] == '\r') {
             return result;
        }
        // Si no es un dígito, retornar -1
        return -1;
    }
    return result;
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
                case 'd':

                    char aux[MAX_CMD_LEN];
                    int auxIndex = 0;

                    // Only read numbers or a minus symbol at the start
                    while((auxIndex == 0 && buffer[index] == '-') 
                        || (buffer[index] >= '0' && buffer[index] <= '9' && index < MAX_CMD_LEN)) {
                        aux[auxIndex++] = buffer[index++];
                    }

                    // Null terminated
                    aux[auxIndex] = '\0';

                    int *toReadInt = va_arg(args, int*);

                    *toReadInt = strToInt(aux); // Parse to int

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
        
            char next = ftm[i+1];

            char *toAppend;
            switch(next){
                case 's':
                    toAppend = va_arg(args, char*);
                    break;
                case 'd':
                    char buffer[MAX_CMD_LEN]; // It will be never be greater than this
                    intToStr(va_arg(args, int), buffer); // Parse to string
                    toAppend = buffer;
                    break;

                default:
                    break;
            }

            sysWrite(STDOUT, toAppend, strlen(toAppend));
            i++;
        } else {
            sysWrite(STDOUT, ftm + i, 1);
        }
    }

    // End
    va_end(args);
}

// ------ SYSCALLS ------

uint64_t sysWrite(int fd, char * buff, int length) {
    return syscall_wizard(0, fd, buff, length);
}

uint64_t sysRead(int fd, char * buff, int length) {
    return syscall_wizard(ID_READ, fd, buff, length);
}

uint64_t sysTimeTicks(){
    return syscall_wizard(ID_TIMETICKS, NO_ARG, NO_ARG, NO_ARG);
}

void sysClear() {
    return syscall_wizard(ID_CLEARBUFFER, NO_ARG, NO_ARG, NO_ARG);
}

void sysDraw() {
    return syscall_wizard(ID_DRAWSCREEN, NO_ARG, NO_ARG, NO_ARG);
}

void sysTime(int code) {
    return syscall_wizard(ID_TIME, code, NO_ARG, NO_ARG);
}
char sysKey() {
    return (char)syscall_wizard(ID_GETKEY,NO_ARG, NO_ARG, NO_ARG);
}

void sysSleep(int duration) {
    return syscall_wizard(ID_SLEEP, duration, NO_ARG, NO_ARG);
}

void sysBeep(int freq, int duration) {
    return syscall_wizard(ID_BEEP, freq, duration, NO_ARG);
}
void sysDrawBitmap(uint64_t x, uint64_t y,uint32_t *bitmap) {
    syscall_wizard(ID_DRAWBITMAP, x, y, bitmap);
}
void sysConfigBitmap(int bitmapSize,uint32_t hexColor,int width){
    syscall_wizard(ID_CONFIGBITMAP, bitmapSize, hexColor, width);
}

void sysRegisters(int fd) {
    return syscall_wizard(ID_DUMPREGS, fd, NO_ARG, NO_ARG);
}

void sysFontSize(int size) {
    return syscall_wizard(ID_FONT_SIZE, size, NO_ARG, NO_ARG);
}