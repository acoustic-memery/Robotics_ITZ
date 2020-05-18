#include "main.h"
#include "compDefaults.h"
/* old mogo lift p
void mobileLift(void*parameter) {
	int error;
	int target = 1100;
	float gain = 1.5;
	if(joystickGetDigital(1, 7, JOY_DOWN)){
		encoderReset(mogoEnc);
	}
	while(joystickGetDigital(1, 7 , JOY_UP)) {
		error = target - abs(encoderGet(mogoEnc));
		error = error * gain;
		if (error > 127){
			error = 127;
		}
		motorSet(9, error);
		delay(10);
	}
}*/

//chainbar control
void chainBack(){
	int error;
	int target = 330;
	float gain = 0.1;
		error = target - analogRead(2);
		error = error * gain;
		if (error > 127){
			error = 127;
		}
		motorSet(5, -error);
		motorSet(8, -error);
}

void chainForeward(){
	int error;
	int target = 625;
	float gain = 0.1;
		error = target - analogRead(2);
		error = error * gain;
		if (error > 127){
			error = 127;
		}
		motorSet(5, -error);
		motorSet(8, -error);
}

void chainLevel(){
	int error;
	int target = 2100;
	float gain = 0.1;
		error = target - analogRead(2);
		error = error * gain;
		if (error > 127){
			error = 127;
		}
		motorSet(5, -error);
		motorSet(8, -error);
}









///////motor presets

void lift (int speed) {
motorSet(3, speed);
motorSet(7, speed);
}

void mobileGoalLift (int speed){
motorSet(9, -speed);
}

void chainBar(int speed) {
	motorSet(5, speed);
	motorSet(8, speed);
}

void claw(int speed) {
	motorSet(4, speed);
}
