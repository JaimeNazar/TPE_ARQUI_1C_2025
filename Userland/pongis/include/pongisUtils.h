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
    uint8_t r_left; // For simultaneous keyboard input
    uint8_t r_right;
    uint8_t foward;
    int lives;
} Body;

int subtractTruncated(int x);
void sincosf(float angle, float *s, float *c);
float arctan(float y, float x);
float sqrtf(float number);
float fabsf(float x);
int iabsi(int x);

void applyForces(Body *b, float angle, float magnitud);
void hitball(Body *b, Body *ball);

#endif