#ifndef PONGIS_UTILS_H
#define PONGIS_UTILS_H

#include <stdint.h>
#define PI 3.1415926f
typedef struct {
    uint64_t x;
    uint64_t y;
    float vel_x;
    float vel_y;
    int rotation;
    uint64_t max_speed;
    int x_offset;
    int y_offset;
} body;

void sincosf(float angle, float *s, float *c);
void arctan(double x, int terms, float *angle);
void applyForces(body *b, float angle, float magnitud);
void checkColissions(body *b1, body *pelota, body *hoyo);
void Finish();
void drawBall();
float fabsf(float x);

#endif