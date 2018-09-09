#include <CommandBundles.h>
#include <stdbool.h>
#define LOW_BATTERY 

/*
 *
 *
 *  no sir
 *
 *
 */

int rightAngle = -6;
int leftAngle = 8;


int main(){

    // Init
    wait_for_light(0);
    shut_down_in(119);
    printf("Roomba not connected\n");
    create_write_byte(7);
    create_connect();
    console_clear();
    printf("We got this\n");
    create_full();

    int roombaBattery = getBatteryCapacity();
    printf("roombaBattery: %i\n", getBatteryCapacity());
    printf("waiting for 10 seconds\n");

    goToLine();
    
    goToCenter(); 
    create_stop();

    //CenterSpot start
    mod_centerSpot();
    create_stop();
    lower_Elevator_To_Get_BotGuy();
    ao();

    //OPENCLAW
    enable_servo(CLAW_SERVO);
    claw(0);

    //TURN TO MOVE IN
    turnLeftByAngle(5,20);
    driveBackwardForSomeCM(21,70);
    create_stop();

    //LOWER TO GRAB BOTGUY
   create_stop();
    msleep(500);

    //LOWER TO GRAB BOTGUY
    lower_to_ground_position();
    ao(); 
    driveBackwardForSomeCM(3,100);
    create_stop();

    //CLOSE CLAW
    claw(CLAW_CLOSE_POSITION);
    ao();
    turnRightByAngle(7,20);
    create_stop();

    //CenterSpot ENDS
    printf("WE GOT THIS YA\n");
    dragBotGuyAndOpenLatch1();
    moveElevatorByTicksAndSpeed(-100,-100);
    enable_servo(LATCH_SERVO);
    latch(OPEN_LATCH);
    dragBotGuyAndOpenLatch2();
    printf("WHY ISN'T ANYTHING WORKING DOG DAMMIT\n");
    dunkToTram(leftAngle, rightAngle);
    printf("Panic party?\n");
    pullTram();


    disable_servo(LATCH_SERVO);
    disable_servo(CLAW_SERVO);
    create_disconnect();
    return 0;

}