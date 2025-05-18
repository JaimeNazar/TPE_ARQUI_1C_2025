#include <syscallDispatcher.h>

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

void syscallDispatcher(uint64_t rax, ...) {
    va_list args;
    va_start(args, rax);  

    switch(rax) {
        case 0:
            write(va_arg(args, int), va_arg(args, const char*), va_arg(args, int));
            break;
        case 1:
            read(va_arg(args, int), va_arg(args, char*), va_arg(args, int));
            break;
        default:
            // Manejar  
            break;
    };

    va_end(args);
}