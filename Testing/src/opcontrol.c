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
void lift(int power) {
	motorSet(8, power);
	motorSet(7, power);
	motorSet(3, power);
}

void mobileLift(int power) {
	motorSet(4, power);

}

void mobileLiftP(void*parameter) {
	int error;
	int target = 1;
	float gain = 1.5;

	while(joystickGetDigital(1, 8 , JOY_UP)) {
		error = analogRead(1) - target;
		error = error * gain;

		if (error > 127){
			error = 127;
		}

		//motorSet(4, error);

		delay(20);


	}


}


void operatorControl() {
	int X1;
	int Y1;
	int deadZone = 10;

lcdClear(uart1);

	while (1) {
		taskCreate(mobileLiftP, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
lcdPrint(uart1, 1, "val is %d", analogRead(1));

		if (abs(joystickGetAnalog(1, 3)) > deadZone) {
			Y1 = joystickGetAnalog(1, 3);
		}
		else {
			Y1 = 0;
		}

		if (abs(joystickGetAnalog(1, 1)) > deadZone) {
			X1 = joystickGetAnalog(1, 1);
		}
		else
		{
			X1 = 0;
		}
motorSet(1, (X1 + Y1));
motorSet(2,(-X1+ Y1));
motorSet(5, (X1 + -Y1));
motorSet(6, (-X1 + -Y1));
motorSet(9, (X1 + Y1));
motorSet(10, (-X1 + Y1));

if (joystickGetDigital(1, 5, JOY_UP)){
	lift(127);
}
else if (joystickGetDigital(1, 5, JOY_DOWN)) {
	lift(-90);
}
else{
	lift(0);
}



if (joystickGetDigital(1, 6, JOY_UP)){
	mobileLift(127);
}
else if (joystickGetDigital(1, 6, JOY_DOWN)) {
	mobileLift(-127);
}
else{
	mobileLift(0);
}





		delay(20);
	}
}
