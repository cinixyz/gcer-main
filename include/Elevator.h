#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <kipr/botball.h>
#include <stdbool.h>
#include <HardwareComponents.h>

#define DEFAULT_ELEVATOR_SPEED 700

void moveElevatorByTicks(int ticks);
void moveElevatorByTicksAndSpeed(int ticks, int speed);
void moveElevatorByClicks(int requiredClicks , int speed);

#endif
