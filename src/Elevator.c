#include <Elevator.h>

void moveElevatorByTicks(int ticks){
    mrp(LOWER_MOTOR, DEFAULT_ELEVATOR_SPEED, ticks);
    mrp(UPPER_MOTOR, DEFAULT_ELEVATOR_SPEED * MOTOR_CORRECTION_FACTOR, ticks);
    bmd(UPPER_MOTOR);
    bmd(LOWER_MOTOR);
}

void moveElevatorByTicksAndSpeed(int ticks, int speed)
{
    //up is negative
    //down is positve

    mrp(LOWER_MOTOR, speed, ticks);
    mrp(UPPER_MOTOR, speed * MOTOR_CORRECTION_FACTOR, ticks);
    bmd(UPPER_MOTOR);
    bmd(LOWER_MOTOR);
}

void moveElevatorByClicks(int requiredClicks, int speed)
{
 
    bool buttonPressed = false;

    motor(LOWER_MOTOR, speed);
    motor(UPPER_MOTOR, speed * MOTOR_CORRECTION_FACTOR);
    msleep(1000);

    while (requiredClicks > 0)
    {

        if (CLICKER == 0)
            set_servo_position(LATCH_SERVO, LATCH_CLOSE_POSITION);
            buttonPressed = false;
        if (CLICKER == 1 && !buttonPressed)
        {
            set_servo_position(LATCH_SERVO, LATCH_CLOSE_POSITION);
            buttonPressed = true;
            requiredClicks--;
            printf("required Clicks minused\n");
        }
        printf("required clicks: %i\n", requiredClicks);
    }

    ao();
    printf("we should have stopped by now\n");

}

void moveElevatorByTime(int sec, int speed){
    motor(LOWER_MOTOR, speed);
    motor(UPPER_MOTOR, speed * MOTOR_CORRECTION_FACTOR);
    msleep(sec);
    ao();
}