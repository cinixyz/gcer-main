#include <Misc.h>

void playDespacito(){
    system("aplay /home/root/Documents/despacito.wav");
}


void waitForSome(double sec)
{
    ao();
    create_stop();
    double mili = sec*1000;
    msleep(mili);

}

int inCmConv(double inches)
{
    return (inches * 2.54) + 1;
}

int getBatteryCapacity()
{
    int batteryCharge = get_create_battery_charge();
    int batteryCapacity = get_create_battery_capacity();
    double dBatteryPercentage = ((double)(batteryCharge)/batteryCapacity)*100;
    int iBatteryPercentage = (int)dBatteryPercentage;
    printf("%d battery charge\n", batteryCharge);
    return iBatteryPercentage;


}
