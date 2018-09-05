#include <Move.h>
#include <stdbool.h>
#include <stdlib.h>

void mod_centerSpot(){

    //int GRAY = 2500;   //value for gray

    int MBLACK = 500;   //value for black 

    int MWHITE = 2000;   //value for white 
	int speed = 15;
    
    int LEFTBACK = get_create_lcliff_amt();
    int RIGHTBACK = get_create_rcliff_amt();
    
    bool LEFTBACK_isGray = (LEFTBACK >= MBLACK) && (LEFTBACK <= MWHITE);
    bool RIGHTBACK_isGray = (RIGHTBACK >= MBLACK) && (RIGHTBACK <= MWHITE);
    
    //printf("TEST %i\n", abs(LEFTBACK-RIGHTBACK));
    printf("Driving towards gray line\n");
    while(!LEFTBACK_isGray && !RIGHTBACK_isGray) {
        LEFTBACK = get_create_lcliff_amt();
        RIGHTBACK = get_create_rcliff_amt();
        LEFTBACK_isGray = (LEFTBACK >= MBLACK) && (LEFTBACK <= MWHITE);
    	RIGHTBACK_isGray = (RIGHTBACK >= MBLACK) && (RIGHTBACK <= MWHITE);
        printf("LEFTBACK: %i %i RIGHTBACK: %i %i \n", get_create_rcliff_amt(), LEFTBACK_isGray, get_create_lcliff_amt(), RIGHTBACK_isGray);
        create_drive_direct (25, 25);
    }    
    create_stop();
    printf("Reached Gray. Beginning alignment.\n");
    //begin alignment 
    //condition: keep aligning until the left sensor gray value is close
    //enough to the right sensor gray value
    /***
     * 9 Different Cases:
     * 1. L-BLACK R-WHITE
     * 2. L-BLACK R-GRAY
     * 3. L-BLACK R-BLACK
     * 4. L-GRAY R-WHITE
     * 5. L-GRAY R-GRAY (IDEAL CASE - If difference between sensors is close enough - end while)
     * 6. L-GRAY R-BLACK
     * 7. L-WHITE R-WHITE
     * 8. L-WHITE R-GRAY
     * 9. L-WHITE R-BLACK
    ***/
    int stuck = 0;
    while(abs(LEFTBACK-RIGHTBACK) >= 20 && (!LEFTBACK_isGray || !RIGHTBACK_isGray) && stuck <= 5){
		LEFTBACK = get_create_lcliff_amt();
        RIGHTBACK = get_create_rcliff_amt();
        
        LEFTBACK_isGray = (LEFTBACK >= MBLACK) && (LEFTBACK <= MWHITE);
        RIGHTBACK_isGray = (RIGHTBACK >= MBLACK) && (RIGHTBACK <= MWHITE);
        
        //GRAY CASES FIRST
        //THEN BLACK
        //THEN WHITE
        
        //CASE 1: L-BLACK R-GRAY
        if(LEFTBACK <= MBLACK && RIGHTBACK_isGray){
            //turn left to re-align, don't move RIGHTBACK
            printf("LEFTBACK: %i RIGHTBACK: %i  L-BLACK R-GRAY\n", LEFTBACK,RIGHTBACK);
            create_drive_direct(-speed,(speed-5));
            msleep(100);
            create_stop();
        }
        
        //CASE 2: L-GRAY R-WHITE
        //LEFTBACK_isGray = (LEFTBACK <= BLACK) && (LEFTBACK >= WHITE);
        else if(LEFTBACK_isGray && RIGHTBACK >= MWHITE){
            //turn left to re-align, don't move LEFTBACK
            printf("LEFTBACK: %i RIGHTBACK: %i  L-GRAY R-WHITE\n", LEFTBACK,RIGHTBACK);
            create_drive_direct(-(speed-5),speed); //pivot on LEFT
            msleep(100);
            create_stop();
        }
        
        //CASE 3: L-GRAY R-GRAY
        else if(LEFTBACK_isGray && RIGHTBACK_isGray){
            printf("LEFTBACK: %i RIGHTBACK: %i  L-GRAY R-GRAY\n", LEFTBACK,RIGHTBACK);
            printf("GRAY GRAY CASE BUT DIFF TOO LARGE - INFINITE LOOP\n");
            int oscillation = 0;
            int difference = abs(LEFTBACK-RIGHTBACK);
            while(abs(LEFTBACK-RIGHTBACK) >= 20 && oscillation <= 2){
                LEFTBACK = get_create_lcliff_amt();
        		RIGHTBACK = get_create_rcliff_amt();
                difference = abs(LEFTBACK-RIGHTBACK);
            	if(LEFTBACK >= RIGHTBACK){
            		printf("Oscillation: %i\n", oscillation);
                    printf("L-High Gray(towards white) R-Low Gray(towards black)\n");
                    create_drive_direct(15,-15); //turn right
            		msleep(100);
            		create_stop();
            	}
                else if(LEFTBACK <= RIGHTBACK){
                    printf("Oscillation: %i\n", oscillation);
            		printf("L-Low Gray(towards black) R-High Gray(towards white)\n");
                    create_drive_direct(-15,15); //turn left
            		msleep(100);
            		create_stop();
            	}
                oscillation++;
            }
            printf("Broke out of while\n");
            printf("Difference: %i\n", difference);
            break;
        }
        
        //CASE 4: L-GRAY R-BLACK
        else if(LEFTBACK_isGray && RIGHTBACK <= MBLACK){
            //turn right to re-align, don't move LEFTBACK
            printf("LEFTBACK: %i RIGHTBACK: %i  L-GRAY R-BLACK\n", LEFTBACK,RIGHTBACK);
            create_drive_direct((speed-5),-speed); //pivot on LEFT
            msleep(100);
            create_stop();
        }
        
        //CASE 5: L-BLACK R-BLACK
        else if(LEFTBACK <= MBLACK && RIGHTBACK <= MBLACK){
            //drive backward. too far forward
            printf("LEFTBACK: %i RIGHTBACK: %i  L-BLACK R-BLACK\n", LEFTBACK,RIGHTBACK);
            create_drive_direct(-speed,-speed);
            msleep(100);
            create_stop();
        }
        
        //CASE 6: L-BLACK R-WHITE
        if(LEFTBACK <= MBLACK && RIGHTBACK >= MWHITE){
            //turn left to re-align
            printf("LEFTBACK: %i RIGHTBACK: %i  L-BLACK R-WHITE\n",LEFTBACK,RIGHTBACK);
            
            //create_drive_direct(speed,-speed);
            create_drive_direct(-speed,speed);
            msleep(100);
            create_stop();
        }
        
        //CASE 7: L-WHITE R-BLACK
        else if(LEFTBACK >= MWHITE && RIGHTBACK <= MBLACK){
            //turn right to re-align
            printf("LEFTBACK: %i RIGHTBACK: %i  L-WHITE R-BLACK\n", LEFTBACK,RIGHTBACK);
            create_drive_direct(speed,-speed); 
            msleep(100);
            create_stop();
        }
        
        //CASE 8: L-WHITE R-GRAY
        //RIGHTBACK_isGray = (RIGHTBACK <= BLACK) && (RIGHTBACK >= WHITE);
        else if(LEFTBACK >= MWHITE && RIGHTBACK_isGray){
            //turn right to re-align, don't move RIGHTBACK
            printf("LEFTBACK: %i RIGHTBACK: %i  L-WHITE R-GRAY\n", LEFTBACK,RIGHTBACK);
            //create_drive_direct(speed,-(speed-5)); //pivot on RIGHT CHANGE HERE
            create_drive_direct(speed,-speed); //pivot on RIGHT
            msleep(100);
            stuck++;
            create_stop();
        }
        
        //CASE 9: L-WHITE R-WHITE
        else if(LEFTBACK >= MWHITE && RIGHTBACK >= MWHITE){
            //drive forward, went too much backward
            printf("LEFTBACK: %i RIGHTBACK: %i  L-WHITE R-WHITE\n", LEFTBACK,RIGHTBACK);
            create_drive_direct(speed,speed);
            msleep(100);
            create_stop();
        }
        printf("Difference: %i\n", abs(LEFTBACK-RIGHTBACK));
        printf("Stuck: %i", stuck);
    }
    
    printf("Finished CenterSpot\n");
}

