
#include <keyboard.h>
#define KEYS 58
#define BUFFER_SIZE 1000
#define ESC 0x01
#define ENTER 28
#define BACKSPACE 14
#define TAB 15	
#define L_SHIFT_PRESS 0x2A
#define L_SHIFT_RELEASE 0xAA
#define R_SHIFT_PRESS 0x36
#define R_SHIFT_RELEASE 0xB6
#define CAPS_LOCK_PRESS 0x3A
#define MAX_PRESS_KEY 0x70

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

static char buffer[BUFFER_SIZE] = {0};//Buffer ciclico de teclado
static int nextToWrite = 0; //Siguiente posicion a escribir
static int nextToRead = 0; //Siguiente posicion a leer
static int countToRead = 0; //Cantidad de caracteres a leer
int altKey = 0; // determina cuando se utiliza shift y capslock
int shift = 0;
int capsLock = 0;

void keyPress() {
    uint8_t sc = get_keyboard_output();

    // Procesamos modificadores sin filtrar (presión y liberación)
    
		
        if (sc > 0x81 && sc!=R_SHIFT_RELEASE && sc!=L_SHIFT_RELEASE)
            return; 
        
        sc = characterFilter(sc);
		if (sc == 0x00) // Si el código es 0, no hacemos nada
			return; // Si es un código de liberación, no hacemos nada más

    // Si pasó la validación, lo agrego al buffer
    if(countToRead < BUFFER_SIZE) {
        buffer[nextToWrite++] = sc;
        countToRead++;
        if(nextToWrite >= BUFFER_SIZE)
            nextToWrite = 0;
    }
}
char getNextKey(char* c){ //devuelve 1 si hay un caracter para leer, 0 si no hay y lo pone en c
  if(countToRead > 0) {
    if(nextToRead >= BUFFER_SIZE) {
      nextToRead = 0;
    }
    *c = buffer[nextToRead++];
    countToRead--;
    return 1; // Hay un caracter para leer
  }
  return 0; // No hay caracteres para leer
}
char characterFilter(char key) {
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
    if(key >= KEYS)
        return 0;
    
    // Para las letras se hace XOR entre shift y capsLock; para otros, se utiliza shift
    if((key >= 16 && key <= 25) || (key >= 30 && key <= 38) || (key >= 44 && key <= 50))
        altKey = (shift ^ capsLock) ? 1 : 0;
    else
        altKey = shift ? 1 : 0;
        
    return keyValues[key][altKey];
}
char canRead() {
  return countToRead > 0;
}
