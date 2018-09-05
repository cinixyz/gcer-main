#ifndef SERVO_H
#define SERVO_H

#include <kipr/botball.h>
#include <stdbool.h>

#include <HardwareComponents.h>
#define CLOSE_LATCH 0
#define OPEN_LATCH 1

void latch(int pos);
void claw(int pos);


#endif
