#include <LineFollowing.h>

/*
 * Gray L: 2750
 * Gray R: 2760
 */
double rightTarget = 2890;
double leftTarget = 2950;

double outMin,outMax;

void getSensorVal() {
    while (1) {
        msleep(200);
        console_clear();
        int lfront = get_create_lfcliff_amt();
        int rfront = get_create_rfcliff_amt();
        printf("Left : %d\n", lfront);
        printf("Right: %d\n", rfront);
    }
}
void SetOutputLimits(double Min, double Max) {
    if (Min > Max) return;
    outMin = Min;
    outMax = Max;
}

void pi_LineFollow(int inputDistance_cm, int speed, int delay) {

    set_create_distance(0);

    double dinputDistance_mm = inputDistance_cm * 9.875; // Less than actual conversion
    double currentDistance_mm = get_create_distance(); // Not updating distance

    double lastRightError = 0;
    double lastLeftError = 0;

    double rightIntegral = 0;
    double leftIntegral = 0;

    double dspeed = (double)speed;

    SetOutputLimits(dspeed-70,dspeed+70);

    while (currentDistance_mm < dinputDistance_mm){
        int lfront = get_create_lfcliff_amt();
        int rfront = get_create_rfcliff_amt();

        double dlfront = (double)lfront;
        double drfront = (double)rfront;


        double rightError = rightTarget - rfront;
        double leftError = leftTarget - lfront;
        double rightProportional = right_P * rightError;
        double leftProportional = left_P * leftError;
        double rightIntegral = (rightIntegral + rightProportional) * right_I;
        double leftIntegral = (leftIntegral + leftProportional) * left_I;

        //Reset Windup - Limits for individual components
        if (rightIntegral > outMax) rightIntegral = outMax;
        else if(rightIntegral < outMin) rightIntegral = outMin;
        /*
        if (leftIntegral > outMax) leftIntegral = outMax;
        else if(leftIntegral < outMin) leftIntegral = outMin;

        if (rightProportional > outMax) rightProportional = outMax; WTFFFFFFFFFFFFFFFFF
        else if(rightProportional < outMin) rightProportional = outMin;
        if (leftProportional > outMax) leftProportional = outMax;
        else if(leftProportional < outMin) leftProportional = outMin;
        */
        //Calculation turning speed

        double pdRight = dspeed + (rightProportional + rightIntegral);//+ rightDifferential); //+ rightIntegral);
        double pdLeft =  dspeed + (leftProportional + leftIntegral);//+ leftDifferential); //+ leftIntegral);

        //Reset Windup - Limits for turning speed
        /*
        if (pdRight > outMax) pdRight = outMax;
        else if(pdRight < outMin) pdRight = outMin;
        if (pdLeft > outMax) pdLeft = outMax;
        else if(pdLeft < outMin) pdLeft = outMin;
        */
        lastRightError = rightError;
        lastLeftError = leftError;

        int ipowerUp = (int) pdRight;
        int ipowerDown = (int) pdLeft;


        //printf("Right-Proportional: %f Left-Proportional: %f\n\n", rightProportional, leftProportional);
        printf("---------------------------------------\n");
        printf("Right-Sensor: %f Left-Sensor: %f\n", dlfront, drfront);
        //printf("rightError: %.2f  leftError: %.2f\n", rightError, leftError);
        printf("turnRight: %.2f turnLeft: %.2f\n",pdRight, pdLeft);
        //printf("lfront: %.2f rfront: %.2f  turnRight: %i  turnLeft: %i\n", dlfront, drfront, turnRight,turnLeft);

        create_drive_direct(ipowerUp, ipowerDown);

        currentDistance_mm = get_create_distance();

        msleep(delay);
    }
}