void mod_backCenterSpot(){

    //int GRAY = 2500;   //value for gray

    int MBLACK = 500;   //value for black 

    int MWHITE = 2000;   //value for white 
	int speed = 15;
    
    int LEFTBACK = get_create_lcliff_amt();
    int RIGHTBACK = get_create_rcliff_amt();
    
    bool LEFTBACK_isGray = (LEFTBACK >= MBLACK) && (LEFTBACK <= MWHITE);
    bool RIGHTBACK_isGray = (RIGHTBACK >= MBLACK) && (RIGHTBACK <= MWHITE);
    
    //printf("TEST %i\n", abs(LEFTBACK-RIGHTBACK));
    printf("Driving backwards towards gray line\n");
    while(!LEFTBACK_isGray && !RIGHTBACK_isGray) {
        LEFTBACK = get_create_lcliff_amt();
        RIGHTBACK = get_create_rcliff_amt();
        LEFTBACK_isGray = (LEFTBACK >= MBLACK) && (LEFTBACK <= MWHITE);
    	RIGHTBACK_isGray = (RIGHTBACK >= MBLACK) && (RIGHTBACK <= MWHITE);
        printf("LEFTBACK: %i %i RIGHTBACK: %i %i \n", get_create_rcliff_amt(), LEFTBACK_isGray, get_create_lcliff_amt(), RIGHTBACK_isGray);
        create_drive_direct (-25, -25);
    }    
    create_stop();
    printf("Reached Gray. Beginning alignment.\n");
    //begin alignment 
    //condition: keep aligning until the left sensor gray value is close
    //enough to the right sensor gray value
    /***
     * 9 Different Cases:
     * 1. L-BLACK R-WHITE
     * 2. L-BLACK R-GRAY
     * 3. L-BLACK R-BLACK
     * 4. L-GRAY R-WHITE
     * 5. L-GRAY R-GRAY (IDEAL CASE - If difference between sensors is close enough - end while)
     * 6. L-GRAY R-BLACK
     * 7. L-WHITE R-WHITE
     * 8. L-WHITE R-GRAY
     * 9. L-WHITE R-BLACK
    ***/
    
    while(abs(LEFTBACK-RIGHTBACK) >= 20 && (!LEFTBACK_isGray || !RIGHTBACK_isGray)){
		LEFTBACK = get_create_lcliff_amt();
        RIGHTBACK = get_create_rcliff_amt();
        
        LEFTBACK_isGray = (LEFTBACK >= MBLACK) && (LEFTBACK <= MWHITE);
        RIGHTBACK_isGray = (RIGHTBACK >= MBLACK) && (RIGHTBACK <= MWHITE);
        
        //GRAY CASES FIRST
        //THEN BLACK
        //THEN WHITE
        
        //CASE 1: L-BLACK R-GRAY
        if(LEFTBACK <= MBLACK && RIGHTBACK_isGray){
            //turn right to re-align, don't move RIGHTBACK
            printf("LEFTBACK: %i RIGHTBACK: %i  L-BLACK R-GRAY\n", LEFTBACK,RIGHTBACK);
            create_drive_direct(speed,-(speed-5));
            msleep(100);
            create_stop();
        }
        
        //CASE 2: L-GRAY R-WHITE
        //LEFTBACK_isGray = (LEFTBACK <= BLACK) && (LEFTBACK >= WHITE);
        else if(LEFTBACK_isGray && RIGHTBACK >= MWHITE){
            //turn right to re-align, don't move LEFTBACK
            printf("LEFTBACK: %i RIGHTBACK: %i  L-GRAY R-WHITE\n", LEFTBACK,RIGHTBACK);
            create_drive_direct((speed-5),-speed); //pivot on LEFT
            msleep(100);
            create_stop();
        }
        
        //CASE 3: L-GRAY R-GRAY
        else if(LEFTBACK_isGray && RIGHTBACK_isGray){
            printf("LEFTBACK: %i RIGHTBACK: %i  L-GRAY R-GRAY\n", LEFTBACK,RIGHTBACK);
            printf("GRAY GRAY CASE BUT DIFF TOO LARGE - INFINITE LOOP\n");
            int oscillation = 0;
            int difference = abs(LEFTBACK-RIGHTBACK);
            while(abs(LEFTBACK-RIGHTBACK) >= 20 && oscillation <= 2){
                LEFTBACK = get_create_lcliff_amt();
        		RIGHTBACK = get_create_rcliff_amt();
                difference = abs(LEFTBACK-RIGHTBACK);
            	if(LEFTBACK >= RIGHTBACK){
            		printf("Oscillation: %i\n", oscillation);
                    printf("L-High Gray(towards white) R-Low Gray(towards black)\n");
                    create_drive_direct(-15,15); //turn left
            		msleep(100);
            		create_stop();
            	}
                else if(LEFTBACK <= RIGHTBACK){
                    printf("Oscillation: %i\n", oscillation);
            		printf("L-Low Gray(towards black) R-High Gray(towards white)\n");
                    create_drive_direct(15,-15); //turn right
            		msleep(100);
            		create_stop();
            	}
                oscillation++;
            }
            printf("Broke out of while\n");
            printf("Difference: %i\n", difference);
            break;
        }
        
        //CASE 4: L-GRAY R-BLACK
        else if(LEFTBACK_isGray && RIGHTBACK <= MBLACK){
            //turn left to re-align, don't move LEFTBACK
            printf("LEFTBACK: %i RIGHTBACK: %i  L-GRAY R-BLACK\n", LEFTBACK,RIGHTBACK);
            create_drive_direct(-(speed-5),speed); //pivot on LEFT
            msleep(100);
            create_stop();
        }
        
        //CASE 5: L-BLACK R-BLACK
        else if(LEFTBACK <= MBLACK && RIGHTBACK <= MBLACK){
            //drive forward. too far backward
            printf("LEFTBACK: %i RIGHTBACK: %i  L-BLACK R-BLACK\n", LEFTBACK,RIGHTBACK);
            create_drive_direct(speed,speed);
            msleep(100);
            create_stop();
        }
        
        //CASE 6: L-BLACK R-WHITE
        if(LEFTBACK <= MBLACK && RIGHTBACK >= MWHITE){
            //turn right to re-align
            printf("LEFTBACK: %i RIGHTBACK: %i  L-BLACK R-WHITE\n",LEFTBACK,RIGHTBACK);
            create_drive_direct(speed,-speed);
            msleep(100);
            create_stop();
        }
        
        //CASE 7: L-WHITE R-BLACK
        else if(LEFTBACK >= MWHITE && RIGHTBACK <= MBLACK){
            //turn left to re-align
            printf("LEFTBACK: %i RIGHTBACK: %i  L-WHITE R-BLACK\n", LEFTBACK,RIGHTBACK);
            create_drive_direct(-speed,speed); 
            msleep(100);
            create_stop();
        }
        
        //CASE 8: L-WHITE R-GRAY
        //RIGHTBACK_isGray = (RIGHTBACK <= BLACK) && (RIGHTBACK >= WHITE);
        else if(LEFTBACK >= MWHITE && RIGHTBACK_isGray){
            //turn left to re-align, don't move RIGHTBACK
            printf("LEFTBACK: %i RIGHTBACK: %i  L-WHITE R-GRAY\n", LEFTBACK,RIGHTBACK);
            create_drive_direct(-speed,(speed-5)); //pivot on RIGHT
            msleep(300);
            create_stop();
        }
        
        //CASE 9: L-WHITE R-WHITE
        else if(LEFTBACK >= MWHITE && RIGHTBACK >= MWHITE){
            //drive backward, went too much forward
            printf("LEFTBACK: %i RIGHTBACK: %i  L-WHITE R-WHITE\n", LEFTBACK,RIGHTBACK);
            create_drive_direct(-speed,-speed);
            msleep(100);
            create_stop();
        }
        printf("Difference: %i\n", abs(LEFTBACK-RIGHTBACK));
    }
    
    printf("Finished CenterSpot\n");
}



