#define B 0x000000
#define G 0x00FF00
#define R 0xFF0000
#define Y 0xFFFF00
#define C 0x00FFFF
#define M 0xFF00FF
#define P 0x800080
#define GRAY 0x808080
#define DARK_GRAY 0x404040
#define LIGHT_GRAY 0xC0C0C0
#define BLUE 0x0000FF
#define ORANGE 0xFFA500
#define PURPLE 0x800080
#define AQUA 0x00FFFF
#define WHITE 0xFFFFFF

uint32_t pos1_x = 0;    
uint32_t pos1_y = 0;
uint32_t pos2_x = 0;
uint32_t pos2_y = 0;
uint32_t ball_x = 0;
uint32_t ball_y = 0;
uint32_t hole_x = 0;
uint32_t hole_y = 0;
uint32_t vel1_x = 0;
uint32_t vel1_y = 0;
uint32_t acceleration1_x = 0;
uint32_t acceleration1_y = 0;
uint32_t angle1 = 0;
uint32_t vel2_x = 0;
uint32_t vel2_y = 0;
uint32_t acceleration2_x = 0;
uint32_t acceleration2_y = 0;
uint32_t angle2 = 0;


uint16_t Auto[][20] = {
    {0x0E70,0x0E70,0x0E70,0x0000,0x0000,0x0E70,0x0E70,0x0E70,0x0E70,0x0E70,0x0E70,0x0E70,0x0E70,0x0E70,0x0000,0x0810,0x0E70,0x0E70,0x0000,0x0E70,}, //amarrillo
    {0x0180,0x1188,0x2184,0x300C,0x2004,0x2184,0x318C,0x2184,0x2184,0x2184,0x2184,0x2184,0x2184,0x318C,0x300C,0x300C,0x318C,0x318C,0x318C,0x1188,},//rojo
    {0x0000,0x0000,0x1008,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,},//blanco
    {0x0000,0x0000,0x0000,0xCFF3,0xEFFB,0xE00B,0xC003,0xE00B,0x1008,0x1008,0x1008,0x1008,0x1008,0xC003,0xCFF3,0xC7E3,0xC003,0x0000,0x0000,0x0000,},//Gris

};

void drawBall(uint32_t x, uint32_t y) {
    
}
void play(){
    char c;
    while(sysKey(&c)!=0) {
        switch(c) {
            case 'w':
                acceleration_y--;
                ve
                break;
            case 's':
                pos1_y++;
                break;
            case 'a':
                pos1_x--;
                break;
            case 'd':
                pos1_x++;
                break;
            case 'i':
                pos2_y--;
                break;
            case 'k':
                pos2_y++;
                break;
            case 'j':
                pos2_x--;
                break;
            case 'l':
                pos2_x++;
                break;
        }
        drawBall(ball_x, ball_y);
    }
}


void Pongis(){
    
}
