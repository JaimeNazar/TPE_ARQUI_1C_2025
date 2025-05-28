#include <syscallDispatcher.h>
#include <time.h>
#include <stdint.h>

#define ID_WRITE 0
#define ID_READ 1
#define ID_CLEARBUFFER 2
#define ID_DRAWSCREEN  3
#define ID_TIMETICKS 4
#define ID_SLEEP 5
#define ID_TIME 6

#define COLOR_WHITE 0xFFFFFFFF
#define COLOR_AMBER 0x00FFBF00

// Output style depends on file descriptor
int write(int fd, const char * buff, int length) {
    switch (fd) {
        case 1:
            printText(buff, length, COLOR_WHITE);
            break;

        case 2:
            printText(buff, length, COLOR_AMBER);
            break;
    };

    return length;
}

// Polls the keyboard until enter is pressed or reached length specified
int read(int fd, char * buff, int length) {
    
    static int read = 0;

    switch (fd) {
        case 1:
            char current;
            
            while (read<length) {
                current =pollKeyboard();
                if (current == '\n') { // Enter
                    buff[read++] = '\n';
                    void nextLine();
                    read = 0; // Reset read count
                    break; // Stop reading on Enter
                } 
                if(current!= 0){
                    buff[read++] = current;
                drawChar(current, COLOR_WHITE);
                drawScreen();
                }
                
            }
        break;
    }

    return read;

}

uint64_t time_ticks() {
    return ticks_elapsed();
}

uint64_t time(uint8_t code) {

    uint8_t number = rtc(code);

    int upperBits = number & 0xF0;
    int lowerBits = number & 0x0F;

    return upperBits * 10 + lowerBits;
}

uint64_t syscallDispatcher(uint64_t rax, ...) {
    va_list args;
    va_start(args, rax);  

    uint64_t ret_val = 0;

    switch(rax) {
        case ID_WRITE:
            int fdWrite = va_arg(args, int);
            const char* buffWrite = va_arg(args, const char*);
            int lengthWrite = va_arg(args, int);

            ret_val = write(fdWrite, buffWrite, lengthWrite);
            drawScreen();
            break;
        case ID_READ:
            int fd = va_arg(args, int);
            char* buff = va_arg(args, char*);
            int length = va_arg(args, int);
            
            ret_val = read(fd, buff, length);
            break;
        case ID_CLEARBUFFER:
            clearBuffer();
            break;
        case ID_DRAWSCREEN:
            drawScreen();
            break;
        case ID_TIMETICKS:
            ret_val = ticks_elapsed();
            break;
        case ID_SLEEP:
            sleep(va_arg(args, uint64_t));
            break;
        case ID_TIME:
            ret_val = time(va_arg(args, uint8_t));
            break;
        default:
            // Manejar  
            break;
    };

    va_end(args);

    return ret_val;
}
