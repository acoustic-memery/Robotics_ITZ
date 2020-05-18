#include "main.h"
#include "autoDefaults.h"


////////motor functions
void motorsForewards(){
motorSet(1,127);
motorSet(2, 127);
motorSet(6, -127);
motorSet(10, -127);
}

void motorsBack(){
  motorSet(1,-127);
  motorSet(2, -127);
  motorSet(6, 127);
  motorSet(10, 127);
}

void motorsLeft(){
  motorSet(1,-127);
  motorSet(2, -127);
  motorSet(6, -127);
  motorSet(10, -127);
}

void motorsRight(){
  motorSet(1,127);
  motorSet(2, 127);
  motorSet(6, 127);
  motorSet(10, 127);
}

void motorsStop(){
  motorSet(1, 0);
  motorSet(2, 0);
  motorSet(6, 0);
  motorSet(10, 0);
}

void motorsLiftUp(){
  motorSet(3, -127);
  motorSet(8, -127);
  motorSet(7, 127);
}

void motorsLiftDown(){
  motorSet(3, 127);
  motorSet(8, 127);
  motorSet(7, -127);
}

void motorsLiftStop(){
  motorSet(3, 0);
  motorSet(8, 0);
  motorSet(7, 0);
}

void motorsChainUp(){
motorSet(5, 127);
}

void motorsChainDown(){
motorSet(5, -127);
}

void motorsChainStop(){
motorSet(5,0);
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
motorSet(9, -127);
}

void motorsMobileDown(){
motorSet(9, 127);
}

void motorsMobileStop(){
motorSet(9,0);
}


///////end motor functions



void go(int way, int distance, int timeOut) {
  encoderReset(driveEncLeft);
  encoderReset(driveEncRight);

  float encTickLastLeft;
  float encTickLastRight; //tick last left and right


  float outputLeft;
  float outputRight; //power to be outputed left and right

  float errLeft;
  float errRight; //target distance - actual distance left and right

//  float errTotalRight;
//  float errTotalLeft; //total accumulated error left and right

//  int errAccuLeft = 50;
//  int errAccuRight = 50; //total accumulated error left and right if less than integral cap

  float gain = 1.25;//motor gain for proportional term


//  float integCap = 100/INTEGRAL; //integral cap

  float propLeft;
  float propRight; //calculated proportional term left and right
  float integLeft;
  float integRight; //calculated integral term left and right
  float derivLeft;
  float derivRight; //calculated derivative term left and right
  long startTime = millis();




  while(((abs(encoderGet(driveEncLeft)))) < distance) { //while less than target distance



     errLeft = distance - (abs(encoderGet(driveEncLeft)));
     errRight = distance - (abs(encoderGet(driveEncRight)));
//calculate error

    /* if(errRight < errAccuRight) {errTotalRight += errRight;}
     else {errTotalRight = 0;}

     if(errLeft < errAccuLeft) {
       errTotalLeft += errLeft;}
     else {errTotalLeft = 0;} //makes integral term 0 if error is less than 50 (this has not been properly tuned)

     if(errTotalLeft > integCap) {
       errTotalLeft = 50/INTEGRAL;
     }

     if(errTotalRight > integCap) {
       errTotalRight = 50/INTEGRAL; //if integral term is greater than 50 (after previous calculation) integral term is incorperated
     }*/

//the above part of the function is only for managing when the integral is enganged

     propLeft = errLeft * gain;
     propRight = errRight * gain; //calculate proprtional term

  //   integLeft = errTotalLeft * INTEGRAL;
    // integRight = errTotalRight * INTEGRAL; //calculate integral term

     derivLeft = (errLeft - encTickLastLeft) * DERIVATIVE;
     derivRight = (errRight - encTickLastRight) * DERIVATIVE;
//calculate derivative term

encTickLastRight = errRight;
encTickLastLeft = errLeft; //calculate enctick last

outputLeft = propLeft + integLeft + derivLeft;
//outputRight = propRight + integRight + derivRight; //output P + I + D for both sides

if (outputLeft > 127) {
 outputLeft = 127;
}

if (outputLeft < 1){
  outputLeft = 0;
}
/*
if (outputRight > 127) {
 outputRight = 127;
}
*/
//make output 127 if greater than 127

if(way == 1) {
  if (abs(encoderGet(driveEncLeft)) < (distance*0.1)){
    outputLeft = 40;
  }

motorSet(1, outputLeft);
motorSet(2, outputLeft);
motorSet(6, -outputLeft);
motorSet(10, -outputLeft);


}

if(way == 2) {
//if backwards
if (abs(encoderGet(driveEncLeft)) < (distance*0.1)){
  outputLeft = 40;
}
motorSet(1, -outputLeft);
motorSet(2, -outputLeft);
motorSet(6, outputLeft);
motorSet(10, outputLeft);


}

if ((millis() - startTime) > timeOut) {
   break;
  }
delay(20);

  }



}

