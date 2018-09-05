#include <HardwareTest.h>

void hardwareTestActivate() {

    bool servos_enabled = false;
	int currentClawPosition = get_servo_position(CLAW_SERVO);
	int currentLatchPosition = get_servo_position(LATCH_SERVO);
  
    int lowerMotorPos = gmpc(LOWER_MOTOR);
	int lastMotorPos = gmpc(LOWER_MOTOR);
	int ticksTravelled = lowerMotorPos - lastMotorPos;
	int elevatorSpeed = 75;
    bool elevatorActivated = false;
    
	bool needCheck = true;

	while (needCheck) {

        //updating data
		lowerMotorPos = gmpc(LOWER_MOTOR);
        ticksTravelled = lowerMotorPos - lastMotorPos;
        currentClawPosition = get_servo_position(CLAW_SERVO);
        currentLatchPosition = get_servo_position(LATCH_SERVO);
        
        //displaying data
        console_clear();
        
        printf("Claw Positon: %i\n", currentClawPosition);
        printf("Latch Positon: %i\n\n", currentLatchPosition);
        
        printf("ELEVATOR:\n\t");
        printf("Last LMotorPos: %i\n\t", lastMotorPos);
        printf("LMotorPos: %i\n\t", lowerMotorPos);
        printf("Ticks Travelled: %i\n\t", ticksTravelled);
        printf("ElevatorSpeed: %i\n\t", elevatorSpeed);
        printf("Clicker Pressed: ");
        
		//elevator states
        if (CLICKER == 1) printf("TRUE\n\n");
        else if (CLICKER != 1) printf("FALSE\n\n");
        
        /* not yet implemented --- needs to add state check feature
		if (INCREASE_ELEVATOR_SPEED){
    		elevatorSpeed-=ELEVATOR_SPEED_INCREMENT;
        	msleep(500);
		}
      
		else if (REDUCE_ELEVATOR_SPEED){
        	elevatorSpeed-=ELEVATOR_SPEED_INCREMENT;
        	msleep(500);
		}*/

		if (GO_UP) {
            if (!elevatorActivated) lastMotorPos = gmpc(LOWER_MOTOR);
			elevatorActivated = true;
			motor(UPPER_MOTOR, -elevatorSpeed * MOTOR_CORRECTION_FACTOR);
			motor(LOWER_MOTOR, -elevatorSpeed);
            set_servo_position(LATCH_SERVO, LATCH_OPEN_POSITION);
		}

		else if (GO_DOWN) {
            if (!elevatorActivated) lastMotorPos = gmpc(LOWER_MOTOR);
      		elevatorActivated = true;
			motor(UPPER_MOTOR, elevatorSpeed * MOTOR_CORRECTION_FACTOR);
			motor(LOWER_MOTOR, elevatorSpeed);
            set_servo_position(LATCH_SERVO, LATCH_OPEN_POSITION);
		}

		//claw states
		else if (TEST_CLOSE_CLAW) {
			if (!servos_enabled) {
				servos_enabled = true;
				enable_servos();
			}
			currentClawPosition += 20;
			if (currentClawPosition >= CLAW_CLOSE_POSITION) {
        		currentClawPosition = CLAW_CLOSE_POSITION;
			}
			set_servo_position(CLAW_SERVO, currentClawPosition);
			msleep(20);
		}

		else if (TEST_OPEN_CLAW) {
			if (!servos_enabled) {
				servos_enabled = true;
				enable_servos();
			}
			currentClawPosition -= 30;
			if (currentClawPosition <= CLAW_OPEN_POSITION) {
				currentClawPosition = CLAW_OPEN_POSITION;
			}
			set_servo_position(CLAW_SERVO, currentClawPosition);
			msleep(20);
		} 
         
		//latch states
		else if (TEST_CLOSE_LATCH) {
			if (!servos_enabled) {
				servos_enabled = true;
				enable_servos();
			}
			currentLatchPosition -= 30;
			if (currentLatchPosition <= LATCH_CLOSE_POSITION) {
				currentLatchPosition = LATCH_CLOSE_POSITION;
			}
			set_servo_position(LATCH_SERVO, currentLatchPosition);
			msleep(40);
		} 
        
		else if (TEST_OPEN_LATCH) {
			if (!servos_enabled) {
        		servos_enabled = true;
        		enable_servos();
			}
			currentLatchPosition += 30;
			if (currentLatchPosition >= LATCH_OPEN_POSITION) {
        		currentLatchPosition = LATCH_OPEN_POSITION;
			}
			set_servo_position(LATCH_SERVO, currentLatchPosition);
			msleep(40);
		}

		else if (servos_enabled) {
        	servos_enabled = false;
        	disable_servos();
		}
        
        else if (elevatorActivated){
      		elevatorActivated = false;
        	ao();
		}
             
		else if(END_HARDWARE_TEST){
			needCheck = false;
			printf("WOWZERS");
        }

	}
    
  disable_servos();

}
