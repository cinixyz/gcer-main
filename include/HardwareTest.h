#ifndef HARDWARETEST_H
#define HARDWARETEST_H

#include <kipr/botball.h>
#include <stdbool.h>
#include <HardwareComponents.h>

//elevator buttons
#define GO_UP digital(1) == 1
#define GO_DOWN digital(2) == 1
#define INCREASE_ELEVATOR_SPEED digital(7) == 1
#define REDUCE_ELEVATOR_SPEED digital(9) == 1
#define ELEVATOR_SPEED_INCREMENT 5
#define TEST_SPEED 50

//claw buttons
#define TEST_CLOSE_CLAW digital(3) == 1
#define TEST_OPEN_CLAW digital(4) == 1

//latch buttons
#define TEST_OPEN_LATCH digital(5) == 1
#define TEST_CLOSE_LATCH digital(8) == 1

//misc
#define END_HARDWARE_TEST digital(10) == 1


void hardwareTestActivate();

#endif