void turnGo(int distance, int way, float gain, int timeOut) {
  gyroReset(mainGyro);
  long startTime = millis();
  float gyroTickLast;
  float output;
  float error;

  float proportional;
  float derivative;
lcdClear(uart1);
  while(abs(gyroGet(mainGyro)) < distance) {
    lcdPrint(uart1, 2, "val is %d", gyroGet(mainGyro));
    error = distance - abs(gyroGet(mainGyro));

    proportional = error * gain;

    derivative = (error - gyroTickLast) * GYRODERIV;

    gyroTickLast = error;

    output = proportional + derivative;

    if (output > 127) {

      output = 127;
    }


    if (way == 1){
      if(abs(gyroGet(mainGyro)) >= distance*0.1){
        output = 40;
      }
      motorSet(1, output);
      motorSet(2, output);
      motorSet(6, output);
      motorSet(10, output);
    }
    if (way == 2){
      if(abs(gyroGet(mainGyro)) >= distance*0.1){
        output = 40;
      }
      motorSet(1, -output);
      motorSet(2, -output);
      motorSet(6, -output);
      motorSet(10, -output);

    }
    if ((millis() - startTime) > timeOut) {
       break;
      }
    delay(20);


  }


lcdPrint(uart1, 2, "val is %d", gyroGet(mainGyro));

}
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
  encoderReset(liftEnc);
  while(abs(encoderGet(liftEnc)) < distance) {
    encoderGet(liftEnc);
motorsLiftUp();
    delay(20);
  }
  encoderGet(liftEnc);
  if (abs(encoderGet(liftEnc)) > distance) {
motorsLiftStop();
    encoderReset(liftEnc);
  }
}

void liftDown(int distance){
  encoderReset(liftEnc);
  while(abs(encoderGet(liftEnc)) < distance) {
    encoderGet(liftEnc);
motorsLiftDown();
    delay(20);
  }
  encoderGet(liftEnc);
  if (abs(encoderGet(liftEnc)) > distance) {
    motorsLiftStop();
    encoderReset(liftEnc);
  }
}

void chainUp(int distance){
  analogRead(2);
while (analogRead(2) > 9){
  motorsChainUp();
  analogRead(2);
  delay(20);
}
if (analogRead(2) <= 9){
  motorsChainStop();
}
}

void chainDown(int distance){
  analogRead(2);
while (analogRead(2) < distance){
  motorsChainDown();
  analogRead(2);
  delay(20);
}
if (analogRead(2) >= distance){
  motorsChainStop();
}
}
void clawOpen(int distance, int timeOut ){
  long startTime = millis();
  analogRead(4);
while (analogRead(4) <  distance){
  motorsClawOpen();
  analogRead(4);
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
  analogRead(4);
while (analogRead(4) >  distance){
  motorsClawClosed();
  analogRead(4);
  delay(20);
}
if (analogRead(4) <= distance){
motorsClawStop();
}

}
void mobileLiftUp(){
  analogRead(3);
while (analogRead(3) > 20){
motorsMobileUp();
analogRead(3);

delay(20);
}
if (analogRead(3) <= 20){
motorsMobileStop();
}

}

void mobileLiftDown(){
  analogRead(3);
while (analogRead(3) < 700){
motorsMobileDown();
  analogRead(3);
  delay(20);
}
analogRead(3);
if (analogRead(3) >  700){
motorsMobileStop();
}
}

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
    motorSet(2, -output);
    motorSet(6, -output);
    motorSet(10, -output);
    if ((millis() - startTime) > timeOut) {
       break;
      }

    delay(20);

}


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
  motorSet(1, output);
  motorSet(2, output);
  motorSet(6, output);
  motorSet(10, output);
  if ((millis() - startTime) > timeOut) {
     break;
    }

  delay(20);
}






lcdPrint(uart1, 2, "val is %d", gyroGet(mainGyro));

}
