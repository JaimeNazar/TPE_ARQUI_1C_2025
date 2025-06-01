#define PI 3.1415926f
#include <pongisUtils.h>


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
void checkColissions(body*b1,body *pelota,body *hoyo){
    if(b1->x-b1->x_offset < 10|| b1->x+b1->x_offset > 1910) 
        b1->vel_x = -b1->vel_x;
    if(b1->y-b1->y_offset < 10|| b1->y+b1->y_offset > 1070)
        b1->vel_y = -b1->vel_y; 
    if(pelota->x-pelota->x_offset < 10|| pelota->x+pelota->x_offset > 1910)
        pelota->vel_x = -pelota->vel_x;
    if(pelota->y-pelota->y_offset < 10|| pelota->y+pelota->y_offset > 1070)
        pelota->vel_y = -pelota->vel_y;
    
    if(pelota->x-pelota->x_offset < b1->x+b1->x_offset || pelota->x+pelota->x_offset > b1->x-b1->x_offset){
        if(pelota->y-pelota->y_offset < b1->y+b1->y_offset || pelota->y+pelota->y_offset > b1->y-b1->y_offset){
            float angle;
            arctan((pelota->y - b1->y) / (pelota->x - b1->x), 10,&angle);
            applyForces(pelota, angle, pelota->vel_x * 1.2f); // Reduce speed by half on collision
        }
    }
    if(pelota->x-pelota->x_offset < hoyo->x+hoyo->x_offset || pelota->x+pelota->x_offset > hoyo->x-hoyo->x_offset){
        if(pelota->y-pelota->y_offset < hoyo->y+hoyo->y_offset || pelota->y+pelota->y_offset > hoyo->y-hoyo->y_offset){
            Finish();
        }
    }
    
}
void applyForces(body *b,float angle,float magnitud){
    float sin;
    float cos;
    sincosf(angle,&sin,&cos);
    b->vel_x = cos * magnitud;
    b->vel_y = sin * magnitud;
}

