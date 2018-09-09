#include <Servo.h>

/*
 * time2 is equal to the amount of counter you want 
 * counter is a frikcen counter you start at 0
 * sec is the amount of seconds you want
 */

void latch(int pos) {
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
    printf("claw activated\n");
    int current = get_servo_position(CLAW_SERVO);
    printf("current pos: %i\n", current);
    set_servo_position(CLAW_SERVO, pos);
    printf("not detected");

}
