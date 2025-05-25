#include<stdlib.h>

#define NO_ARG 0x0

// Syscalls IDs
#define ID_WRITE 0x0
#define ID_READ 0x1
#define ID_TIME_TICKS 0x2
#define ID_CLEAR 0x3
#define ID_DRAW 0x4

uint64_t sysWrite(int fd, char * buff, int length) {
    return syscall_wizard(0, fd, buff, length);
}

uint64_t sysRead(int fd, char * buff, int length) {
    return syscall_wizard(1, fd, buff, length);
}

uint64_t sysTimeTicks(){
    return syscall_wizard(2, NO_ARG, NO_ARG, NO_ARG);
}

void sysClear() {
    return syscall_wizard(3, NO_ARG, NO_ARG, NO_ARG);
}

void sysDraw() {
    return syscall_wizard(4, NO_ARG, NO_ARG, NO_ARG);
}

int strlen(char* str) {
	int count = 0;
	while (str[count++] != 0);

	return count;
}
