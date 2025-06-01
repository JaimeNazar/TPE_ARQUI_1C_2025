#include <syscallDispatcher.h>
#include <time.h>
#include <stdint.h>
#include <interrupts.h>
#include <keyboard.h>

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
    
    int count = 0;

    switch (fd) {
        case 1:
            char current;
            while (count<length) {

                while(!canRead());  // Wait until there is a key to read

                getNextKey(&current);   // Get key from keyboard buffer

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

static uint64_t time(uint8_t code) {

    uint8_t number = rtc(code);

    int upperBits = number & 0xF0;
    int lowerBits = number & 0x0F;

    return upperBits * 10 + lowerBits;
}

uint64_t syscallDispatcher(uint64_t rax, ...) {
    va_list args;
    va_start(args, rax);  


    // Re-enable interrupts
    _sti();

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
            sleep(va_arg(args, int));
            break;
        case ID_TIME:
            ret_val = time(va_arg(args, int));
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
        case ID_DRAWBITMAP: 
            uint64_t x = va_arg(args, uint64_t);
            uint64_t y = va_arg(args, uint64_t);
            uint32_t *bitmap = va_arg(args, uint32_t*);
            drawBitMap( x, y,bitmap);
            break;
        case ID_CONFIGBITMAP:
            int bitmapPixelSize = va_arg(args, int);
            uint32_t hexColor = va_arg(args, uint32_t);
            int width = va_arg(args, int);
            ConfigBitmap(bitmapPixelSize, hexColor, width);
            break;
        case ID_DUMP_REGS:
            int fdDump = va_arg(args, int);
            interruptsDumpRegisters(fdDump);
            break;
        default:
            // Manejar  
            break;
    };

    va_end(args);

    return ret_val;
}
