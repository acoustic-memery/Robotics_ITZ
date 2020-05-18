#include "main.h"
#include "autoFunctions.h"

#define DERIVATIVE 5
#define GYRODERIV 4
///////////////////motor functions//////////////////

void motorsForeward(int speed) {
  motorSet(1, speed);
  motorSet(2, speed);
  motorSet(5, speed);
  motorSet(6, -speed);
  motorSet(9, -speed);
  motorSet(10, -speed);
}

void motorsBackward(int speed) {
  motorSet(1, -speed);
  motorSet(2, -speed);
  motorSet(5, -speed);
  motorSet(6, speed);
  motorSet(9, speed);
  motorSet(10, speed);
}

void motorsStop(){
  motorSet(1,  0);
  motorSet(2,  0);
  motorSet(5,  0);
  motorSet(6,  0);
  motorSet(9,  0);
  motorSet(10, 0);
}

void motorsRight(int speed){
  motorSet(1, speed); //l
  motorSet(2, speed); //l
  motorSet(5, -speed);//r
  motorSet(6, speed);//-r
  motorSet(9, -speed); //-l
  motorSet(10, speed);//-r
}

void motorsLeft(int speed){
  motorSet(1, -speed); //l
  motorSet(2, -speed); //l
  motorSet(5, speed);//r
  motorSet(6, -speed);//-r
  motorSet(9, speed); //-l
  motorSet(10, -speed);//-r
}


void mogoUp(int speed){
  motorSet(3, -127);

  motorSet(4, 127);
  motorSet(8, 127);
}


void mogoDown(int speed){
  motorSet(3, 127);

  motorSet(4, -127);
  motorSet(8, -127);
}

void mogoStop(){
  motorSet(3, 0);
  motorSet(4, 0);
  motorSet(7, 0);
  motorSet(8, 0);
}




void mobileLift(void*parameter) {
	int error;
	int target = 3300;
	float gain = 0.5;


	while(1) {
		error = analogRead(2)- target;
		error = error * gain;

		if (error > 127){
			error = 127;
		}

    motorSet(3, -error);

    motorSet(4, error);
    motorSet(8, error);

		delay(10);
	}

}

void mogoLift1(void*parameter) {
	int error;
	int target = 3150;
	float gain = 0.5;


	while(joystickGetDigital(1, 5, JOY_UP)) {
		error = analogRead(2)- target;
		error = error * gain;

		if (error > 127){
			error = 127;
		}

    motorSet(3, -error);

    motorSet(4, error);
    motorSet(8, error);

		delay(10);
	}

}


void mobileLift2(void*parameter) {
	int error;
	int target = 3000;
	float gain = 0.5;


	while(1) {
		error = analogRead(2)- target;
		error = error * gain;

		if (error > 127){
			error = 127;
		}

    motorSet(3, -error);

    motorSet(4, error);
    motorSet(8, error);

		delay(10);
	}

}



////////////PIDs///////////////



///////// drive PIDS
void go(int way, int distance, int timeOut, float deriv, float gain) {
  encoderReset(driveEncLeft);
  encoderReset(driveEncRight);
  float encTickLastLeft = 0;
  float encTickLastRight = 0; //tick last left and right
  float outputLeft;
  float outputRight; //power to be outputed left and right
  float errLeft;
  float errRight; //target distance - actual distance left and right

  float propLeft;
  float propRight; //calculated proportional term left and right
  float derivLeft;
  float derivRight; //calculated derivative term left and right
  long startTime = millis();
  float sumErrorL;
  float sumErrorR;


  float integ = 0;


  float integralL;
  float integralR;
  while( millis() - startTime < timeOut) { //while less than target distance

     errLeft = distance - (abs(encoderGet(driveEncLeft)));
     errRight = distance - (abs(encoderGet(driveEncRight)));
     //calculate error



     propLeft = errLeft * gain;
     propRight = errRight * gain;
     //calculate proprtional term

     derivLeft = (errLeft - encTickLastLeft) * deriv;
     derivRight = (errRight - encTickLastRight) * deriv;
     //calculate derivative term

     encTickLastRight = errRight;
     encTickLastLeft = errLeft;



     //outputLeft = propLeft + derivLeft;
     outputRight = propRight+ derivRight;
     //output P + I + D for both sides


if (outputRight > 127) {
 outputRight = -127;
}

if (outputRight < -127) {
 outputRight = -127;
}

//make output 127 if greater than 127

if(way == 1) {

  motorSet(1, outputRight);
  motorSet(2, outputRight);
  motorSet(5, outputRight);
  motorSet(6, -outputRight);
  motorSet(9, -outputRight);
  motorSet(10, -outputRight);



}

if(way == 2) {


motorSet(1, -outputRight);
motorSet(2, -outputRight);
motorSet(5, -outputRight);
motorSet(6, outputRight);
motorSet(9, outputRight);
motorSet(10, outputRight);

}


delay(20);

  }



}

