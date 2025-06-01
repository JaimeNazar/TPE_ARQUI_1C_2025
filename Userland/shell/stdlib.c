#include<stdlib.h>

// TODO: move constants to header
#define STDOUT 0x1

#define NO_ARG 0x0


#define MAX_CMD_LEN 128
#define MAX_ARGS 16

// Syscalls IDs
#define ID_WRITE 0x0
#define ID_READ 0x1
#define ID_CLEARBUFFER 0x2
#define ID_DRAWSCREEN 0x3
#define ID_TIMETICKS 0x4
#define ID_SLEEP 0x5
#define ID_TIME 0x6
#define ID_GETKEY 0x8
#define ID_BEEP 0x7
#define ID_DRAWBITMAP 0x9
#define ID_CONFIGBITMAP 0xA


// ------ AUXILIARY ------

// From naiveConsole implementation
static uint32_t uintToBase(uint64_t value, char * bufferBase, uint32_t base)
{
	char *p = bufferBase;
	char *p1, *p2;
	uint32_t digits = 0;

	//Calculate characters for each digit
	do
	{
		uint32_t remainder = value % base;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	}
	while (value /= base);

	// Terminate string in bufferBase.
	*p = 0;

	//Reverse string in bufferBase.
	p1 = bufferBase;
	p2 = p - 1;
	while (p1 < p2)
	{
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return digits;
}


// ------ UTILS ------

// TODO: make them all static?
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
        int digit = value % 10;
        str[i++] = digit + '0';
        value /= 10;
    }

    if (isNegative)
        str[i++] = '-';

    str[i] = '\0';

    // Invertir el string
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

    // Convertir dígitos
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    if (str[i] < '0' || str[i] > '9') {
        // Si no es un dígito, retornar -1
        return -1;
    }
    return result;
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
                    toAppend = stoi(va_arg(args, int));// Parse to string
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

#define BASE_TEN 10

char * stoi(int value) {
    uintToBase(value, bufferBase, BASE_TEN);
    return bufferBase;
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
void sysKey(uint8_t * c) {
    return syscall_wizard(ID_GETKEY,&c, NO_ARG, NO_ARG);
}

void sysSleep(int duration) {
    return syscall_wizard(ID_SLEEP, duration, NO_ARG, NO_ARG);
}

void sysBeep(int freq, int duration) {
    return syscall_wizard(ID_BEEP, freq, duration, NO_ARG);
}
void sysDrawBitmap(uint64_t x, uint64_t y,int bitmapSize) {
    syscall_wizard(ID_DRAWBITMAP, x, y, bitmapSize);
}
void sysConfigBitmap(uint32_t *bitmap,uint32_t hexColor,int width){
    syscall_wizard(ID_CONFIGBITMAP, bitmap, hexColor, width);
}

