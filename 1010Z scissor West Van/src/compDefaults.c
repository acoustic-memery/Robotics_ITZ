#include "main.h"
#include "compDefaults.h"

void mobileLift(void*parameter) {
	int error;
	int target = 1100;
	float gain = 1.5;


	while(joystickGetDigital(1, 7 , JOY_UP)) {
		error = target - analogRead(3);
		error = error * gain;

		if (error > 127){
			error = 127;
		}

		motorSet(9, error);

		delay(10);
	}

}

void chainBack(void*parameter){
	if(joystickGetDigital(2, 8, JOY_UP)){
		analogRead(2);
		if(analogRead(2) > 9) {
			motorSet(5, 127);
			analogRead(2);
		}
		if(analogRead(2) <= 9){
			motorSet(5,0);
		}
	}

}










void lift (int speed) {
motorSet(3, speed);
motorSet(8, -speed);
motorSet(7, -speed);
}

void mobileGoalLift (int speed){
motorSet(9, -speed);
}

void chainBar(int speed) {
	motorSet(5, speed);
}

void claw(int speed) {
	motorSet(4, speed);
}




void autoStack(void*parameter) {

	int cone[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
	//int stackSize = 3;
	int chainState = 0;
	int coneOffset = 15;
	int error;
	int chainTarget = 145;
	float gain = 2.0;
	int coneState = 0;



	while(joystickGetDigital(2, 8, JOY_RIGHT)){

	//	if (coneState == 0){
			error = chainTarget - analogRead(2);
			error = error * gain;
			if(error > 127){
				error = 127;
			}
			chainBar(-error);
			delay(20);
		}

			/*if(analogRead(2) >= (chainTarget +- 10)){
				if(abs(encoderGet(liftEnc)) <= 3){
					coneState = 1;
			}
			}
		}
if (coneState == 1){
		if(analogRead(2) >= (chainTarget +- 10)){
			claw(40);
		}
		encoderReset(liftEnc);
		if(encoderGet(liftEnc) >= cone[stackSize]*coneOffset){
			encoderGet(liftEnc);
			chainBar(127);
		}
		if (analogRead(2) <= 120){
			chainBar(0);
			claw(-127);
			delay(1000);
			coneState = 0;
			stackSize++;

		}
}
}
	int stackState = 0;
	//0 for not positioned, 1 for grabbing and stacking cone, 2 for reversing chain bar
	int coneState = 0; //0 for not grabbed, 1 for grabbed
	int coneDifference = 50;
	int fullRotation = 270;
	int grabHeight = 0;
	int clawTarget = 3000;
	int clawTargetOpen = 1000;
	int liftState = 0;






	int stackDifference;
	int liftHeight;

while (joystickGetDigital(1, 8, JOY_RIGHT)){

	while (stackState == 0) { //raise lift to default position (only happens once)
		encoderReset(liftEnc);
		encoderGet(liftEnc);

		if (abs(encoderGet(liftEnc)) <= grabHeight){
			encoderGet(liftEnc);
			lift(127);
		}
		encoderGet(liftEnc);
		if (abs(encoderGet(liftEnc)) >= grabHeight) {
			lift(0);
			encoderReset(liftEnc);
			stackState = 1;

		}
	delay(20);}

		while (stackState == 1) {
			stackDifference = cone[stackSize] * coneDifference;
			 liftHeight = grabHeight - stackDifference;
			if (coneState == 0) { //close claw around cone
				analogRead(1);
				if (analogRead(1) < clawTarget) {
					claw(127);
					analogRead(1);
				}
			 if (analogRead(1) >= clawTarget) {
					claw(0);
					coneState = 1;
				}
			else if (coneState == 1) { //lift to correct height
					 if (abs(encoderGet(liftEnc)) < liftHeight) {
						 lift(127);
						 encoderGet(liftEnc);
					 }
					 if (abs(encoderGet(liftEnc)) > liftHeight) {
						 lift(-127);
						 encoderGet(liftEnc);
					 }
					 if (abs(encoderGet(liftEnc)) == liftHeight+-10) {
						 lift(0);
						 encoderReset(liftEnc);
						 coneState = 2;
					 }
				}
				else if (coneState == 2) { // chain back
					if(abs(encoderGet(chainEnc)) < fullRotation) {
						encoderGet(chainEnc);
						chainBar(127);
					}
					if(abs(encoderGet(chainEnc)) >= fullRotation) {
						encoderGet(chainEnc);
						chainBar(0);
						coneState = 3;
					}
				else if (coneState == 3) { // cone release
						analogRead(1);
						if (analogRead(1) < clawTargetOpen) {
							claw(127);
							analogRead(1);
						}
					 if (analogRead(1) >= clawTargetOpen) {
							claw(0);
							stackState = 2;
							coneState = 0;
						}

				}

				}

			}
		delay(20);}

		while(stackState == 2) {
			stackDifference = cone[stackSize] * coneDifference;
			 liftHeight = grabHeight - stackDifference;
if (liftState == 0) {

			 if (abs(encoderGet(liftEnc)) > liftHeight) {
				 lift(127);
				 encoderGet(liftEnc);
			 }
			 if (abs(encoderGet(liftEnc)) < liftHeight) {
				 lift(-127);
				 encoderGet(liftEnc);
			 }
			else if (abs(encoderGet(liftEnc)) == liftHeight+-10) {
				 lift(0);
				 encoderReset(liftEnc);
				 liftState = 1;

			 }
		 }

		 if (liftState == 1) {
			 if(abs(encoderGet(chainEnc)) < fullRotation) {
				 encoderGet(chainEnc);
				 chainBar(127);
			 }
			 if(abs(encoderGet(chainEnc)) >= fullRotation) {
				 encoderGet(chainEnc);
				 chainBar(0);
				 liftState = 0;
				 stackState = 1;
				 stackSize++;


				 }
			 }


		delay(20);}
*/



	}
void compStack(void*parameter) {
	int cone[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
	int differance = 20;

	if(joystickGetDigital(1, 7, JOY_DOWN)){
		while (analogRead(2) < 130){
			chainBar(-127);
			delay(20);
		}
		if (analogRead(2) >= 130) {
			chainBar(7);
		}
	while (encoderGet(liftEnc) > 2){
		lift(-127);
		delay(20);
	}
	if (encoderGet(liftEnc) <= 2) {
		lift(0);
	}

	while (analogRead(2) < 198){
		chainBar(-127);
		delay(20);
	}
	if (analogRead(2) >= 198) {
		chainBar(0);
	}

	if (analogRead(1) < 1450) {
		claw(-127);

	}
	while (encoderGet(liftEnc) < cone[stackSize]*differance){
		lift(127);
		delay(20);
	}
	if (encoderGet(liftEnc) >= cone[stackSize]*differance){
		lift(0);
	}
	while (analogRead(2) > 120){
		chainBar(-127);
		delay(20);
	}
	if (analogRead(2) <= 120) {
		chainBar(0);
	}
	while (analogRead(1) >= 1000) {
		claw(-127);
		delay(20);
	}
	if (analogRead(1) <= 1000) {
		claw(0);
		stackSize++;
	}






}
if (joystickGetDigital(2, 7, JOY_RIGHT)){
	stackSize = 0;
}
}
