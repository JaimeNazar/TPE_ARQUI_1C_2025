#ifndef PONGIS_H
#define PONGIS_H

#include <stdint.h>

 uint32_t AutoL[][21];
 uint32_t AutoR[][21];
 uint32_t AutoD[][21];
 uint32_t AutoU[][21];
 uint32_t pelota[][15];

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

 body p1;
 body p2;
 body ball;

void drawBall(void);
void play(void);
void Pongis(void);

#endif // PONGIS_H