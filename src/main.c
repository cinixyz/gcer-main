
#include <CommandBundles.h>
#include <stdbool.h>
#define LOW_BATTERY 

/*
 *
 *
 *  deprecated???? use botguy26????????????????????????????
 *
 *
 */

int rightAngle = -6;
int leftAngle = 8;


int main(){



    /*create_connect();
    while(1){
        turnLeftByAngle(4,20);
        create_stop();
        msleep(3000);
        turnRightByAngle(4,20);
        create_stop();
        msleep(3000);
    }*/
    
    


    //initializing functions
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
    
    /*
        create_stop();
    lower_Elevator_To_Get_BotGuy();
     create_stop();
    ao();
    //OPENCLAW
    enable_servo(CLAW_SERVO);
     claw(0);
    //TURN TO MOVE IN
    turnLeftByAngle(3,20);
    // msleep(100);
    create_stop;
    driveBackwardForSomeCM(24,70);
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
    turnRightByAngle(5,20);
    create_stop();
    */
    
    //msleep(30000);
    
    
   // msleep(10000);


    /*
    while(1){
        printf("LEFTBACK: %i RIGHTBACK %i\n", get_create_lcliff_amt(), get_create_rcliff_amt() );
        msleep(100);
        console_clear();
    } */
    /*
    while(1){
    driveForwardForSomeCM(10, 75);
        //msleep(1000);
     centerSpot(70, 25);
       //msleep(5000);
      driveBackwardForSomeCM(10, 75);
        //msleep(1000);
    backCenterSpot(70,25);
       // msleep(5000);
    }
    */




    /*
   // msleep(100);
    //OPEN CLAW
    enable_servo(CLAW_SERVO);
    claw(0);
    //TURN TO MOVE IN
   // turnRightByAngle(4,20);
   // msleep(100);
    create_stop;
   // driveBackwardForSomeCM(22,70);
    //LOWER TO GRAB BOTGUY
    lower_to_ground_position();
   // msleep(100);
    ao();*/

    //TEST CODE FOR DRIVE TILL BLACK 
    // driveTillBlack(150);
    //  msleep(10000);


    //removed because it is potentionally causing problems
    //enable_servos();
    //put this here to display the battery capacity



    //CENTERSPOT TEST
    /*
    printf("CENTERSPOT TEST");
    mod_backCenterSpot();
    create_stop();
    printf("PAUSE");
    msleep(30000);
	*/
    //printf("waiting for 28 seconds");
    //msleep(28000);



    /* TEST CODES
    while(1){
    moveElevatorByClicks(1, -35);
    ao();
     moveElevatorByTicksAndSpeed(-350, -300);
    ao();
    msleep(1000);
    moveElevatorByClicks(1, 30);
    ao();
    //moveElevatorByTicksAndSpeed(500, 150);
    moveElevatorByTicksAndSpeed(700, 150);
    ao();
    msleep(1000);
    }*/

    /*   
    moveElevatorByClicks(1, -70);
    ao();
    ao();
 	moveElevatorByTicksAndSpeed(-350, -300);
    ao();
  	msleep(1000);
    hardwareTestActivate();
    */

    //ELEVATOR UPDATE CODE
    /*while(1) {
   	moveElevatorByClicks(1, -40);
    ao();
    ao();
    moveElevatorByTicksAndSpeed(-450, -300);
    ao();
    ao();
    console_clear();
   	//driveForwardForSomeCM(6,75);
    ao();
    ao();

    //turnLeftByAngle(7,20);
    // msleep(1000);

    msleep(100);
    create_stop();
    moveElevatorByClicks(1, 40);
    ao();
    ao();

    moveElevatorByTicksAndSpeed(400, 300);
    ao();
    ao();
  //  turnRightByAngle(9,20); 
    create_stop();
    }*/


    goToLine();
    
    goToCenter(); 
    create_stop();

    //CenterSpot start
    //centerSpot(70,15);
    mod_centerSpot();
    create_stop();
    lower_Elevator_To_Get_BotGuy();
    ao();
    //OPENCLAW
    enable_servo(CLAW_SERVO);
     claw(0);
    //TURN TO MOVE IN
    
    // msleep(100);
        turnLeftByAngle(5,20);
    driveBackwardForSomeCM(21,70);
    create_stop();
   // turnLeftByAngle(6,20);
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
    /* msleep(100);
    driveForwardForSomeCM(20,70);
    msleep(100); */
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














	/*
    printf("position 3");


    moveElevatorByClicks(1, -30);
    ao();
    ao();
    moveElevatorByTicksAndSpeed(-350, -300);
    ao();
    ao();

    moveTillEnd(leftAngle, rightAngle);
    msleep(100);
    
    //either drivebackward or pushTillEnd gets to position 3
    driveBackwardForSomeCM(60,150);
    //might need this code
 	//pushTillEnd(leftAngle, rightAngle);*/
    










    //playDespacito();



    //hardwareTestActivate();


    disable_servo(LATCH_SERVO);
    disable_servo(CLAW_SERVO);
    create_disconnect();
    return 0;

}