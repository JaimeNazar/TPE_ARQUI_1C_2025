
#include <keyboard.h>

// Scancode to ASCII for US keyboard layout
char kbd_US [128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',   
  '\t', /* <-- Tab */
  'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',     
    0, /* <-- control key */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',  0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',   0,
  '*',
    0,  /* Alt */
  ' ',  /* Space bar */
    0,  /* Caps lock */
    0,  /* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,  /* < ... F10 */
    0,  /* 69 - Num lock*/
    0,  /* Scroll Lock */
    0,  /* Home key */
    0,  /* Up Arrow */
    0,  /* Page Up */
  '-',
    0,  /* Left Arrow */
    0,
    0,  /* Right Arrow */
  '+',
    0,  /* 79 - End key*/
    0,  /* Down Arrow */
    0,  /* Page Down */
    0x1,  /* Insert Key */
    0,  /* Delete Key */
    0,   0,   0,
    0,  /* F11 Key */
    0,  /* F12 Key */
    0,  /* All other keys are undefined */
};

static unsigned char keyValues[KEYS][2] = {
	{0, 0},
	{27, 27},
	{'1', '!'},
	{'2', '@'},
	{'3', '#'},
	{'4', '$'},
	{'5', '%'},
	{'6', '^'},
	{'7', '&'},
	{'8', '*'},
	{'9', '('},
	{'0', ')'},
	{'-', '_'},
	{'=', '+'},
	{'\b', '\b'},
	{'\t','\t'},
	{'q', 'Q'}, // 16
	{'w', 'W'},
	{'e', 'E'},
	{'r', 'R'},
	{'t', 'T'},
	{'y', 'Y'},
	{'u', 'U'},
	{'i', 'I'},
	{'o', 'O'},
	{'p', 'P'}, // 25
	{'[', '{'},
	{']', '}'},
	{'\n', '\n'},
	{0, 0},
	{'a', 'A'},//30
	{'s', 'S'},
	{'d', 'D'},
	{'f', 'F'},
	{'g', 'G'},
	{'h', 'H'},
	{'j', 'J'},
	{'k', 'K'},
	{'l', 'L'},//38
	{';', ':'},
	{39, 34}, 
	{'`', '~'},
	{0, 0},
	{'\\', '|'},
	{'z', 'Z'}, //44
	{'x', 'X'},
	{'c', 'C'},
	{'v', 'V'},
	{'b', 'B'},
	{'n', 'N'},
	{'m', 'M'},//50
	{',', '<'},
	{'.', '>'},
	{'/', '?'},
	{0, 0},
	{0, 0},
	{0, 0},
	{' ', ' '},
};

typedef struct{
    int elemCount;
    char buffer[BUFFER_SIZE];
    char nextToWrite; // Siguiente posicion a escribir
    char nextToRead; // Siguiente posicion a leer

} CycleBuffer;

static CycleBuffer inputBuffer;

static int nextToWrite = 0; //Siguiente posicion a escribir
static int nextToRead = 0; //Siguiente posicion a leer
static int countToRead = 0; //Cantidad de caracteres a leer
static int altKey = 0; // determina cuando se utiliza shift y capslock
static int shift = 0;
static int capsLock = 0;

static char characterFilter(char key) {
    // Primero, actualizamos el estado de los modificadores y descartamos el evento
    if(key == L_SHIFT_PRESS || key == R_SHIFT_PRESS) {
        shift = !shift; 
        return 0;
    }
    if(key == L_SHIFT_RELEASE || key == R_SHIFT_RELEASE) {
        shift = !shift;
        return 0;
    }
    if(key == CAPS_LOCK_PRESS) {
        capsLock = !capsLock;
        return 0;
    }
    
    // Evitamos índices fuera de rango
    if(key >= KEYS||key<0)
        return 0;
    
    // Para las letras se hace XOR entre shift y capsLock; para otros, se utiliza shift
    if((key >= 16 && key <= 25) || (key >= 30 && key <= 38) || (key >= 44 && key <= 50))
        altKey = (shift ^ capsLock) ? 1 : 0;
    else
        altKey = shift ? 1 : 0;
        
    return keyValues[key][altKey];
}

char canRead() {
  return inputBuffer.elemCount > 0;
}

uint8_t pollKeyboard() {
    while(!(get_keyboard_status() & 0x01));

    uint8_t scancode = get_keyboard_output();
    scancode = characterFilter(scancode);
	return scancode;

}

char getNextKey(char* c) {
    if (inputBuffer.elemCount > 0) {
        *c = inputBuffer.buffer[inputBuffer.nextToRead];
        inputBuffer.nextToRead = (inputBuffer.nextToRead + 1) % BUFFER_SIZE;
        inputBuffer.elemCount--;
        return 1;
    }

    *c = 0;
    return 0;
}

char saveKey() {
    char c = get_keyboard_output();
    c = characterFilter(c);

    if (inputBuffer.elemCount < BUFFER_SIZE) {
        inputBuffer.buffer[inputBuffer.nextToWrite] = c;
        inputBuffer.nextToWrite = (inputBuffer.nextToWrite + 1) % BUFFER_SIZE;
        inputBuffer.elemCount++;
    } else {
        // Buffer lleno: sobrescribimos el más viejo (nextToRead)
        inputBuffer.buffer[inputBuffer.nextToWrite] = c;
        inputBuffer.nextToWrite = (inputBuffer.nextToWrite + 1) % BUFFER_SIZE;
        inputBuffer.nextToRead = (inputBuffer.nextToRead + 1) % BUFFER_SIZE; 
    }

    return c;
}