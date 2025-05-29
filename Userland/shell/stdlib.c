#include<stdlib.h>

// TODO: move constants to header
#define STDOUT 0x1

#define NO_ARG 0x0

// Syscalls IDs
#define ID_WRITE 0x0
#define ID_READ 0x1
#define ID_CLEARBUFFER 0x2
#define ID_DRAWSCREEN 0x3
#define ID_TIMETICKS 0x4
#define ID_SLEEP 0x5
#define ID_TIME 0x6
#define ID_BEEP 0x7


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

void sysSleep(int duration) {
    return syscall_wizard(ID_SLEEP, duration, NO_ARG, NO_ARG);
}

void sysBeep(int freq, int duration) {
    return syscall_wizard(ID_BEEP, freq, duration, NO_ARG);
}

