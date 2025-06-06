#ifndef PONGIS_UTILS_H
#define PONGIS_UTILS_H

#include <stdint.h>
#include <stdlib.h>
#define PI 3.1415926f
#define OFFSET 10
#define FEELGOODCONSTANT 2.5
typedef struct {
    uint64_t x;
    uint64_t y;
    float vel_x;
    float vel_y;
    int rotation;
    int hits;
} body;
extern uint64_t hole_x;
extern uint64_t hole_y;
extern char end;
extern body p1;
extern body p2;
extern body ball;
extern char player2Exists;
void sincosf(float angle, float *s, float *c);
float arctan(float y, float x);
void applyForces(body *b, float angle, float magnitud);
void checkColissions();
void Finish();
void drawBall();
float fabsf(float x);

#endif