void turnRightTillBlack(){
    
    
    int rightSensor = get_create_rfcliff_amt();
    
    while(rightSensor >= BLACK){
        
        rightSensor = get_create_rfcliff_amt();
        create_spin_CCW(30);
        console_clear();
        printf("rightSensor:%i\n", rightSensor);
    }
    
    create_stop();
}

void turn(int angle) {

    if (angle > 0) {
        printf("Turn Right 90\n");
        set_create_normalized_angle(0);
        int currentAngle = get_create_normalized_angle();
        double capacity = (double) get_create_battery_capacity();
        double charge = (double) get_create_battery_charge() ;

        double dpercent = charge / capacity;

        double turnFactor = (100 - dpercent) * BATT_TURN_FACTOR + 100;
        while (currentAngle > -angle) {
            printf("cA %i, -a %i\n", currentAngle, -angle);
            create_spin_CW(25);
            currentAngle = get_create_normalized_angle();
            printf("%i\n",get_create_normalized_angle());
        }

        create_stop();
    }
    if (angle < 0) {
        printf("Turn left 90\n");
        set_create_normalized_angle(0);
        int currentAngle = get_create_normalized_angle();
        currentAngle = 0;
        double capacity = (double) get_create_battery_capacity();
        double charge = (double) get_create_battery_charge() ;

        double dpercent = charge / capacity;

        double turnFactor = (100 - dpercent) * BATT_TURN_FACTOR + 100;
        while (currentAngle < -angle) {
            create_spin_CCW(25);
            currentAngle = get_create_normalized_angle();
            printf("%i\n",get_create_normalized_angle());

            create_stop();
        }
    }

}

