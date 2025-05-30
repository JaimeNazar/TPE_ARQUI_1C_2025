#ifndef PONGIS_UTILS_H
#define PONGIS_UTILS_H
#include <Pongis.h>

void sincosf(float angle, float *s, float *c);
void arctan(double x, int terms, float *angle);
void applyForces(body *b, float angle, float magnitud);
void checkColissions(body *b1, body *pelota, body *hoyo);
void Finish();
void drawBall();

#endif