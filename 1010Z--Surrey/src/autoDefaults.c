#include "main.h"
#include "autoDefaults.h"


////////motor functions
void motorsForewards(){
motorSet(1, 127);
motorSet(2, 127);
motorSet(6, -127);
motorSet(10, 127);
}

void motorsBack(){
  motorSet(1,-127);
  motorSet(2, -127);
  motorSet(6, 127);
  motorSet(10, -127);
}

void motorsLeft(){
  motorSet(1,-127);
  motorSet(2, -127);
  motorSet(6, -127);
  motorSet(10, 127);
}

void motorsRight(){
  motorSet(1, 127);
  motorSet(2, 127);
  motorSet(6, 127);
  motorSet(10, -127);
}

void motorsStop(){
  motorSet(1, 0);
  motorSet(2, 0);
  motorSet(6, 0);
  motorSet(10, 0);
}

void motorsLiftUp(){
  motorSet(3, 127);
  motorSet(7, 127);
}

void motorsLiftDown(){
  motorSet(3, -127);
  motorSet(7, -127);
}

void motorsLiftStop(){
  motorSet(3, 0);
  motorSet(7, 0);
}

void motorsChainUp(){
motorSet(5, 127);
motorSet(8, 127);
}

void motorsChainDown(){
motorSet(5, -127);
motorSet(8, -127);

}

void motorsChainStop(){
motorSet(5,0);
motorSet(8,0);
}

void motorsClawOpen(){
motorSet(4, -50);
}

void motorsClawClosed(){
motorSet(4, 50);
}

void motorsClawStop(){
motorSet(4,0);
}

void motorsMobileUp(){
motorSet(9, 127);
}

void motorsMobileDown(){
motorSet(9, -127);
}

void motorsMobileStop(){
motorSet(9,0);
}


///////end motor functions


///////// drive PIDS///////// drive PIDS
void go(int way, int distance, int timeOut, int deriv, int gain) {
  encoderReset(driveEncLeft);

  float encTickLastLeft = 0;
  float encTickLastRight = 0; //tick last left and right
  float outputLeft;
  float outputRight; //power to be outputed left and right
  float errLeft;
  float errRight; //target distance - actual distance left and right
  float gainLeft = 1.25;//motor gain for proportional term
  float gainRight = 1.25;
  float propLeft;
  float propRight; //calculated proportional term left and right
  float derivLeft;
  float derivRight; //calculated derivative term left and right
  long startTime = millis();

  while( millis() - startTime < timeOut) { //while less than target distance

    // errLeft = distance - (abs(encoderGet(driveEncLeft)));
     errRight = distance - (abs(encoderGet(driveEncLeft)));
     //calculate error

    // propLeft = errLeft * gainLeft;
     propRight = errRight * gain;
     //calculate proprtional term

  //   derivLeft = (errLeft - encTickLastLeft) * DERIVATIVE;
     derivRight = (errRight - encTickLastRight) * deriv;
     //calculate derivative term

     encTickLastRight = errRight;
  //   encTickLastLeft = errLeft;

  //   outputLeft = propLeft + derivLeft;
     outputLeft = propRight + derivRight;
     //output P + I + D for both sides

if (outputLeft > 127) {
 outputLeft = 127;
}
if (outputLeft < -127) {
 outputLeft = -127;
}






//make output 127 if greater than 127

if(way == 1) {
  motorSet(1, outputLeft);
  motorSet(2, outputLeft);
  motorSet(6, -outputLeft);
  motorSet(10, outputLeft);



}

if(way == 2) {


  motorSet(1, -outputLeft);
  motorSet(2, -outputLeft);
  motorSet(6, outputLeft);
  motorSet(10, -outputLeft);
}


delay(20);


lcdPrint(uart1,1, "val is %d", abs(encoderGet(driveEncLeft)));
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
    if (output < -127) {

      output = -127;
    }



    if (way == 1){ //right

      motorSet(1, output);
      motorSet(2, output);
      motorSet(6, output);
      motorSet(10, -output);
    }
    if (way == 2){ //left

      motorSet(1, -output);
      motorSet(2, -output);
      motorSet(6, -output);
      motorSet(10, output);

    }

    delay(20);


  }




}

