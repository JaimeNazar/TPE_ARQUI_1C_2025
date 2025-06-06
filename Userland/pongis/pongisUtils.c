
#include <pongisUtils.h>

float fabsf(float x) {
    return (x < 0.0f) ? -x : x;
}
void sincosf(float angle, float *s, float *c) {
    // Normaliza el ángulo entre -PI y PI
    while (angle > PI) {
        angle -= 2.0f * PI;
    }
    while (angle < -PI) {
        angle += 2.0f * PI;
    }
    
    float angle2 = angle * angle;
    // Aproximación del seno (serie de Taylor hasta el término de x^7)
    *s = angle - (angle * angle2) / 6.0f + (angle * angle2 * angle2) / 120.0f - (angle * angle2 * angle2 * angle2) / 5040.0f;
    
    // Aproximación del coseno (serie de Taylor hasta el término de x^6)
    *c = 1 - angle2 / 2.0f + (angle2 * angle2) / 24.0f - (angle2 * angle2 * angle2) / 720.0f;
    
}
float sqrtf(float number) {
    if (number <= 0.0f) return 0.0f;

    union {
        float f;
        int i;
    } conv;

    conv.f = number;
    conv.i = (1 << 29) + (conv.i >> 1) - (1 << 22);  
    return conv.f;
}

float arctan(float y, float x) {
    if (x == 0.0f) {
        if (y > 0.0f)  return PI / 2;    //  +90°
        if (y < 0.0f)  return -PI / 2;   //  -90°
        return 0.0f;                    //  x=0, y=0 → arbitrario igual a 0
    }
    // Constante de ajuste; 0.28 es un valor común para buena aproximación en [−π/2, +π/2]
    const float A = 0.28f;

    float abs_y = fabsf(y);
    float abs_x = fabsf(x);
    float z = y / x;
    float atan;

    // Caso |z| < 1  → usamos aproximación directa
    if (fabsf(z) < 1.0f) {
        atan = z / (1.0f + A * z * z);
        if (x < 0.0f) {
            // x < 0, hay que desplazar π según signo de y
            if (y < 0.0f)      atan -= PI;
            else               atan += PI;
        }
    }
    // Caso |z| ≥ 1  → hacemos reflect en π/2
    else {
        atan = (PI / 2) - (x / y) / (1.0f + A * (x / y) * (x / y));
        if (y < 0.0f)     atan -= PI;
    }
    return atan;
}
void Finish(){
    end = 1;
    sysBeep(800,2);
    sysBeep(700,3);
    sysBeep(800,2);
    sysBeep(700,3);
}
void hitball(body *b,body *ball){
    int dx =  b->x - ball->x;
int dy = b->y - ball->y;
float distancia = sqrtf((float)(dx*dx + dy*dy));



float suma_radios = OFFSET* 2.0 * FEELGOODCONSTANT;

if (distancia <= suma_radios) {
    // Colisión detectada
    float angle;
    angle = arctan(dy,dx);
    
    float velocity = sqrtf(b->vel_x * b->vel_x + b->vel_y * b->vel_y);
    applyForces(ball, angle,  velocity * 1.4f);
    b->hits++;

}
}
void checkColissions(){
    if(p1.x-OFFSET< 10|| p1.x+OFFSET > 1000){
        sysBeep(800,2);
        p1.vel_x = -p1.vel_x * 1.5f;
    } 
    if(p1.y-OFFSET < 80|| p1.y+OFFSET > 700){
        sysBeep(800,2);
        p1.vel_y = -p1.vel_y * 1.5f; 
    }
    if(ball.x-OFFSET < 10|| ball.x+OFFSET > 1000){
        sysBeep(800,2);
        ball.vel_x = -ball.vel_x * 1.5f;
    }
        
    if(ball.y-OFFSET < 80|| ball.y+OFFSET > 700){
        sysBeep(800,2);
        ball.vel_y = -ball.vel_y * 1.5f;
    }
hitball(&p1, &ball);
if(player2Exists){
    if(p2.x-OFFSET< 10|| p2.x+OFFSET > 1000) 
        p2.vel_x = -p2.vel_x * 1.5f; ;
    if(p2.y-OFFSET < 80|| p2.y+OFFSET > 700)
        p2.vel_y = -p2.vel_y * 1.5f; 
    hitball(&p2, &ball);
    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;
    float distancia = sqrtf((float)(dx*dx + dy*dy));
    float suma_radios = OFFSET* 2.0 * FEELGOODCONSTANT;
    if (distancia <= suma_radios) {
        float aux = p2.vel_x;
        p2.vel_x = p1.vel_x;
        p1.vel_x = aux;
        aux = p2.vel_y;
        p2.vel_y = p1.vel_y;
        p1.vel_y = aux;
    }
}


int dx = ball.x - hole_x;
int dy = ball.y - hole_y;
float distancia = sqrtf(dx * dx + dy * dy);
float suma_radios = OFFSET* 2.0 * FEELGOODCONSTANT;
    if(distancia <= suma_radios){
        Finish();
    }

}
void applyForces(body *b,float angle,float magnitud){
    float s, c;
    sincosf(angle, &s, &c);
    b->vel_x += magnitud * c * (-1.0f);
    b->vel_y += magnitud * s;
}

