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
#include "autoDefaults.h"

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

 void compLs(){
   //gyroReset(mainGyro);
//motorsClawClosed();
//liftUp(40);
//mobileLiftDown();
//go(1, 1450, 2000);
//motorsStop();
//mobileLiftUp();
//liftDown(10);
//delay(500);
//clawOpen(149, 400);
//motorsClawStop();
//delay(100);
//resetAxis(0.5, 1000);
//go(2, 400, 1500);
//turnGo(150, 1, 0.7, 7000);
//go(1, 600, 1500);
//turnGo(60, 1, 0.5, 7000);
//go(1, 30, 750);
//mobileLiftDown();
//motorsBack();
//delay(1000);
//motorsStop();
turnGo(180, 2, 1.5, 7000);


 }

 void compRs() {
   gyroReset(mainGyro);
motorsClawClosed();
liftUp(40);
mobileLiftDown();
go(1, 1500, 2000);
motorsStop();
mobileLiftUp();
liftDown(10);
delay(500);
clawOpen(149, 400);
motorsClawStop();
delay(100);
resetAxis(0.5 , 1000);
go(2, 400, 1500);
turnGo(180, 2, 1.5, 2500);
go(1, 450, 1500);

turnGo(80, 2, 1.5, 1000);
go(1, 30, 500);
mobileLiftDown();
motorsBack();
delay(1000);
motorsStop();


 }

 void skills() {
   motorsClawClosed();
   liftUp(75);
   go(1, 500, 4000);
  motorsStop();
   liftDown(10);
   delay(300);
   clawOpen(149, 2000);
   go(2, 150, 600);
   motorsStop();
   liftDown(58);
   driveRight(60);
   go(1, 500, 3000);
  // turnGo(85, 1, 0.3, 2000);
  // go(1, 100, 1600);
  // motorsStop();
   //motorsChainDown();
   //delay(1000);
   //motorsChainStop();
   //motorsClawClosed();
   //motorsChainUp();
   //delay(1000);
  // motorsChainStop();







}

void postRs(){
    motorsClawClosed();
   liftUp(75);
   go(1, 500, 4000);
  motorsStop();
   liftDown(10);
   delay(300);
   clawOpen(149, 2000);
   go(2, 150, 600);
   motorsStop();
   liftDown(58);

}
void autonomous() {
  if (program == 1) {
 skills();
}
else if (program == 2) {
compLs();
}
else if (program == 3) {
  compRs();

}
else if (program == 4) {
  postRs();
}
}
