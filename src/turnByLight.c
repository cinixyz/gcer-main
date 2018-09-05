#include <turnByLight.h>

void ciniTurn(int angle, int speed) {
    if (angle > 0) {
        int wait = 0;
        printf("Moving %d clockwise.\n", angle);
        wait = (int)(angle * G_DEGREESTOMILISECFACTOR);
        create_spin_CW(speed);
        msleep(wait);
        create_stop();
        printf("Moved %d clockwise.\n", angle);
    }
    if (angle < 0) {
        int wait = 0;
        printf("Moving %d counterclockwise.\n", angle);
        wait = (int)(-angle * G_DEGREESTOMILISECFACTOR);
        printf("%d", wait);
        create_spin_CCW(speed); // moving counterclockwise since angle is in negatives
        msleep(wait);
        create_stop();
        printf("Moved %d counterclockwise.\n", angle);
    }

}

void turnLeftByAngle(int angle, int speed)
{
    double ratio = 90.0/102.0;
    double realAngle = ((double)angle/ratio) + 0.5; 
    int iRealAngle = (int)realAngle;
    printf("ratio: %lf , realAngle = %lf  , iLeftRealAngle = %i", ratio, realAngle, iRealAngle);

    set_create_normalized_angle(0);
    int currentAngle = get_create_normalized_angle();
    while (currentAngle <= iRealAngle) {
        create_spin_CCW(speed);
        currentAngle = get_create_normalized_angle();
        printf("%i\n",get_create_normalized_angle());
    }

    create_stop();
}
 
void turnRightByAngle(int angle, int speed)
{
    double ratio = 90.0/102.0;
    double realAngle = ((double)angle/ratio) + 0.5; 
    int iRealAngle = (int)realAngle;
    printf("ratio: %lf , realAngle = %lf  , iRightRealAngle = %i", ratio, realAngle, iRealAngle);
    
    set_create_normalized_angle(0);
    int currentAngle = get_create_normalized_angle();
    while (currentAngle > -iRealAngle) {
        create_spin_CW(speed);
        currentAngle = get_create_normalized_angle();
        printf("%i\n",get_create_normalized_angle());
    }

    create_stop();
}

 
    