void turnLeft180(int speed)
{

    printf("Turn left 180");
    set_create_normalized_angle(0);
    int currentAngle = get_create_normalized_angle();
    while (currentAngle < REAL180) {
        create_spin_CCW(speed);
        currentAngle = get_create_normalized_angle();
        printf("%i\n",get_create_normalized_angle());
    }

    create_stop();

}

void turnRight180(int speed)
{

    printf("Turn Right 180");
    set_create_normalized_angle(0);
    int currentAngle = get_create_normalized_angle();
    while (currentAngle > -REAL180) {
        create_spin_CW(speed);
        currentAngle = get_create_normalized_angle();
        printf("%i\n",get_create_normalized_angle());
    }

    create_stop();

}

void turnLeft90(int speed)
{

    printf("Turn left 90");
    set_create_normalized_angle(0);
    int currentAngle = get_create_normalized_angle();
    while (currentAngle < REAL90) {
        create_spin_CCW(speed);
        currentAngle = get_create_normalized_angle();
        printf("%i\n",get_create_normalized_angle());
    }

    create_stop();

}

void turnRight90(int speed)
{

    printf("Turn Right 90");
    set_create_normalized_angle(0);
    int currentAngle = get_create_normalized_angle();
    while (currentAngle > -REAL90) {
        create_spin_CW(speed);
        currentAngle = get_create_normalized_angle();
        printf("%i\n",get_create_normalized_angle());
    }

    create_stop();

}

void turnLeftBotGuy(int angle, int speed)
{

    printf("Turn left %i\n", angle);
    set_create_normalized_angle(0);
    int currentAngle = get_create_normalized_angle();
    while (currentAngle < angle) {
        create_spin_CCW(speed);
        currentAngle = get_create_normalized_angle();
        printf("%i\n",get_create_normalized_angle());
    }

    create_stop();

}

void turnRightBotGuy(int angle, int speed)
{

    printf("Turn Right %i\n", angle);
    set_create_normalized_angle(0);
    int currentAngle = get_create_normalized_angle();
    while (currentAngle > -angle) {
        create_spin_CW(speed);
        currentAngle = get_create_normalized_angle();
        printf("%i\n",get_create_normalized_angle());
    }

    create_stop();

}

void driveForwardTillBothBumped(int speed){

    while(1){
        create_drive_direct(speed,speed);
        printf("driving\n");
        if( get_create_lbump() == BUMP && get_create_rbump() == BUMP){break;}

    }

    printf("not driving");
    create_stop();

}

void driveForwardTillOneBumped(int speed){

    while(1){
        create_drive_direct(speed,speed);
        printf("driving\n");
        if( get_create_lbump() == BUMP || get_create_rbump() == BUMP){break;}

    }

    printf("not driving");
    create_stop();

}

