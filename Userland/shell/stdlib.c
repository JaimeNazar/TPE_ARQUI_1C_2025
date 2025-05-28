#include<stdlib.h>

#define NO_ARG 0x0

// Syscalls IDs
#define ID_WRITE 0x0
#define ID_READ 0x1
#define ID_CLEARBUFFER 0x2
#define ID_DRAWSCREEN 0x3
#define ID_TIMETICKS 0x4
#define ID_TIME 0x6

// ------ UTILS ------

int strlen(char* str) {
	int count = 0;
	while (str[count++] != 0);

	return count;
}

int strcmp(char* str1, char* str2) {
    int i = 0;
    while (str1[i] != 0 && str2[i] != 0) {
        if (str1[i] != str2[i]) {
            return str1[i] - str2[i];
        }
        i++;
    }

    return str1[i] - str2[i];
}

/* Recieves null terminated string, parse it and print it */
void printf(char* ftm, ...) {

    // Variable arguments list
    va_list ptr;
    va_start(ptr, str);



    // End
    va_end(ptr);
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
