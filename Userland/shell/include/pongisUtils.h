#ifndef PONGIS_UTILS_H
#define PONGIS_UTILS_H

#include <stdint.h>
typedef struct {
    uint64_t x;
    uint64_t y;
    uint64_t acceleration_x;
    uint64_t acceleration_y;
    uint64_t vel_x;
    uint64_t vel_y;
    float angle;
    uint64_t max_speed;
    uint64_t max_acceleration;
    int x_offset;
    int y_offset;
} body;

void sincosf(float angle, float *s, float *c);
void arctan(double x, int terms, float *angle);
void applyForces(body *b, float angle, float magnitud);
void checkColissions(body *b1, body *pelota, body *hoyo);
void Finish();
void drawBall();

#endif