void driveForwardForSomeCM(int inputDistance_cm, int speed)
{

    set_create_distance(0);

    int inputDistance_mm = inputDistance_cm * 10.125;
    int currentDistance_mm = get_create_distance();

    while(currentDistance_mm < inputDistance_mm)
    {
        create_drive_direct(speed,speed);
        msleep(10);
        currentDistance_mm = get_create_distance();
        printf("length: %i\n", currentDistance_mm);
    }

    create_stop();

}

void driveBackwardForSomeCM(int inputDistance_cm, int speed)
{

    set_create_distance(0);
    speed*=-1;

    int inputDistance_mm = inputDistance_cm *10.125 * -1;
    int currentDistance_mm = get_create_distance();

    while(currentDistance_mm > inputDistance_mm)
    {
        create_drive_direct(speed,speed);
        msleep(10);
        currentDistance_mm = get_create_distance();
    }


    create_stop();

}

void driveTillBlack(int speed)
{

    bool needCheck = true;
    create_drive_direct(speed, speed);
    printf("driving\n");
    while(needCheck){
        int checkLeft = get_create_lcliff_amt();
        int checkRight = get_create_rcliff_amt();
        if(checkLeft <= BLACK || checkRight <= BLACK) needCheck = false;
        else if (checkLeft == 1) printf("left\n");
        else if (checkRight == 1) printf("right\n");
        else{
            printf ("drving right: %i left: %i\n", checkRight, checkLeft);
            msleep(10);
        }
    }
    printf("stop");
     int checkLeft = get_create_lcliff_amt();
        int checkRight = get_create_rcliff_amt();
 printf ("drving right: %i left: %i\n", checkRight, checkLeft);
    create_stop();

}

void driveTillLeftBlack(int speed)
{
   
    bool needCheck = true;
    create_drive_direct(speed, speed);
    printf("driving\n");
    while(needCheck){
     
int checkLeft = get_create_lcliff_amt();
        if(checkLeft <= BLACK) needCheck = false;
        else if (checkLeft == 1) printf("left\n");
        else{
            printf ("drving right: %i\n", checkLeft);
            msleep(100);
        }
    }
    int checkLeft = get_create_lcliff_amt();
    printf("stop");
printf ("drving LEFT VALUE: %i\n", checkLeft);
    create_stop();

}

void driveTillLeftFrontBlack(int speed)
{
 
    bool needCheck = true;
    create_drive_direct(speed, speed);
    printf("driving\n");
    while(needCheck){
      
 		int checkLeft = get_create_lfcliff_amt();
        if(checkLeft <= BLACK) needCheck = false;
        else if (checkLeft == 1) printf("left\n");
        
        else{
            printf ("drving right: %i\n", checkLeft);
            msleep(10);
        }
        
    }
     int checkLeft = get_create_lfcliff_amt();
    printf("stop");
 printf ("drving right: %i\n", checkLeft);
    create_stop();

}


void driveTillRightBlack(int speed)
{

    bool needCheck = true;
    create_drive_direct(speed, speed);
    printf("driving\n");
    while(needCheck){
        int checkRight = get_create_rcliff_amt();

        if(checkRight <= BLACK) {
            printf ("black value found: %i\n", checkRight);
            needCheck = false;
        }
        else{
            printf ("drving right: %i\n", checkRight);
            //console_clear();
            create_drive_direct(70,70);
            // pi_LineFollow(10,100,0);
            msleep(10);
        }
    }
    create_stop();
}

