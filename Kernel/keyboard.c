
#include <keyboard.h>


static unsigned char keyValues[KEYS_END][2] = {
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
	{'a', 'A'}, //30
	{'s', 'S'},
	{'d', 'D'},
	{'f', 'F'},
	{'g', 'G'},
	{'h', 'H'},
	{'j', 'J'},
	{'k', 'K'},
	{'l', 'L'}, //38
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
	{'m', 'M'}, //50
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
    uint8_t buffer[BUFFER_SIZE];
    uint8_t nextToWrite; // Siguiente posicion a escribir
    uint8_t nextToRead; // Siguiente posicion a leer

} CycleBuffer;

static CycleBuffer keyboardEvents;

static int nextToWrite = 0; //Siguiente posicion a escribir
static int nextToRead = 0; //Siguiente posicion a leer
static int countToRead = 0; //Cantidad de caracteres a leer
static int altKey = 0; // determina cuando se utiliza shift y capslock
static int shift = 0;
static int capsLock = 0;

static void enqueue(uint8_t event) {
    if (keyboardEvents.elemCount < BUFFER_SIZE) {
        keyboardEvents.buffer[keyboardEvents.nextToWrite] = event;
        keyboardEvents.nextToWrite = (keyboardEvents.nextToWrite + 1) % BUFFER_SIZE;
        keyboardEvents.elemCount++;
    } else {
        // Buffer lleno: sobrescribimos el más viejo (nextToRead)
        keyboardEvents.buffer[keyboardEvents.nextToWrite] = event;
        keyboardEvents.nextToWrite = (keyboardEvents.nextToWrite + 1) % BUFFER_SIZE;
        keyboardEvents.nextToRead = (keyboardEvents.nextToRead + 1) % BUFFER_SIZE; 
    }
}

static uint8_t dequeue() {
    if (keyboardEvents.elemCount > 0) {
        uint8_t toReturn = keyboardEvents.buffer[keyboardEvents.nextToRead];
        keyboardEvents.nextToRead = (keyboardEvents.nextToRead + 1) % BUFFER_SIZE;
        keyboardEvents.elemCount--;
        return toReturn;
    }
    return 0;
}

static char characterFilter(char key) {
    if(key == CAPS_LOCK_PRESS) {
        capsLock = !capsLock;
        return 0;
    }
    
    // Evitamos índices fuera de rango
    if(key >= KEYS_END||key<KEYS_START)
        return 0;
    
    // Para las letras se hace XOR entre shift y capsLock; para otros, se utiliza shift
    if((key >= 16 && key <= 25) || (key >= 30 && key <= 38) || (key >= 44 && key <= 50))
        altKey = (shift ^ capsLock) ? 1 : 0;
    else
        altKey = shift ? 1 : 0;
        
    return keyValues[key][altKey];
}

static uint8_t isKeyPress(uint8_t event) {
    return event < KEYS_END && event > KEYS_START;
}

char keyboardHasEvent() {
  return keyboardEvents.elemCount > 0;
}

uint8_t keyboardPoll() {
    while(!(get_keyboard_status() & 0x01));

    uint8_t scancode = get_keyboard_output();
    scancode = characterFilter(scancode);
	return scancode;

}

char keyboardGetChar() {
    uint8_t event = keyboardGetKeyEvent();

    // While no char is pressed, keep asking for the next event on the queue
    while (!isKeyPress(event)) {
        event = keyboardGetKeyEvent();
    }

    // Parse event into a char
    return characterFilter(event);
}

void keyboardSaveEvent() {
    uint8_t event = get_keyboard_output();

	// Check shift state
	if (event == L_SHIFT_PRESS || event == R_SHIFT_PRESS)
		shift = 1;
	else if (event == BREAK_KEY(L_SHIFT_PRESS) || event == BREAK_KEY(R_SHIFT_PRESS))
		shift = 0;

    enqueue(event);
}

uint8_t keyboardGetKeyEvent(){
    return dequeue();
}