void turnGo(int distance, int way, float gain, float kd, int timeOut) {
  gyroReset(mainGyro);
  long startTime = millis();
  float gyroTickLast;
  float output;
  float error;

  float proportional;
  float derivative;
lcdClear(uart1);
  while((millis() - startTime) < timeOut) {
    lcdPrint(uart1, 2, "val is %d", gyroGet(mainGyro));
    error = distance - abs(gyroGet(mainGyro));

    proportional = error * gain;

    derivative = (error - gyroTickLast) * kd;

    gyroTickLast = error;

    output = proportional + derivative;

    if (output > 127) {

      output = 127;
    }


    if (way == 1){ //right

      motorSet(1, output); //l
      motorSet(2, output); //l
      motorSet(5, -output);//r
      motorSet(6, output);//-r
      motorSet(9, output); //-l
      motorSet(10, -output);//-r
    }
    if (way == 2){ //left

      motorSet(1, -output); //l
      motorSet(2, -output); //l
      motorSet(5, output);//r
      motorSet(6, -output);//-r
      motorSet(9, -output); //-l
      motorSet(10, output);//-r

    }

    delay(20);


  }




}


/////////////////intake functions

void autoDrop(void*parameter){
  int potTarget = 1700;

  while(1){
    if (analogRead(2) > potTarget){
      digitalWrite(2, HIGH);
    }
    if (analogRead(2) < potTarget){
      digitalWrite(2, LOW);
    }
    delay(20);
  }

}

////////////////thread for controlling pneumatic intake

void intakeUp(int amount, int hDistance){

  int error;
  float gain = 1;

  while (abs(encoderGet(driveEncRight)) < hDistance ) {

    if (analogRead(2) > amount){
      error = analogRead(2) - amount;
      error = error * gain;

      if (error > 90){
        error = 90;
      }


      mogoUp(error);
}
else if (analogRead(2) < amount){
  mogoStop();
}
      delay(10);

  }

}

void intakeTurn(int amount, int hDistance){

  int error;
  float gain = 1;

  while (abs(gyroGet(mainGyro)) < hDistance ) {

    if (analogRead(2) > amount){
      error = analogRead(2) - amount;
      error = error * gain;

      if (error > 90){
        error = 90;
      }


      mogoUp(error);
}
else if (analogRead(2) < amount){
  mogoStop();
}
      delay(10);

  }

}

void intakeDelay(int amount){
  while(abs(encoderGet(driveEncRight)) < amount){

    delay(20);
  }
}

void intakeDelayTurn(int amount) {
  while(abs(gyroGet(mainGyro)) < amount){
    delay(20);
  }
}

void intakeReset(){
  int target = 4060;

  while(analogRead(2) < target){
    mogoDown(127);
    delay(20);
  }
  if(analogRead(2) >= target) {
    mogoStop();
  }
}


/*
Note

The main running auto thread is used to control the drive and drive related functions

The second thread is used to control the pnuematics

The third thread is used to control the mogo lifter
*/
