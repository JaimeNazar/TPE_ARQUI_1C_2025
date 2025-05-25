#include <syscallDispatcher.h>
#include <time.h>
#include <stdint.h>

#define ID_WRITE 0
#define ID_READ 1
#define ID_ 0
#define ID_  0
#define ID_ 0
#define ID_SLEEP 5
#define ID_CLEARSCREEN 6


void syscallDispatcher(uint64_t rax, ...) {
    va_list args;
    va_start(args, rax);  

    switch(rax) {
        case ID_WRITE:
            write(va_arg(args, int), va_arg(args, const char*), va_arg(args, int));
            break;
        case ID_READ:
            read(va_arg(args, int), va_arg(args, char*), va_arg(args, int));
            break;
        case ID_SLEEP:
            sleep(va_arg(args, uint64_t));
            break;
        case ID_CLEARSCREEN:
            //Syscall_clearScreen
            clearScreen();
            break;
        default:
            // Manejar  
            break;
    };

    va_end(args);
}








// Output style depends on file descriptor
int write(int fd, const char * buff, int length) {
    switch (fd) {
        case 1:
            for (int i = 0; i < length; i++) {
                if (buff[i] == '\n')
                    ncNewline();
                else
                    ncPrintChar(buff[i]);
            }

            break;

        case 2:
            ncPrint(buff);
            break;
    };

    return length;  // TODO: improve
}

// TODO: check if int or is size_t

// Polls the keyboard until enter is pressed or reached length specified
int read(int fd, char * buff, int length) { 
    
    int read = 0;

    switch (fd) {
        case 1:
            char current;

            while (read < length && (current = pollKeyboard()) != 0xA) {  // 0xA, Enter scancode
                
                if (current != 0)
                    buff[read++] = current;
            } 
            break;

        case 2:
            ncPrint(buff);
            break;
    };

    return read;

}


void clearScreen() {
    uint64_t totalBytes = VBE_mode_info->pitch * VBE_mode_info->height;
    memset((void*)VBE_mode_info->framebuffer, 0, totalBytes);
}

