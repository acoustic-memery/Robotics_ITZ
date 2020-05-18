/** @file auto.c
 * @brief File for autonomous code
 *
 * This file should contain the user autonomous() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

/*
 * Runs the user autonomous code. This function will be started in its own task with the default
 * priority and stack size whenever the robot is enabled via the Field Management System or the
 * VEX Competition Switch in the autonomous mode. If the robot is disabled or communications is
 * lost, the autonomous task will be stopped by the kernel. Re-enabling the robot will restart
 * the task, not re-start it from where it left off.
 *
 * Code running in the autonomous task cannot access information from the VEX Joystick. However,
 * the autonomous function can be invoked from another task if a VEX Competition Switch is not
 * available, and it can access joystick information if called in this way.
 *
 * The autonomous task may exit, unlike operatorControl() which should never exit. If it does
 * so, the robot will await a switch to another mode or disable/enable cycle.
 */
#define FOREWARD 1
#define BACKWARDS 2
#define RIGHT 1
#define LEFT 2
#define UP 1
#define DOWN 2
#define OPEN 1
#define CLOSED 2



void motorsForeward (float output) {

}

void motorsBackward (float output) {

}

void goForeward () {
  motorSet(1, 127);
  motorSet(2,127);
  motorSet(5, -127);
  motorSet(6, -127);
  motorSet(9, 127);
  motorSet(10, 127);
}

void goBack () {
  motorSet(1, -127);
  motorSet(2, -127);
  motorSet(5, 127);
  motorSet(6, 127);
  motorSet(9, -127);
  motorSet(10, -127);
}



void motorsRight () {
  motorSet(1, 127);
  motorSet(2,-127);
  motorSet(5, 127);
  motorSet(6, -127);
  motorSet(9, 127);
  motorSet(10, -127);
}

void motorsLeft () {

  motorSet(1, -127);
  motorSet(2, 127);
  motorSet(5, -127);
  motorSet(6, 127);
  motorSet(9, -127);
  motorSet(10, 127);

}

void motorsStop () {
  motorSet(1, 0);
  motorSet(2,0);
  motorSet(5, 0);
  motorSet(6, 0);
  motorSet(9, 0);
  motorSet(10, 0);

}

void liftBack () {
  motorSet(8, -127);
  motorSet(7, -127);
  motorSet(3, -127);
}

void liftForeward () {
  motorSet(8, 127);
  motorSet(7, 127);
  motorSet(3, 127);
}

void liftStop () {
  motorSet(8, 0);
  motorSet(7, 0);
  motorSet(3, 0);

}

void mobileLiftUp () {
  motorSet(4, -127);
}

void mobileLiftDown () {
  motorSet(4, 127);
}

void mobileLiftStop () {
  motorSet(4, 0);

}

void stopEverything() {
    motorsStop();
    mobileLiftStop();
    liftStop();
  }

  #define INTEGRAL 1
  #define DERIVATIVE 0.0


  void go(int way, int distance) {
    encoderReset(driveEncLeft);
    encoderReset(driveEncRight);

    float encTickLastLeft;
    float encTickLastRight; //tick last left and right


    float outputLeft;
    float outputRight; //power to be outputed left and right

    float errLeft;
    float errRight; //target distance - actual distance left and right

    float errTotalRight;
    float errTotalLeft; //total accumulated error left and right

    int errAccuLeft = 50;
    int errAccuRight = 50; //total accumulated error left and right if less than integral cap

    float gain = 0.25; //motor gain for proportional term

    float integCap = 50/INTEGRAL; //integral cap

    float propLeft;
    float propRight; //calculated proportional term left and right
    float integLeft;
    float integRight; //calculated integral term left and right
    float derivLeft;
    float derivRight; //calculated derivative term left and right





    while(((abs(encoderGet(driveEncLeft)) +
(abs(encoderGet(driveEncRight)))) / 2) < distance) { //while less than target distance



       errLeft = distance - (abs(encoderGet(driveEncLeft)));
       errRight = distance - (abs(encoderGet(driveEncRight)));
//calculate error

       if(errRight < errAccuRight) {errTotalRight += errRight;}
       else {errTotalRight = 0;}

       if(errLeft < errAccuLeft) {
         errTotalLeft += errLeft;}
       else {errTotalLeft = 0;} //makes integral term 0 if error is less than 50 (this has not been properly tuned)

       if(errTotalLeft > integCap) {
         errTotalLeft = 50/INTEGRAL;
       }

       if(errTotalRight > integCap) {
         errTotalRight = 50/INTEGRAL; //if integral term is greater than 50 (after previous calculation) integral term is incorperated
       }

//the above part of the function is only for managing when the integral is enganged

       propLeft = errLeft * gain;
       propRight = errRight * gain; //calculate proprtional term

       integLeft = errTotalLeft * INTEGRAL;
       integRight = errTotalRight * INTEGRAL; //calculate integral term

       derivLeft = (errLeft - encTickLastLeft) * DERIVATIVE;
       derivRight = (errRight - encTickLastRight) * DERIVATIVE;
//calculate derivative term

encTickLastRight = errRight;
encTickLastLeft = errLeft; //calculate enctick last

outputLeft = propLeft + integLeft + derivLeft;
outputRight = propRight + integRight + derivRight; //output P + I + D for both sides

if (outputLeft > 127) {
   outputLeft = 127;
}

if (outputRight > 127) {
   outputRight = 127;
}

//make output 127 if greater than 127

if(way == 1) {
//if forewards

motorSet(1, outputRight);
motorSet(2, outputLeft);
motorSet(5, -outputLeft);
motorSet(6, -outputRight);
motorSet(9, outputRight);
motorSet(10, outputLeft);



}

if(way == 2) {
//if backwards

motorSet(1, -outputRight);
motorSet(2, -outputLeft);
motorSet(5, outputLeft);
motorSet(6, outputRight);
motorSet(9, -outputRight);
motorSet(10, -outputLeft);



}


delay(20);

    }



  }

  void drive (int distance) {
    encoderReset(driveEncLeft);
    while(abs(encoderGet(driveEncLeft)) < distance) {
      encoderGet(driveEncLeft);
      goForeward();
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
      goBack();
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

  void deploy (int target) {
    analogRead(1);
    while(analogRead(1) < target) {
      analogRead(1);
    mobileLiftDown();
      delay(20);
    }
    analogRead(1);
    if (analogRead(1) > target) {
      mobileLiftStop();
    }

  }


void skillsAuto () {

}

void compLeftAuto () {
  mobileLiftDown();
  delay(200);
  mobileLiftStop();
  mobileLiftUp();
  delay(150);
  mobileLiftStop();

}

void compRightAuto () {


}

void autonomous() {
  if (program == 1) {
    compLeftAuto();
  }
  else if (program == 2) {
    compLeftAuto();
  }
  else if (program == 3) {
    compRightAuto();
  }

}
