
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
    conv.i = (1 << 29) + (conv.i >> 1) - (1 << 22);  // ajuste mágico
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

}
void applyForces(body *b, float angle, float magnitude) {
    float s, c;
    sincosf(angle, &s, &c);
    b->vel_x += magnitude * c;
    b->vel_y += -magnitude * s;
}
void checkColissions(body*b1,body *pelota,body *hoyo){
    if(b1->x-b1->x_offset < 0|| b1->x+b1->x_offset > 1000) 
        b1->vel_x = -b1->vel_x;
    if(b1->y-b1->y_offset < 10|| b1->y+b1->y_offset > 700)
        b1->vel_y = -b1->vel_y; 
    if(pelota->x-pelota->x_offset < 0|| pelota->x+pelota->x_offset > 1800)
        pelota->vel_x = -pelota->vel_x;
    if(pelota->y-pelota->y_offset < 0|| pelota->y+pelota->y_offset > 700)
        pelota->vel_y = -pelota->vel_y;
    
float dx = pelota->x - b1->x;
float dy = pelota->y - b1->y;
float distancia = sqrtf(dx * dx + dy * dy);
float suma_radios = pelota->x_offset + b1->x_offset;

if (distancia <= suma_radios) {
    // Colisión detectada
    float angle;
    arctan(dy / dx, 10, &angle);
    applyForces(pelota, angle, b1->vel_x * 1.2f);
}
    if(pelota->x-pelota->x_offset < hoyo->x+hoyo->x_offset || pelota->x+pelota->x_offset > hoyo->x-hoyo->x_offset){
        if(pelota->y-pelota->y_offset < hoyo->y+hoyo->y_offset || pelota->y+pelota->y_offset > hoyo->y-hoyo->y_offset){
            Finish();
        }
    }
    
}


