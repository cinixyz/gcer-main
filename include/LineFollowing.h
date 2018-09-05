#ifndef LINEFOLLOWING_H
#define LINEFOLLOWING_H

#include <kipr/botball.h>
#include <stdbool.h>

#define right_P 0.4
#define right_I 0.5
#define right_D 0.3
#define left_P 0.3
#define left_I 0.4
#define left_D 0.3

void getSensorVal();
void SetOutputLimits(double Min, double Max);
void pi_LineFollow(int inputDistance_cm, int speed, int delay);

#endif
