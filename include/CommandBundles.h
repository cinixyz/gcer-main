#ifndef COMMANDBUNDLES_H
#define COMMANDBUNDLES_H

#include <kipr/botball.h>
#include <stdbool.h>


#include <HardwareComponents.h>
#include <Elevator.h>
#include <HardwareTest.h>
#include <LineFollowing.h>
#include <Misc.h>
#include <Move.h>
#include <Servo.h>
#include <turnByLight.h>

#define DELAY 100

//elevator helper functions
void lower_Elevator_To_Get_BotGuy();
void lower_to_ground_position();

//main code
void goToLine();
void goToCenter();
void grabBotguy();
void dragBotGuyAndOpenLatch1();
void dragBotGuyAndOpenLatch2();
void dunkToTram(int left, int right);
void moveTillEnd(int left, int right);
void pushTillEnd(int left, int right);
void pullTram();
void step5();
void step6();
void step7();

#endif