///////base encoder and drive functions

void drive (int distance) {
  encoderReset(driveEncLeft);
  while(abs(encoderGet(driveEncLeft)) < distance) {
    encoderGet(driveEncLeft);
    motorsForewards();
    delay(20);
  }
  encoderGet(driveEncLeft);
  if (abs(encoderGet(driveEncLeft)) > distance) {
motorsStop();
    encoderReset(driveEncLeft);
  }
}

void driveBack (int distance) {
  encoderReset(driveEncLeft);
  while(abs(encoderGet(driveEncLeft)) < distance) {
    encoderGet(driveEncLeft);
motorsBack();
    delay(20);
  }
  encoderGet(driveEncLeft);
  if (abs(encoderGet(driveEncLeft)) > distance) {
motorsStop();
    encoderReset(driveEncLeft);
  }

}

void driveRight (int amount) {
  encoderReset(driveEncLeft);
  while(abs(encoderGet(driveEncLeft)) < amount) {
    encoderGet(driveEncLeft);
motorsRight();
    delay(20);
  }
  encoderGet(driveEncLeft);
  if (abs(encoderGet(driveEncLeft)) > amount) {
motorsStop();
    encoderReset(driveEncLeft);
  }
}

void driveLeft (int amount) {
  encoderReset(driveEncLeft);
  while(abs(encoderGet(driveEncLeft)) < amount) {
    encoderGet(driveEncLeft);
motorsLeft();
    delay(20);
  }
  encoderGet(driveEncLeft);
  if (abs(encoderGet(driveEncLeft)) > amount) {
motorsStop();
    encoderReset(driveEncLeft);
  }

}

void liftUp(int distance){

  while(analogRead(4) < distance) {
    analogRead(4);
motorsLiftUp();
    delay(20);
  }
  if (analogRead(4) > distance) {
motorsLiftStop();
  }
}

void liftScore(void*parameter){
  while(analogRead(4) < 950) {
    analogRead(4);
motorsLiftUp();
    delay(20);
  }
  if (analogRead(4) > 950) {
motorsLiftStop();
  }
}

void liftScore2(void*parameter){
  while(analogRead(4) < 1000) {
    analogRead(4);
motorsLiftUp();
    delay(20);
  }
  if (analogRead(4) > 1000) {
motorsLiftStop();
  }
}

void liftScore3(void*parameter){
  while(analogRead(4) < 950) {
    analogRead(4);
motorsLiftUp();
    delay(20);
  }
  if (analogRead(4) > 950) {
motorsLiftStop();
  }
}

void liftDown(void*parameter){
  while(1) {
    analogRead(4);
if(analogRead(4) > 690){
  motorsLiftDown();
}

  if (analogRead(4) < 690) {
motorsLiftStop();
}
delay(20);
}
}



void chainUp(int distance){
  encoderReset(chainEnc);
while (abs(encoderGet(chainEnc)) < distance){
  motorsChainUp();
encoderGet(chainEnc);
  delay(20);
}
if (abs(encoderGet(chainEnc)) >= distance){
  motorsChainStop();
  encoderReset(chainEnc);
}
}

void chainDown(int distance, int timeOut){
  encoderReset(chainEnc);
while (abs(encoderGet(chainEnc)) < distance - 5){
  int error;
	int target = distance;
  long startTime = millis();
	float gain = 0.7;
		error = target - abs(encoderGet(chainEnc));
		error = error * gain;
		if (error > 127){
			error = 127;
		}
    motorSet(5, -error);
    motorSet(8, -error);

    if ((millis() - startTime) > timeOut) {
       break;
      }
}
if (abs(encoderGet(chainEnc)) >= distance-5){
  motorsChainStop();
  encoderReset(chainEnc);
}
}



void clawOpen(int distance, int timeOut ){
  long startTime = millis();
  analogRead(3);
while (analogRead(3) <  distance){
  motorsClawOpen();
  analogRead(3);
  delay(20);
  if ((millis() - startTime) > timeOut) {
     break;
    }
}
if (analogRead(3) >= distance){
motorsClawStop();
}
}

