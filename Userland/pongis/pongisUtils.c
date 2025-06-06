
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

void arctan(double x, int terms, float *angle) {
    if (x > 1.0) {
        float aux;
        arctan(1 / x, terms, &aux);
        *angle = PI / 2 - aux;
        return;
    } else if (x < -1.0) {
        float aux;
        arctan(1 / x, terms, &aux);
        *angle = -PI / 2 - aux;
        return;
    }

    float result = 0.0;
    float power = x;
    int sign = 1;

    for (int n = 0; n < terms; n++) {
        int denom = 2 * n + 1;
        result += sign * (power / denom);
        power *= x * x;
        sign *= -1;
    }

    *angle = result;
}
void Finish(){
    end = 1;
    sysClear();


}
void checkColissions(body*b1,body *pelota){
    if(b1->x-OFFSET< 0|| b1->x+OFFSET > 1000) 
        b1->vel_x = -b1->vel_x;
    if(b1->y-OFFSET < 50|| b1->y+OFFSET > 700)
        b1->vel_y = -b1->vel_y; 
    if(pelota->x-OFFSET < 0|| pelota->x+OFFSET > 1000)
        pelota->vel_x = -pelota->vel_x;
    if(pelota->y-OFFSET < 50|| pelota->y+OFFSET > 700)
        pelota->vel_y = -pelota->vel_y;
    
float dx =  b1->x - pelota->x;
float dy = b1->y - pelota->y;
printf("x: %f, y: %f, x2:%f , y2:%f\n", b1->x, b1->y,dx,dy);
float distancia = sqrtf(dx + dy);
float suma_radios = OFFSET*10;

if (distancia <= suma_radios) {
    // Colisión detectada
    float angle;
    
    applyForces(pelota, angle, b1->vel_x * 1.2f);
}
dx = pelota->x - hole_x;
dy = pelota->y - hole_y;
distancia = sqrtf(dx * dx + dy * dy);
suma_radios = OFFSET*7;
    if(distancia <= suma_radios){
        Finish();        
    }
    
}
void applyForces(body *b,float angle,float magnitud){
    sysWrite(1, "Applying forces\n", 16);
}

