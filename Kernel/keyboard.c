
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
    uint8_t nextToWrite; // Next slot to write into
    uint8_t nextToRead; // Next slot to be read

} CycleBuffer;

// Main buffer for keyboard events
static CycleBuffer keyboardEvents;

// Keep track of these for upper and lower case 
static int shift = 0;
static int capsLock = 0;

static void enqueue(uint8_t event) {
    if (keyboardEvents.elemCount < BUFFER_SIZE) {
        keyboardEvents.buffer[keyboardEvents.nextToWrite] = event;
        keyboardEvents.nextToWrite = (keyboardEvents.nextToWrite + 1) % BUFFER_SIZE;
        keyboardEvents.elemCount++;
    } else {
        // Buffer full: overwrite the oldest one (nextToRead)
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

/* Checks if char should be in uppercase or not */
static char getChar(uint8_t event) {

	uint8_t uppercase = 0;
    // Check special keys
    if(capsLock || shift)
        uppercase = 1;
        
    return keyValues[event][uppercase];
}

static uint8_t isKeyPress(uint8_t event) {
    return event < KEYS_END && event > KEYS_START;
}

static uint8_t isChar(uint8_t event) {
    return isKeyPress(event) && event != L_SHIFT_PRESS && event != R_SHIFT_PRESS && event != CAPS_LOCK_PRESS;
}

char keyboardHasEvent() {
	return keyboardEvents.elemCount > 0;
}

char keyboardGetChar() {
    uint8_t event = keyboardGetKeyEvent();

    // While no char is pressed, keep asking for the next event on the queue
    while (!isChar(event)) {
        event = keyboardGetKeyEvent();
    }

    // Parse event into a char
    return getChar(event);
}

void keyboardSaveEvent() {
	
    uint8_t event = get_keyboard_output();

	// Keep track of special keys
	if (event == L_SHIFT_PRESS || event == R_SHIFT_PRESS) // Check shift state
		shift = 1;
	else if (event == BREAK_KEY(L_SHIFT_PRESS) || event == BREAK_KEY(R_SHIFT_PRESS))
		shift = 0;
	else if (event == CAPS_LOCK_PRESS) // Check caps lock
		capsLock = capsLock ? 0 : 1;	// Toggle it
	else if(event == ESC)
		saveRegs();

    enqueue(event);
}

uint8_t keyboardGetKeyEvent(){
    return dequeue();
}


