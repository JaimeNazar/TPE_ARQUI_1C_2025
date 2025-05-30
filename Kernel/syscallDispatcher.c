#include <syscallDispatcher.h>
#include <time.h>
#include <stdint.h>
#define BUFFER_SIZE 5

typedef struct{
    int contador;
    char buffer[6];
    char nextToWrite; // Siguiente posicion a escribir
    char nextToRead; // Siguiente posicion a leer

}CicleBuffer;
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

CicleBuffer inputBuffer = {0, {0}, 0, 0};
char getNextKey(char* c) {
    if (inputBuffer.contador > 0) {
        *c = inputBuffer.buffer[inputBuffer.nextToRead];
        inputBuffer.nextToRead = (inputBuffer.nextToRead + 1) % BUFFER_SIZE;
        inputBuffer.contador--;
        return 1;
    }

    *c = 0;
    return 0;
}


char saveKey() {
    char c = get_keyboard_output();
    c = characterFilter(c);

    if (inputBuffer.contador < BUFFER_SIZE) {
        inputBuffer.buffer[inputBuffer.nextToWrite] = c;
        inputBuffer.nextToWrite = (inputBuffer.nextToWrite + 1) % BUFFER_SIZE;
        inputBuffer.contador++;
    } else {
        // Buffer lleno: sobrescribimos el más viejo (nextToRead)
        inputBuffer.buffer[inputBuffer.nextToWrite] = c;
        inputBuffer.nextToWrite = (inputBuffer.nextToWrite + 1) % BUFFER_SIZE;
        inputBuffer.nextToRead = (inputBuffer.nextToRead + 1) % BUFFER_SIZE; 
    }

    return c;
}
// Polls the keyboard until enter is pressed or reached length specified
int read(int fd, char * buff, int length) {
    
    int count = 0;

    switch (fd) {
        case 1:
            char current;
            while (count<length) {
                current =pollKeyboard();
                if (current == '\n') { // Enter
                    buff[count++] = '\n';
                    void nextLine();
                    break; // Stop reading on Enter
                } 
                
                if(current == '\b'&&canErase()) { // Backspace
                    if (count > 0) {
                        count--;
                        
                        drawChar('\b', COLOR_WHITE); 
                        drawScreen();
                        continue;
                    }
                    
                }
                if(current!= 0){
                    buff[count++] = current;
                drawChar(current, COLOR_WHITE);
                drawScreen();
                }
            }
        break;
    }

    return count;

}

static uint64_t time_ticks() {
    return ticks_elapsed();
}

static uint64_t time(uint8_t code) {

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
        case ID_BEEP:
            int freq = va_arg(args, int);
            int duration = va_arg(args, int);
            bell(freq, duration);
            break;
        case ID_GETKEY:
            uint8_t* c = va_arg(args, uint8_t*);
            ret_val = getNextKey(c);
            break;
        default:
            // Manejar  
            break;
    };

    va_end(args);

    return ret_val;
}
