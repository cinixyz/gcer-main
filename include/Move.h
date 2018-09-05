#ifndef MOVE_H
#define MOVE_H

#include <kipr/botball.h>
#include <stdbool.h>

#define REAL180 204
#define REAL90 102
#define BUMP 1
#define BLACK 1800
#define WHITE 2800
#define GRAY 1600
#define MIDBLACK 1470
#define BATT_TURN_FACTOR 0.375

void turnRightTillBlack();
void turnLeft180(int speed);
void turnRight180(int speed);
void turnLeft90(int speed);
void turnRight90(int speed);
void turnLeftBotGuy(int angle, int speed);
void turnRightBotGuy(int angle, int speed);
void turn(int angle);
void driveForwardTillBothBumped(int speed);
void driveForwardTillOneBumped(int speed);
void driveForwardForSomeCM(int inputDistance_cm, int speed);
void driveBackwardForSomeCM(int inputDistance_cm, int speed);
void driveTillBlack(int speed);
void driveTillLeftBlack(int speed);
void driveTillLeftFrontBlack(int speed);
void driveTillRightBlack(int speed);
void centerSpot(int RANGE, int SPIN);
void backCenterSpot(int RANGE, int SPIN);
void specialTurn();
void magicalTurn();
void mod_centerSpot();
void mod_backCenterSpot();


#endif