void clawClosed(int distance){
  analogRead(3);
while (analogRead(3) >  distance){
  motorsClawClosed();
  analogRead(3);
  delay(20);
}
if (analogRead(3) <= distance){
motorsClawStop();
}

}
void mobileLiftUp(){
  encoderReset(mogoEnc);
while (abs(encoderGet(mogoEnc)) > 20){
motorsMobileUp();
encoderGet(mogoEnc);

delay(20);
}
if ((abs(encoderGet(mogoEnc))) <= 20){
motorsMobileStop();
}

}

void mobileLiftDown(){
  encoderReset(mogoEnc);
while (abs(encoderGet(mogoEnc)) < 700){
motorsMobileDown();
  encoderGet(mogoEnc);
  delay(20);
}
encoderGet(mogoEnc);
if (abs(encoderGet(mogoEnc)) >  700){
motorsMobileStop();
}
}


///////axis reset program

void resetAxis(float gain, int timeOut) {
  long startTime = millis();
  float gyroTickLast;
  float output;
  float error;

  float proportional;
  float derivative;
lcdClear(uart1);

  while(gyroGet(mainGyro) > 0) {
    lcdPrint(uart1, 2, "val is %d", gyroGet(mainGyro));
    error = abs(gyroGet(mainGyro));

    proportional = error * gain;

    derivative = (error - gyroTickLast) * GYRODERIV;

    gyroTickLast = error;

    output = proportional + derivative;

    if (output > 127) {

      output = 127;
    }
    motorSet(1, -output);
    motorSet(2, output);
    motorSet(6, output);
    motorSet(10, -output);
    if ((millis() - startTime) > timeOut) {
       break;
      }

    delay(20);

}


  while(gyroGet(mainGyro) < 0) {
  lcdPrint(uart1, 2, "val is %d", gyroGet(mainGyro));
  error = abs(gyroGet(mainGyro));

  proportional = error * gain;

  derivative = (error - gyroTickLast) * GYRODERIV;

  gyroTickLast = error;

  output = proportional + derivative;

  if (output > 127) {

    output = 127;
  }
  motorSet(1, output);
  motorSet(2, -output);
  motorSet(6, -output);
  motorSet(10, output);
  if ((millis() - startTime) > timeOut) {
     break;
    }

  delay(20);
}






lcdPrint(uart1, 2, "val is %d", gyroGet(mainGyro));

}



void chainGrabTask(void*parameter){
  while (1){
    int error;
    int target;
    float gain = 0.7;
      error = target - analogRead(2);
      error = error * gain;
      if (error > 127){
        error = 127;
      }
      motorSet(5, -error);
      motorSet(8, -error);

    delay(20);
  }

}

void chainScoreTask(void*parameter){

  while (1){
    int error;
  	int target= 1500;
  	float gain = 0.05;
  		error = target - analogRead(2);
  		error = error * gain;
  		if (error > 127){
  			error = 127;
  		}
      motorSet(5, -error);
      motorSet(8, -error);

    delay(20);
  }

}

void chainBackTask(void*parameter){
  while (1){
    int error;
    int target = 2400;
    float gain = 0.05;
      error = target - analogRead(2);
      error = error * gain;
      if (error > 127){
        error = 127;
      }
      motorSet(5, -error);
      motorSet(8, -error);

    delay(20);
  }


}

void chainResetTask(void*parameter){
  while (1){
    int error;
    int target = 330;
    float gain = 0.05;
      error = target - analogRead(2);
      error = error * gain;
      if (error > 127){
        error = 127;
      }
      motorSet(5, -error);
      motorSet(8, -error);

    delay(20);
  }


}

void liftPidDown(int timeOut, int target, float gain){
  long startTime = millis();
  while((millis() - startTime) > timeOut) {
    int error;
    error =  analogRead(4) - target;
    error = error * gain;
      if (error > 127){
        error = 127;
      }
      motorSet(3, -error);
      motorSet(7, -error);
      delay(20);
}
}

void liftPidUp(int timeOut, int target, float gain){
  long startTime = millis();
  while((millis() - startTime) > timeOut) {
    int error;
    error =  analogRead(4) - target;
    error = error * gain;
      if (error > 127){
        error = 127;
      }

      motorSet(3, -error);
      motorSet(7, -error);
      delay(20);
}
}
