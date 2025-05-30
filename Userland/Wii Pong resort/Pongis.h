#ifndef PONGIS_H
#define PONGIS_H

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

void drawBall(void);
void play(void);
void Pongis(void);

#endif // PONGIS_H