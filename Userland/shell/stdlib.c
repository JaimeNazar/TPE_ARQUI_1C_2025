#include<stdlib.h>

#define NO_ARG 0x0

// Syscalls IDs
#define ID_WRITE 0x0
#define ID_READ 0x1
#define ID_CLEARBUFFER 0x2
#define ID_DRAWSCREEN 0x3
#define ID_TIMETICKS 0x4

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

int strlen(char* str) {
	int count = 0;
	while (str[count++] != 0);

	return count;
}
