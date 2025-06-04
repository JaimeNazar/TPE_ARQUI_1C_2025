#ifndef PONGIS_UTILS_H
#define PONGIS_UTILS_H

#include <stdint.h>
#include <stdlib.h>
#define PI 3.1415926f
#define OFFSET 10
typedef struct {
    uint64_t x;
    uint64_t y;
    float vel_x;
    float vel_y;
    int rotation;
} body;
extern uint64_t hole_x;
extern uint64_t hole_y;
extern char end;
extern int flag;
void sincosf(float angle, float *s, float *c);
void arctan(double x, int terms, float *angle);
void applyForces(body *b, float angle, float magnitud);
void checkColissions(body *b1, body *pelota, body *hoyo);
void Finish();
void drawBall();
float fabsf(float x);

#endif