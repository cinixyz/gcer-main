#include <CommandBundles.h>

//elevator functions to grab botguy
void lower_Elevator_To_Get_BotGuy(){
    //lower claw to middle position
    moveElevatorByClicks(1, 40);
    ao();
    // msleep(100);
    //create_stop();
    printf("The First Has Clicked");
    msleep(100);
    //lower claw more just above the bump
  //OLD ELEVATOR THAT MIGHT WORK
    moveElevatorByTicksAndSpeed(300, 550);
    printf("The elevator has moved");
    ao();
    // msleep(2000);
    create_stop();
}

void lower_to_ground_position(){
    moveElevatorByClicks(1, 10);
    ao();
    printf("The Second has Clicked");
    // msleep(1000); 
    create_stop();
}


// rest of the functions

void goToLine(){
    printf("goToLine()\n");
    //turnLeftByAngle(50,250);
    turnLeftByAngle(40,120);
    create_stop();
    driveTillBlack(120);
    driveForwardForSomeCM(17, 280);
    driveTillLeftFrontBlack(100);
    driveForwardForSomeCM(3, 50);
    console_clear();
    printf("goToLine() Completed, Doing Next Step in 2 Seconds\n");
    //system("aplay /home/root/Documents/audio/Go_to_line.wav");
    console_clear();


}
void goToCenter(){
    
    //turnLeftBotGuy(45, 100);
    turnRightTillBlack();
    create_stop();
    msleep(15500);

   // driveBackwardForSomeCM(25,100);
    pi_LineFollow(35,120,0); // distance_cm, speed, delay
    create_stop();
    driveTillRightBlack(280);
    create_stop();
    driveForwardForSomeCM(6, 100);
    
    //THSI THE WHOLE FREAKING REASON WHY WE LOST THE FREAKING REGIIONALS!"!:WlqndzjsgvbojasdegfuljwaHNFcjgj
    //create_drive_direct(150,150);
      //msleep(400);
    
    
    create_stop();
    //turnLeft90(75);
    
    
    turnLeftByAngle(88,75);
    create_stop();
    driveBackwardForSomeCM(8, 300);
    //system("aplay /home/root/Documents/audio/Go_to_center.wav");
}
/*

void grabBotguy(){
    centerSpot(70,25);
    create_stop();
   // lightTurn();
    create_stop();
    lower_Elevator_To_Get_BotGuy();
    ao();
   // msleep(100);
 //   latch(CLOSE_LATCH);
    claw(0);
    msleep(100);
    turn(-7);
    msleep(100);

    // driveBackwardForSomeCM(15,100);
    //turn(-5);
    driveBackwardForSomeCM(27,70);
    //turn(-1);
    lower_to_ground_position();
    msleep(100);
    driveBackwardForSomeCM(3,100);
    //system("aplay /home/root/Documents/audio/juicy.wav");
}
*/

void dragBotGuyAndOpenLatch1(){
    //driveForwardForSomeCM(10,70);
    // create_stop();
    //   msleep(100);
    create_stop();
    
    //experimental take out
   msleep(100);
    
    
    // this needs to be increased to make sure that freaking botguy does not get freaking caught in the goddamn pipes kys
    driveForwardForSomeCM(30,70);
    create_stop();
    
    mod_centerSpot;
    create_stop();
    // msleep(1000);
    //moving to position two
    create_stop();
    moveElevatorByClicks(1, -30);
    ao();
    ao();
    moveElevatorByTicksAndSpeed(-50, -800);
    ao();
    ao();

    //   msleep(1000);
}

void dragBotGuyAndOpenLatch2(){
    create_stop();
    //msleep(1000);
    //moveElevatorByTicksAndSpeed(-150, -800);
    ao();
    //msleep(1000);
    //system("aplay /home/root/Documents/audio/Drag_Botguy.wav");
    printf("dragBotGuyAndOpenLatch2 STOP");
}