void centerSpot(int RANGE, int SPIN) {

    //bool needCheck = true;

    int checkRight;
    int checkLeft;
    checkRight = get_create_rcliff_amt();
    checkLeft = get_create_lcliff_amt();

    printf("starting to center\n");

    while(checkRight >= GRAY && checkLeft >= GRAY ) {
        checkRight = get_create_rcliff_amt();
        checkLeft = get_create_lcliff_amt();
        create_drive_direct (100, 100);
		
    }
	printf("Sees gray");
    int counter = 0;
    while(counter < 240) {

        checkRight = get_create_rcliff_amt();
        checkLeft = get_create_lcliff_amt();
		
        //L-WHITE R-WHITE
        if (checkRight >= GRAY && checkLeft >= GRAY ) {
            create_drive_direct (30, 30);
            printf("go forward Right: %i     Left: %i\n", checkRight, checkLeft);
        }
		
        //L-BLACK R-WHITE
        else if (checkRight >= GRAY && checkLeft <= GRAY) {
            create_drive_direct(-20, -20);
            printf("right is on white: %i    Left: %i\n", checkRight, checkLeft);
            create_spin_CCW(SPIN);
        }
		//L-WHITE R-BLACK
        else if (checkRight <= GRAY && checkLeft >= GRAY) {
            create_drive_direct(-20, -20);
            printf("left is on white: %i   Right: %i\n", checkLeft, checkRight);
            create_spin_CW(SPIN);
        }
        
		//L-BLACK R-BLACK
        //this will only happen when both is less than GRAY
        else if (checkLeft <= GRAY && checkRight <= GRAY) {
            printf("Stop Right: %i    Stop Left:   %i\n", checkLeft , checkRight);

            int sumRight = checkRight - checkLeft;
            printf("sumRight Before: %i\n", sumRight);

            //getting the absolute value
            if (sumRight <= 0) {
                sumRight *= -1;
                printf("sumRight Multiplied: %i\n", sumRight);
            }else{
                printf("sumRight: %i\n",sumRight );
            }

            if (sumRight < RANGE) {
                printf("100 less 1 Right: %i  Left: %i  sumRight: %i\n", checkRight, checkLeft, sumRight);
                return;
                //needCheck = false;
            }else{
                printf("Doesn't work\n");
            }

        }

        // when left is less than 900 (on black) and right is more than 900 (more on white)
        else if (checkLeft <= MIDBLACK && checkRight >= MIDBLACK) {
            create_drive_direct(-20,-20);
            printf("right is GRAY: %i\n", checkRight);
            create_spin_CCW(SPIN);

        }

        // when left is more than 900 (on white) and right is less than 900 (more on black)
        else if (checkLeft >= MIDBLACK && checkRight <= MIDBLACK) {

            create_drive_direct(-20,-20);
            printf("left is GRAY: %i\n", checkRight);
            create_spin_CW(SPIN);
        }

        else if (checkRight <= MIDBLACK && checkLeft <= MIDBLACK) {
            create_drive_direct(-35 , -35);
            printf("Less than MIDBLACK Right: %i   Left: %i\n", checkRight, checkLeft);

        }

        else if (checkRight >= MIDBLACK && checkLeft >= MIDBLACK) {

            if (checkRight < GRAY && checkLeft < GRAY) {
                printf("Code Finished Right: %i    Left: %i\n", checkRight , checkLeft);
                //needCheck = false;
                return;

            }else{
                printf("In the area Right: %i    Left: %i\n", checkRight , checkLeft);
                create_drive_direct(-30,-30);
            }

        }

        else {
            //needCheck = false;
            return;
            printf("Code Finished Right: %i    Left: %i\n", checkRight , checkLeft);
        }
        counter++;
        msleep(5);

    }

}





void backCenterSpot(int RANGE, int SPIN) {

    int checkRight = get_create_rcliff_amt();
    int checkLeft = get_create_lcliff_amt();
      int sumRight = checkRight - checkLeft;
    printf("starting to center\n");

    while(checkRight >= GRAY && checkLeft >= GRAY ) {
        checkRight = get_create_rcliff_amt();
        checkLeft = get_create_lcliff_amt();
        create_drive_direct (-200, -200);
        printf("WTF");
    }
    
    int counter = 0;
    while(counter<240) {

        checkRight = get_create_rcliff_amt();
        checkLeft = get_create_lcliff_amt();

        if (checkRight >= GRAY && checkLeft >= GRAY ) {
            create_drive_direct (-30, -30);
            //printf("go forward Right: %i     Left: %i\n", checkRight, checkLeft);
        }

        else if (checkRight >= GRAY && checkLeft <= GRAY) {
            create_drive_direct(20, 20);
            //printf("right is on white: %i    Left: %i\n", checkRight, checkLeft);
            create_spin_CW(SPIN);
        }

        else if (checkRight <= GRAY && checkLeft >= GRAY) {
            create_drive_direct(20, 20);
            //printf("left is on white: %i   Right: %i\n", checkLeft, checkRight);
            create_spin_CCW(SPIN);
        }

        //this will only happen when both is less than GRAY
        else if (checkLeft <= GRAY && checkRight <= GRAY) {
            //printf("Stop Right: %i    Stop Left:   %i\n", checkLeft , checkRight);

               // int sumRight = checkRight - checkLeft;
                //printf("sumRight Before: %i\n", sumRight);

                //getting the absolute value
                if (sumRight <= 0) {
                    sumRight *= -1;
                    //printf("sumRight Multiplied: %i\n", sumRight);
                }else{
                    printf("sumRight: %i\n",sumRight );
                }

                if (sumRight < RANGE) {
                    //printf("100 less 1 Right: %i  Left: %i  sumRight: %i\n", checkRight, checkLeft, sumRight);
                    return;
                }else{
                    printf("Doesn't work\n");
                }

            }

            // when left is less than 900 (on black) and right is more than 900 (more on white)
            else if (checkLeft <= MIDBLACK && checkRight >= MIDBLACK) {
                create_drive_direct(20,20);
                //printf("right is GRAY: %i\n", checkRight);
                create_spin_CW(SPIN);

            }

            // when left is more than 900 (on white) and right is less than 900 (more on black)
            else if (checkLeft >= MIDBLACK && checkRight <= MIDBLACK) {

                create_drive_direct(20,20);
                //printf("left is GRAY: %i\n", checkRight);
                create_spin_CCW(SPIN);
            }

            else if (checkRight <= MIDBLACK && checkLeft <= MIDBLACK) {
                create_drive_direct(35 , 35);
                //printf("Less than MIDBLACK Right: %i   Left: %i\n", checkRight, checkLeft);

            }

            else if (checkRight >= MIDBLACK && checkLeft >= MIDBLACK) {

                if (checkRight < GRAY && checkLeft < GRAY) {
                    //printf("Code Finished Right: %i    Left: %i\n", checkRight , checkLeft);
                    return;

                }else{
                    //printf("In the area Right: %i    Left: %i\n", checkRight , checkLeft);
                    create_drive_direct(30,30);
                }

            }

            else {
                return;
                //printf("Code Finished Right: %i    Left: %i\n", checkRight , checkLeft);
            }
        	//console_clear();
        	printf("counter: %i\n", counter);
            msleep(5);
        	counter++;
            printf("CheckRight: %i  CheckLeft: %i  sumRight: %i\n", checkRight, checkLeft, sumRight);

        }
}

