/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"
#include "lcdFunctions.h"
#include "compDefaults.h"


#define DERIV 0.45
/*

 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */
void operatorControl() {

	encoderReset(mogoEnc);
	int X1;
	int Y1;
	int deadZone = 10;
	float output;
  float error;
	float gain = 0.05;
	float setPoint = 1000;

	//taskCreate(driveLcd, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);

  float proportional;
  float derivative;
	int tickLast;


	///////chainbar functions


	while (1) {


		bool chainUp = joystickGetDigital(2, 5, JOY_UP);
		bool chainDown = joystickGetDigital(2, 5, JOY_DOWN);


///////////running tasks

//taskCreate(mobileLift, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);

//////////chainbar control

/*
if (chainUp == 1 && chainDown == 0){
	//taskCreate(chainBack, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
	chainBack();
}

/// if up
else if (chainUp == 0 && chainDown == 1) {
	//taskCreate(chainForeward, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
	chainForeward();
}
////if down

else if (chainUp == 0 && chainDown == 0){
	//taskCreate(chainLevel, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
	chainLevel();
}
else {
	chainBar(0);
}*/

if(joystickGetDigital(2, 5, JOY_UP)){
	chainBar(127);
}
else if(joystickGetDigital(2, 5, JOY_DOWN)){
	chainBar(-127);
}

else if(joystickGetDigital(2, 8, JOY_RIGHT)){
	chainLevel();
}
else if(joystickGetDigital(2, 8, JOY_UP)){
	chainBack();
}
else if (joystickGetDigital(2, 8 , JOY_DOWN)){
	chainForeward();
}
else

 {
	chainBar(0);
}

/*
if (joystickGetDigital(2, 5, JOY_UP)) {
	chainBar(127);
}
else if (joystickGetDigital(2, 5, JOY_DOWN)){
	chainBar(-127);
}
else {
	chainBar(0);
}
*/


///////////////mogo lift
if (joystickGetDigital(1, 6,JOY_UP)){
	mobileGoalLift(127);
}
else if (joystickGetDigital(1, 6, JOY_DOWN)){
	mobileGoalLift(-127);
}
else {
	mobileGoalLift(0);
}


////////////////main lift

if (joystickGetDigital(1, 5 , JOY_UP) == 1){
	lift(127);
setPoint = analogRead(4);

}
else if (joystickGetDigital(1, 5, JOY_DOWN) == 1) {
	lift(-127);
setPoint = analogRead(4);


}/*
else if (joystickGetDigital(1, 5 , JOY_UP) == 0 && joystickGetDigital(1, 5, JOY_DOWN) == 0) {
	error = analogRead(4) - setPoint;
	proportional = error * gain;
	derivative = (error - tickLast) * DERIV;
	tickLast = error;
	output = proportional + derivative;

	lift(-output);

}*/
else {
	lift(0);
}

/////////////////////intake

if (joystickGetDigital(2, 6 , JOY_UP)){
	claw(50);
}
else if (joystickGetDigital(2, 6, JOY_DOWN)) {
claw(-50);
}
else {
claw(-10);
}

printf("val is %d", abs(encoderGet(driveEncLeft)));



/////////////////////drive


		if (abs(joystickGetAnalog(1, 1)) > deadZone) {
			Y1 = joystickGetAnalog(1, 1);
		}
		else {
			Y1 = 0;
		}



		if (abs(joystickGetAnalog(1, 3)) > deadZone) {
			X1 = joystickGetAnalog(1, 3);
		}
		else
		{
			X1 = 0;
		}

		if (Y1 > 90){
			Y1 = 90;
		}
		if (Y1 < -90) {
			Y1 = -90;
		}
		if (X1 > 90) {
			X1 = 90;
		}
		if (X1 < -90) {
			X1 = -90;
		}

		motorSet(1, (X1 + Y1));
		motorSet(2, (X1 + Y1));
		motorSet(6, (-X1 + Y1));
		motorSet(10, (X1 - Y1));



		delay(20);
	}

} // end while (1)
