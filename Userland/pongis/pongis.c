#include <stdint.h>
#include <pongis.h>
#define MAXVEL 10

#define B 0x000000
#define G 0x00FF00
#define R 0xFF0000
#define Y 0xFFFF00
#define C 0x00FFFF
#define M 0xFF00FF
#define P 0x800080
#define GRAY 0x808080
#define DG 0x404040
#define LG 0xC0C0C0
#define BLUE 0x0000FF
#define ORANGE 0xFFA500
#define AQUA 0x00FFFF
#define W 0xFFFFFF


uint32_t nave[][21]={
    {0x000000,0x000000,0x030000,0x03C000,0x03F000,0x03FC00,0x03C700,0x0329C0,0x0329F0,0x0286FC,0x024000,0x0286FC,0x0329F0,0x0329C0,0x03C700,0x03FC00,0x03F000,0x03C000,0x030000,0x000000,0x000000},
    {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x043800,0x04D600,0x04D600,0x013900,0x01FFFF,0x013900,0x04D600,0x04D600,0x043800,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

    {0x000000,0x000004,0x00001A,0x000074,0x0001EC,0x0007D8,0x001FB8,0x006370,0x0194F0,0x079CE0,0x0F6360,0x072280,0x036340,0x019C80,0x009480,0x006300,0x003F00,0x001E00,0x000E00,0x000400,0x000000},
    {0x000000,0x000002,0x000004,0x000008,0x000010,0x000020,0x000040,0x001C80,0x006B00,0x006300,0x009C80,0x00DD80,0x009C80,0x046300,0x066B00,0x001C00,0x004000,0x006000,0x000000,0x000000,0x000000},

    {0x000000,0x000000,0x000A00,0x000A00,0x001B00,0x001B00,0x003B80,0x003B80,0x0071C0,0x004A40,0x00CA60,0x00B1A0,0x018030,0x01B1B0,0x03C478,0x03CA78,0x07F1FC,0x07FFFC,0x000000,0x000000,0x000000},
    {0x000400,0x000400,0x000400,0x000400,0x000400,0x000400,0x000400,0x000400,0x000E00,0x003580,0x003580,0x004E40,0x007FC0,0x004E40,0x003580,0x003580,0x000E00,0x000000,0x0071C0,0x000000,0x000000},
    
    {0x000000,0x040000,0x0B0000,0x05C000,0x06F000,0x037C00,0x03BD00,0x01DAC0,0x01E530,0x00E73C,0x00D8DE,0x00489C,0x0058D8,0x002730,0x002520,0x0018C0,0x001F80,0x000F00,0x000E00,0x000400,0x000000},
    {0x000000,0x080000,0x040000,0x020000,0x010000,0x008000,0x004000,0x002700,0x001AC0,0x0018C0,0x002720,0x003760,0x002720,0x0018C8,0x001AD8,0x000700,0x000000,0x000040,0x0000C0,0x000000,0x000000},

    {0x000000,0x000000,0x000018,0x000078,0x0001F8,0x0007F8,0x001C78,0x007298,0x01F298,0x07EC28,0x000048,0x07EC28,0x01F298,0x007298,0x001C78,0x0007F8,0x0001F8,0x000078,0x000018,0x000000,0x000000},
    {0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000384,0x000D64,0x000D64,0x001390,0x1FFFF0,0x001390,0x000D64,0x000D64,0x000384,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

    {0x000000,0x000400,0x000E00,0x000F00,0x001F80,0x0018C0,0x002520,0x002730,0x0058D8,0x00289C,0x00D8DE,0x00E73C,0x01E530,0x01D8C0,0x03BF00,0x037C00,0x06F000,0x05C000,0x0B0000,0x040000,0x000000},
    {0x000000,0x000000,0x000000,0x0000C0,0x000040,0x000700,0x001ACC,0x0018C4,0x002720,0x003760,0x002720,0x0018C0,0x001AC0,0x002700,0x004000,0x008000,0x010000,0x020000,0x040000,0x080000,0x000000},

    {0x000000,0x000000,0x000000,0x07FFFC,0x07F1FC,0x03CA78,0x03C478,0x01B1B0,0x018030,0x00B1A0,0x00CA60,0x004A40,0x0071C0,0x003B80,0x003B80,0x001B00,0x001B00,0x000A00,0x000A00,0x000000,0x000000},
    {0x000000,0x000000,0x0071C0,0x000000,0x000E00,0x003580,0x003580,0x004E40,0x007FC0,0x004E40,0x003580,0x003580,0x000E00,0x000400,0x000400,0x000400,0x000400,0x000400,0x000400,0x000400,0x000400},

    {0x000000,0x000400,0x000E00,0x001E00,0x003F00,0x006300,0x009480,0x019C80,0x036340,0x072240,0x0F6360,0x079CE0,0x0194F0,0x006B70,0x0017B8,0x0007D8,0x0001EC,0x000074,0x00001A,0x000004,0x000000},
    {0x000000,0x000000,0x006000,0x004000,0x000000,0x001C00,0x036B00,0x026300,0x009C80,0x00DD80,0x009C80,0x006300,0x006B00,0x001C80,0x000040,0x000020,0x000010,0x000008,0x000004,0x000002,0x000000},
    {0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF,0xFFFFFF}
};
float angulos[8]={0,PI/4.0,PI/2.0,(3.0/4.0)*PI,PI,(5.0/4.0)*PI,(3.0/2.0)*PI,(7.0/4.0)*PI};
uint32_t blackHole[][21]={
    {0x000780,0x000580,0x061F06,0x0761CE,0x078334,0x030218,0x028218,0x026618,0x1FFFFF,0x140C25,0x1C06C7,0x040786,0x0405C4,0x020E7E,0x06081E,0x0D381E,0x08F026,0x0FF0C0,0x00BF00,0x00E000,0x000000},
    {0x000000,0x000000,0x000000,0x001E00,0x007CC0,0x00E0E0,0x024060,0x018020,0x000000,0x030018,0x030018,0x030018,0x030018,0x018000,0x01C060,0x00C0E0,0x000FC0,0x000F00,0x000000,0x000000,0x000000},
    {0x000000,0x000000,0x000000,0x000000,0x000000,0x001D00,0x003D80,0x0019C0,0x000000,0x00F3C0,0x03F920,0x00F860,0x00FA20,0x007180,0x003780,0x000700,0x000000,0x000000,0x000000,0x000000,0x000000}
};


uint32_t asteroide[][21]={
    {0x003F80,0x00FFE0,0x003FC0,0x000F80,0x000FC0,0x0007E2,0x0007FE,0x1007FF,0x180FFF,0x18FFFF,0x1E3FFF,0x1FFFE3,0x1FFFC1,0x1FFF80,0x0FFF80,0x0FFF80,0x07FF80,0x03F880,0x01FDC0,0x00FFE0,0x003F80},
    {0x000000,0x00001C,0x01C03E,0x07F07F,0x07F03E,0x0FF81C,0x0FF800,0x0FF800,0x07F000,0x07F000,0x01C000,0x00001C,0x00003E,0x00007F,0x00007F,0x00007F,0x00027F,0x00077F,0x00023E,0x00001C,0x000000},
};
char player2Exists = 0;

body p1 = {50,50, 0, 0, 0};
body p2 = {100, 100, 0, 0, 0};
body ball = {200,200, 0, 0, 0};
uint64_t hole_x = 0;
uint64_t hole_y = 0;
char end = 0;
int flag = 0;

void drawBall() {
    sysConfigBitmap(3, DG, 21);
    sysDrawBitmap(ball.x-OFFSET,ball.y-OFFSET,asteroide[0]);
    sysConfigBitmap(3, LG, 21);
    sysDrawBitmap(ball.x-OFFSET,ball.y-OFFSET,asteroide[1]);
}
void drawPlayer(int player){
    if(player == 1){
    sysConfigBitmap(3, BLUE, 21);
    sysDrawBitmap(p1.x-OFFSET, p1.y-OFFSET, nave[p1.rotation * 2]);
    sysConfigBitmap(3, R, 21);
    sysDrawBitmap(p1.x-OFFSET, p1.y-OFFSET, nave[p1.rotation * 2 + 1]);
    }
    else{
    sysConfigBitmap(3, G, 21);
    sysDrawBitmap(p2.x-OFFSET, p2.y-OFFSET, nave[p2.rotation * 2]);
    sysConfigBitmap(3, R, 21);
    sysDrawBitmap(p2.x-OFFSET, p2.y-OFFSET, nave[p2.rotation * 2 + 1]);
    }
}
void drawHole(){
    sysConfigBitmap(3,C,21);
    sysDrawBitmap(hole_x-OFFSET,hole_y-OFFSET,blackHole[0]);
    sysConfigBitmap(3,P,21);
    sysDrawBitmap(hole_x-OFFSET,hole_y-OFFSET,blackHole[1]);
    sysConfigBitmap(3,BLUE,21);
    sysDrawBitmap(hole_x-OFFSET,hole_y-OFFSET,blackHole[2]);
}
void drawPlayfield(){
    sysConfigBitmap(50, DG, 21);
    sysDrawBitmap(0, 0, nave[16]);
    sysConfigBitmap(40, B, 21);
    sysDrawBitmap(0, 60, nave[16]);
    sysConfigBitmap(40, B, 21);
    sysDrawBitmap(400, 60, nave[16]);
}


void play(void) {
    clearGame();

    

    char c = sysKey();
    float s, cs; 
    switch(c) {
        case 'w':
            sincosf(angulos[p1.rotation], &s, &cs);
            // Calcula la aceleración en función del ángulo seleccionado en el ciclo
            p1.vel_x += (int)(5 * cs);
            p1.vel_y += (int)(5 * (-s));
            break;
        case 'a':
            // Incrementa el índice de rotación cíclicamente (0 a 7)
            p1.rotation = (p1.rotation + 1) % 8;
            break;
        case 'd':
            // Decrementa el índice de rotación cíclicamente (usando módulo 8)
            p1.rotation = (p1.rotation + 7) % 8;
            break;
            case 'i':
            sincosf(angulos[p2.rotation], &s, &cs);
            // Calcula la aceleración en función del ángulo seleccionado en el ciclo
            p2.vel_x += (int)(5 * cs);
            p2.vel_y += (int)(5 * (-s));
            break;
        case 'j':
            // Incrementa el índice de rotación cíclicamente (0 a 7)
            p2.rotation = (p2.rotation + 1) % 8;
            break;
        case 'l':
            // Decrementa el índice de rotación cíclicamente (usando módulo 8)
            p2.rotation = (p2.rotation + 7) % 8;
            break;
        default:
            break;
    }
    checkColissions(&p1,&ball);
    
    float drag = 0.9f; 
    p1.vel_x *= drag;
    p1.vel_y *= drag;
    if(player2Exists){
        p2.vel_x *= drag;
        p2.vel_y *= drag;
    }
    
    ball.vel_x *= drag;
    ball.vel_y *= drag;


// Si es suficientemente bajo, ponelo en 0
    if (fabsf(p1.vel_x) < 0.5f) p1.vel_x = 0;
    if (fabsf(p1.vel_y) < 0.5f) p1.vel_y = 0;
    if (fabsf(ball.vel_x) < 0.5f) ball.vel_x = 0;
    if (fabsf(ball.vel_y) < 0.5f) ball.vel_y = 0;
    p1.x += p1.vel_x;
    p1.y += p1.vel_y;
    ball.x += ball.vel_x;
    ball.y += ball.vel_y*-1;
    if(player2Exists){
    if (fabsf(p2.vel_x) < 0.5f) p2.vel_x = 0;
    if (fabsf(p2.vel_y) < 0.5f) p2.vel_y = 0;
    p2.x += p1.vel_x;
    p2.y += p1.vel_y;
    drawPlayer(2);
    }
    // Dibuja la nave usando el sprite correspondiente:
    drawPlayer(1);
    drawBall();
    drawHole();
    
    sysDraw();

}

void pongis(int playerCount) {
    sysClear();
    sysConfigBitmap(50, DG, 21);
    sysDrawBitmap(0, 0, nave[16]);
    if(playerCount==2){
        player2Exists = 1;
    }
    sysClear();
    drawPlayfield();
    int randTick = sysTimeTicks();
    switch(randTick%4) {
        case 0:
            hole_x = 100;
            hole_y = 100;
            p1.x = 100;
            p1.y = 500;
            p2.x = 400;
            p2.y = 500;
            ball.x = 600;
            ball.y = 600;
            break;
        case 1:
            hole_x = 800;
            hole_y = 100;
            p1.x = 100;
            p1.y = 500;
            p2.x = 400;
            p2.y = 500;
            ball.x = 200;
            ball.y = 600;
            break;
        case 2:
            hole_x = 200;
            hole_y = 700;
            p1.x = 100;
            p1.y = 500;
            p2.x = 400;
            p2.y = 500;
            ball.x = 600;
            ball.y = 200;
            break;
        case 3:
            hole_x = 800;
            hole_y = 700;
            p1.x = 100;
            p1.y = 500;
            p2.x = 400;
            p2.y = 500;
            ball.x = 200;
            ball.y = 200;
            break;
    }
    while(1){
        play();
    }
}
clearGame(){
    sysConfigBitmap(3, B, 21);
    sysDrawBitmap(p1.x-OFFSET,p1.y-OFFSET,nave[16]);
    if(player2Exists){
        sysDrawBitmap(p2.x-OFFSET,p2.y-OFFSET,nave[16]);
    }
    sysDrawBitmap(ball.x-OFFSET,ball.y-OFFSET,nave[16]);
}
//typedef struct {
   // uint64_t x;
    //uint64_t y;
    //uint64_t acceleration_x;
    //uint64_t acceleration_y;
    //uint64_t vel_x;
    //uint64_t vel_y;
    //float angle;
    //uint64_t max_speed;
    //uint64_t max_acceleration;
    //int x_offset;
    //int y_offset;
//} body;