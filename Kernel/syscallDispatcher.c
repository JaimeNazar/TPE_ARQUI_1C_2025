#include <syscallDispatcher.h>
#include <time.h>
#include <stdint.h>
#include <interrupts.h>
#include <keyboard.h>

// Output style depends on file descriptor
int syscallWrite(int fd, const char * buff, int length) {
    switch (fd) {
        case 1:
            videoPrintText(buff, length, COLOR_WHITE);
            break;

        case 2:
            videoPrintText(buff, length, COLOR_AMBER);
            break;
    };

    return length;
}

// Polls the keyboard until enter is pressed or reached length specified
int syscallRead(int fd, char * buff, int length) {
    
    int count = 0;

    switch (fd) {
        case 1:
            char current;
            while (count<length) {

                current = keyboardGetChar();   // Get char from keyboard buffer

                if (current == '\n') { // Enter
                    buff[count++] = '\n';
                    videoNextLine();
                    break; // Stop reading on Enter
                } else if(current == '\b' && videoCanErase()) { // Backspace
                    if (count > 0) {
                        count--;
                        
                        videoDrawChar('\b', COLOR_WHITE); 
                        videoDrawScreen();
                        continue;
                    }
                    
                }else if(current!= 0){
                    buff[count++] = current;
                    videoDrawChar(current, COLOR_WHITE);
                    videoDrawScreen();
                }

            }
        break;
    }

    return count;

}

static uint64_t time(uint8_t code) {

    uint8_t number = rtc(code);

    int upperBits = (number & 0xF0) >> 4;
    int lowerBits = number & 0x0F;

    return upperBits * 10 + lowerBits;
}

// FIX: Org id numbers
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

            ret_val = syscallWrite(fdWrite, buffWrite, lengthWrite);
            break;

        case ID_READ:
            int fd = va_arg(args, int);
            char* buff = va_arg(args, char*);
            int length = va_arg(args, int);
            
            ret_val = syscallRead(fd, buff, length);
            break;

        case ID_CLEAR_BUFFER:
            videoClearBuffer();
            break;

        case ID_DRAW_SCREEN:
            videoDrawScreen();
            break;

        case ID_TIME_TICKS:
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

        case ID_GET_CHAR:
            ret_val = keyboardGetChar();
            break;

        case ID_DRAW_BITMAP: 
            uint64_t x = va_arg(args, uint64_t);
            uint64_t y = va_arg(args, uint64_t);
            uint32_t *bitmap = va_arg(args, uint32_t*);

            videoDrawBitMap( x, y,bitmap);
            break;

        case ID_CONFIG_BITMAP:
            int bitmapPixelSize = va_arg(args, int);
            uint32_t hexColor = va_arg(args, uint32_t);
            int width = va_arg(args, int);
            videoConfigBitmap(bitmapPixelSize, hexColor, width);

            break;

        case ID_DUMP_REGS:
            int fdDump = va_arg(args, int);
            interruptsDumpRegisters(fdDump);

            break;

        case ID_FONT_SIZE:
            int fontSize = va_arg(args, int);
            videoSetFontsize(fontSize);

            break;

        case ID_DRAW_TEXT:
            const char * str = va_arg(args, const char *);
            int lenght = va_arg(args, int);
            uint64_t posX = va_arg(args, uint64_t);
            uint64_t posY = va_arg(args, uint64_t);
            uint32_t textColor = va_arg(args, uint32_t);

            videoDrawTextAt(str, lenght, posX, posY, textColor);

            break;
        case ID_GET_KEY_EVENT:
            ret_val = keyboardGetKeyEvent();
            break;
        case ID_VIDEO_WIDTH:
            ret_val = videoGetWidth();
            break;
        case ID_VIDEO_HEIGHT:
            ret_val = videoGetHeight();
            break;

        default:
            // Manejar  
            break;
    };

    va_end(args);

    return ret_val;
}