void specialTurn(){
    
    int rightSensor = get_create_rcliff_amt();
    int leftSensor = get_create_lcliff_amt();
    
    while( (rightSensor > 2700 && rightSensor < 2800) && (leftSensor> 1100 && leftSensor <1200) ){
        rightSensor = get_create_rcliff_amt();
    	leftSensor = get_create_lcliff_amt();
        create_spin_CCW(20);
    }
    
    create_stop();
    
}




  


/*
void centerSpot(int RANGE, int SPIN) {

    bool needCheck = true;

    int checkRight;
    int checkLeft;
    checkRight = get_create_rcliff_amt();
    checkLeft = get_create_lcliff_amt();

    printf("starting to center\n");

    while(checkRight >= GRAY && checkLeft >= GRAY ) {
        checkRight = get_create_rcliff_amt();
        checkLeft = get_create_lcliff_amt();
    create_drive_direct(60, 60);

    }
    
    while(needCheck) {
	
   // int counter = 0;
 //   while(counter < 180) {

        checkRight = get_create_rcliff_amt();
        checkLeft = get_create_lcliff_amt();

        if (checkRight >= GRAY && checkLeft >= GRAY ) {
                    create_drive_direct(20, 20);
            printf("go forward Right: %i     Left: %i\n", checkRight, checkLeft);
        }

        else if (checkRight >= GRAY && checkLeft <= GRAY) {
            create_drive_direct(-20, -20);
            printf("right is on white: %i    Left: %i\n", checkRight, checkLeft);
            create_spin_CCW(SPIN);
        }

        else if (checkRight <= GRAY && checkLeft >= GRAY) {
            create_drive_direct(-20, -20);
            printf("left is on white: %i   Right: %i\n", checkLeft, checkRight);
            create_spin_CW(SPIN);
        }

        //this will only happen when both is less than GRAY
        else if (checkLeft <= GRAY && checkRight <= GRAY) {
            printf("Stop Right: %i    Stop Left:   %i\n", checkLeft , checkRight);

            int sumRight = checkRight - checkLeft;
            printf("sumRight Before: %i\n", sumRight);

            //getting the absolute value
            if (sumRight <= 0) {
                sumRight *= -1;
                printf("sumRight Multiplied: %i\n", sumRight);
            }else{
                printf("sumRight: %i\n",sumRight );
            }

            if (sumRight < RANGE) {
                printf("100 less 1 Right: %i  Left: %i  sumRight: %i\n", checkRight, checkLeft, sumRight);
              //  return;
                needCheck = false;
               // return;
            }else{
                printf("Doesn't work\n");
            }

        }

        // when left is less than 900 (on black) and right is more than 900 (more on white)
        else if (checkLeft <= MIDBLACK && checkRight >= MIDBLACK) {
            create_drive_direct(-20,-20);
            printf("right is GRAY: %i\n", checkRight);
            create_spin_CCW(SPIN);

        }

        // when left is more than 900 (on white) and right is less than 900 (more on black)
        else if (checkLeft >= MIDBLACK && checkRight <= MIDBLACK) {

            create_drive_direct(-20,-20);
            printf("left is GRAY: %i\n", checkRight);
            create_spin_CW(SPIN);
        }

        else if (checkRight <= MIDBLACK && checkLeft <= MIDBLACK) {
            create_drive_direct(-35 , -35);
            printf("Less than MIDBLACK Right: %i   Left: %i\n", checkRight, checkLeft);

        }

        else if (checkRight >= MIDBLACK && checkLeft >= MIDBLACK) {

            if (checkRight < GRAY && checkLeft < GRAY) {
                printf("Code Finished Right: %i    Left: %i\n", checkRight , checkLeft);
                //needCheck = false;
              //  return;

            }else{
                printf("In the area Right: %i    Left: %i\n", checkRight , checkLeft);
                create_drive_direct(-30,-30);
            }

        }

        else {
            //needCheck = false;
           // return;
            printf("Code Finished Right: %i    Left: %i\n", checkRight , checkLeft);
        }
       // counter++;
       // msleep(10);

    }

}





void backCenterSpot(int RANGE, int SPIN) {

    int checkRight = get_create_rcliff_amt();
    int checkLeft = get_create_lcliff_amt();
    int sumRight = checkRight - checkLeft;
    printf("starting to center\n");
    bool needCheck = true;

    while(checkRight >= GRAY && checkLeft >= GRAY ) {
        checkRight = get_create_rcliff_amt();
        checkLeft = get_create_lcliff_amt();
        create_drive_direct (-50, -50);
        printf("WTF");
    }
    
   // int counter = 0;
   // while(counter<180) {
    
    while(needCheck) {

        checkRight = get_create_rcliff_amt();
        checkLeft = get_create_lcliff_amt();

        if (checkRight >= GRAY && checkLeft >= GRAY ) {
            create_drive_direct (-20, -20);
            //printf("go forward Right: %i     Left: %i\n", checkRight, checkLeft);
        }

        else if (checkRight >= GRAY && checkLeft <= GRAY) {
                   create_drive_direct(-20, -20);
            //printf("right is on white: %i    Left: %i\n", checkRight, checkLeft);
            create_spin_CW(SPIN);
        }

        else if (checkRight <= GRAY && checkLeft >= GRAY) {
            create_drive_direct(20, 20);
            //printf("left is on white: %i   Right: %i\n", checkLeft, checkRight);
            create_spin_CCW(SPIN);
        }

        //this will only happen when both is less than GRAY
        else if (checkLeft <= GRAY && checkRight <= GRAY) {
            //printf("Stop Right: %i    Stop Left:   %i\n", checkLeft , checkRight);

               // int sumRight = checkRight - checkLeft;
                //printf("sumRight Before: %i\n", sumRight);

                //getting the absolute value
                if (sumRight <= 0) {
                    sumRight *= -1;
                    //printf("sumRight Multiplied: %i\n", sumRight);
                }else{
                    //printf("sumRight: %i\n",sumRight );
                }

                if (sumRight < RANGE) {
                    needCheck = false;
                    //printf("100 less 1 Right: %i  Left: %i  sumRight: %i\n", checkRight, checkLeft, sumRight);
                  //  return;
                }else{
                    //printf("Doesn't work\n");
                }

            }

            // when left is less than 900 (on black) and right is more than 900 (more on white)
            else if (checkLeft <= MIDBLACK && checkRight >= MIDBLACK) {
                create_drive_direct(20,20);
                //printf("right is GRAY: %i\n", checkRight);
                create_spin_CW(SPIN);

            }

            // when left is more than 900 (on white) and right is less than 900 (more on black)
            else if (checkLeft >= MIDBLACK && checkRight <= MIDBLACK) {

                create_drive_direct(20,20);
                //printf("left is GRAY: %i\n", checkRight);
                create_spin_CCW(SPIN);
            }

            else if (checkRight <= MIDBLACK && checkLeft <= MIDBLACK) {
                create_drive_direct(35 , 35);
                //printf("Less than MIDBLACK Right: %i   Left: %i\n", checkRight, checkLeft);

            }

            else if (checkRight >= MIDBLACK && checkLeft >= MIDBLACK) {

                if (checkRight < GRAY && checkLeft < GRAY) {
                    //printf("Code Finished Right: %i    Left: %i\n", checkRight , checkLeft);
                    return;

                }else{
                    //printf("In the area Right: %i    Left: %i\n", checkRight , checkLeft);
                    create_drive_direct(30,30);
                }

            }

            else {
                return;
                //printf("Code Finished Right: %i    Left: %i\n", checkRight , checkLeft);
            }
        	//console_clear();
        	//printf("counter: %i\n", counter);
           // msleep(10);
        	//counter++;
            printf("CheckRight: %i  CheckLeft: %i  sumRight: %i\n", checkRight, checkLeft, sumRight);
    }
        
}

void specialTurn(){
    
    int rightSensor = get_create_rcliff_amt();
    int leftSensor = get_create_lcliff_amt();
    
    while( (rightSensor > 2700 && rightSensor < 2800) && (leftSensor> 1100 && leftSensor <1200) ){
        rightSensor = get_create_rcliff_amt();
    	leftSensor = get_create_lcliff_amt();
        create_spin_CCW(20);
    }
    
    create_stop();
}



/*void magicalTurn(double angle, int speed) {
    
    double dRealAngle = angle/0.88235;
    int iRealAngle = (int)dRealAngle;
    printf("iRealAngle: %i\n", iRealAngle);

    if (angle > 0) {
        printf("Turn Right 90\n");
        set_create_normalized_angle(0);
        int currentAngle = get_create_normalized_angle();
        printf("CURRENTANGLE: %i,  iRealAngle: %i\n", currentAngle, iRealAngle);

        while (currentAngle < iRealAngle) {
            printf("HEEELP\n");
            printf("cA %i, -a %i\n", currentAngle, -angle);
            create_spin_CCW(25);
            currentAngle = get_create_normalized_angle();
            printf("%i\n",get_create_normalized_angle());
        }

        create_stop();
    }
    if (angle < 0) {
        printf("Turn left 90\n");
        set_create_normalized_angle(0);
        int currentAngle = get_create_normalized_angle();
          printf("CURRENTANGLE: %i, iRealAngle2: %i\n", currentAngle, iRealAngle);
        //currentAngle = 0;

        while (currentAngle > -iRealAngle) {
            printf("WE'RE ALL GONNA DIE");
            create_spin_CW(25);
            currentAngle = get_create_normalized_angle();
            printf("%i\n",get_create_normalized_angle());

            
        }
        create_stop();
    }

}


*/
