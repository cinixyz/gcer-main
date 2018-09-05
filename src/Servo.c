#include <Servo.h>

/*
// time2 is equal to the amount of counter you want 
//counter is a frikcen counter you start at 0
// sec is the amount of seconds you want
int sec = 

time2 = sec*30;
void timer(counter <= time2) { 
    time



*/


void latch(int pos) {

    ///enable_servos();
    switch(pos){
        case CLOSE_LATCH:
            set_servo_position(LATCH_SERVO, LATCH_CLOSE_POSITION);
            break;
        case OPEN_LATCH:
            set_servo_position(LATCH_SERVO, LATCH_OPEN_POSITION);
            break;
        default:
            printf("invalid position input");
    }
}

void claw(int pos) {

    //int latchPosition = get_servo_position(LATCH_SERVO);
    
    
    //removed because of potential problems
    //enable_servos();
    /*msleep(500);
    if (latchPosition  != LATCH_CLOSE_POSITION){
        set_servo_position(LATCH_SERVO, LATCH_CLOSE_POSITION);
    }*/
    
    printf("claw activated\n");
    int current = get_servo_position(CLAW_SERVO);
    printf("current pos: %i\n", current);
    /*if (pos >= current) {
        while (current < pos) {
            printf("%i\n", current);
            set_servo_position(CLAW_SERVO, current);
            current+=25;
            msleep(20);
        }
    }
    else if (pos <= current) {
        while (current > pos) {
            printf("%i\n", current);
            set_servo_position(CLAW_SERVO, current);
            current-=25;
            msleep(20);
        }
    }*/
    set_servo_position(CLAW_SERVO, pos);
    //disable_servos();
    printf("not detected");

}
