
#include <pongisUtils.h>

static lastHit = 0;

float fabsf(float x) {
    return (x < 0.0f) ? -x : x;
}

int restaTruncada(int x) {
    return (x < 0) ? 0 : x;
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

void hitball(Body *b, Body *ball){
    int dx =  b->x - ball->x;
    int dy = b->y - ball->y;
    float distancia = sqrtf((float)(dx*dx + dy*dy));

    float suma_radios = OFFSET* 2.0 * FEELGOODCONSTANT;

    if (distancia <= suma_radios) {
        // Colisión detectada
        float angle;
        angle = arctan(dy,dx);
        
        float velocity = sqrtf(b->vel_x * b->vel_x + b->vel_y * b->vel_y);
        applyForces(ball, angle,  velocity * 1.4f+(ball->vel_x+ball->vel_y) * -0.4f);
        
        int timeElapsed = sysTimeTicks();
        
        if(timeElapsed - lastHit > 25){
            lastHit = timeElapsed;
            b->hits++;
        }

    }
}

void applyForces(Body *b,float angle,float magnitud){
    float s, c;
    sincosf(angle, &s, &c);
    b->vel_x += magnitud * c * (-1.0f);
    b->vel_y += magnitud * s;
}

