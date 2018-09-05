#ifndef TURNBYLIGHT_H
#define TURNBYLIGHT_H
#include <kipr/botball.h>

#define G_DEGREESTOMILISECFACTOR 11.666666667
void ciniTurn(int angle, int speed);
void turnLeftByAngle(int angle, int speed);
void turnRightByAngle(int angle, int speed);

#endif