void dunkToTram(int left, int right){
    printf("DUNK TO TRAM ACTIVATED");
    turnRightByAngle(180,150);
    create_stop();
  	
    //   pi_LineFollow(15,3,0);

    //  msleep(1000);
    // driveForwardForSomeCM(6,100);
    // centerSpot(70,20);
    //  printf("Before");
    // moveElevatorByClicks(1, -150);
    moveElevatorByClicks(1, -70);
    ao();
    ao();
 moveElevatorByTicksAndSpeed(-350, -300);
    // msleep(1000);
    // moveElevatorByTicksAndSpeed(150, -200);
    ao();
    ao();
    // msleep(300);
    
    //backCenterSpot(50,15);
    mod_backCenterSpot();
    driveBackwardForSomeCM(3,100);
    // printf("After");
    create_stop();
    // msleep(500);
    turnLeftByAngle(7,20);
    create_stop();
    moveElevatorByClicks(1, 30);
    ao();
    ao();
    moveElevatorByTicksAndSpeed(450, 90);
    ao();
    ao();
    //    msleep(1000);
    //  msleep(100);
    create_stop();
    //system("aplay /home/root/Documents/audio/Dunk_to_Tray.wav");
    turnRightByAngle(9,20);
    
    
}

void pullTram(){
    printf("pulling the tram all the way to position 2\n");
    //Pull all the way back till bump
    mod_centerSpot(70,15);
    create_stop();
    // driveForwardForSomeCM(30,65);
    driveForwardTillOneBumped(150);
    //system("aplay /home/root/Documents/audio/Pull_Tram.wav");
    // Get claw out of the tram and move all the way back to poistion three so the claw and botguy isnt in the way
}


void moveTillEnd(int left, int right){
    //Driving all the way back till second line
    //I CHANGED THIS PLACE 
    driveBackwardForSomeCM(40,500);
    ao();
    ao();
    create_stop();
    msleep(100);
    turnLeftByAngle(180,75);
    ao();
    ao();
    create_stop();
   // centerSpot(50,30);
    mod_centerSpot();
    // bob
    create_stop();
    driveForwardTillOneBumped(200);
    create_stop();
    // msleep(100);
    create_stop();
    turnLeftByAngle(7,20);
    create_stop();
    moveElevatorByClicks(1, 30);
    ao();
    ao();
   moveElevatorByTicksAndSpeed(450, 90);
    ao();
    ao();
    //Put claw up and slam
    turnRightByAngle(9,20);
    create_stop();
}
void pushTillEnd(int left, int right){
    //Push all the way to middle tape 
    driveBackwardForSomeCM(15,75);
    // msleep(100);
    create_stop();
    //backCenterSpot(70,30);
    mod_backCenterSpot();
    create_stop();
    // msleep(100); 
    //start going up to dum
    //moveElevatorByClicks(1, -150);
    moveElevatorByClicks(1, -35);
    ao();
    ao();
  moveElevatorByTicksAndSpeed(-350, -300);
    ao();
    ao();
    driveForwardForSomeCM(5,75);
    turnLeftByAngle(7,20);
    create_stop();
    // msleep(1000);
    
    
    
    
    moveElevatorByClicks(1, 30);
    ao();
    ao();
   
    moveElevatorByTicksAndSpeed(450, 150);
    ao();
    ao();
    turnRightByAngle(9,20);
    //dump botball
    driveBackwardForSomeCM(30,75);
    mod_centerSpot(70,20);
    create_stop();
    driveBackwardForSomeCM(25,75);
    //moveElevatorByClicks(1, -150);
    moveElevatorByClicks(1, -35);
    ao();
    ao();
 moveElevatorByTicksAndSpeed(-350, -300);
    ao();
    ao();
    driveForwardForSomeCM(6,75);

    ao();
    ao();
    //turnLeftByAngle(7,20);
    // msleep(1000);
    create_stop();
    moveElevatorByClicks(1, 30);
    ao();
    ao();
    moveElevatorByTicksAndSpeed(500, 150);
    ao();
    ao();
    turnRightByAngle(9,20); 
    create_stop();
    //Put Claw up so it automatically centers and then put claw down.

}
