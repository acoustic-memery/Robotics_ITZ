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
#include "lcdFunctions.h"
#include "autoFunctions.h"


void meme(int speed){
  while((digitalRead(5) == HIGH)){
    motorsForeward(speed);
    delay(10);}

  if (digitalRead(5) == LOW){
    motorsStop();}
}
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


 void intakeControl(void*parameter){
   intakeTurn(3000, 30);
 }


 void intakeControl2 (void* parameter) {
   intakeTurn(3000, 30);
 }
/*
 void scoreMogoStraight () {
   taskCreate(intakeControl, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
   go(1, 2500, 6500);
   turnGo(45, 2.5, 30, 5000);

 }

 void grabMogoRight () {
   taskCreate(intakeControl, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);

 }

 void grabMogoLeft () {
   taskCreate(intakeControl, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);

 }

*/
void autonomous() {
  lcdClear(uart1);
  digitalWrite(2, HIGH);

  //taskCreate(autoOutput, TASK_DEFAULT_STACK_SIZE, NULL , TASK_PRIORITY_DEFAULT);
  //taskCreate(autoDrop, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);



/////////////////////begin skills
 //taskCreate(autoOutput, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);


///////tuning
/*
meme();
turnGo(85, 2, 3,1000);
go(2, 750, 2000, 5, 1.25);
*/

/*

go(1, 500, 1500, 4.8, 1.5);
lcdPrint(uart1, 1, "val is %d", abs(encoderGet(driveEncRight)));
turnGo(90, 1, 3,1, 4000);*/ //tuned



//////////first mogo

/*
mogoUp(1);
delay(200);
mogoStop();


digitalWrite(2, LOW);

delay(250);

digitalWrite(2, HIGH);

digitalWrite(2, LOW);

delay(250);

digitalWrite(2, HIGH);

digitalWrite(2, LOW);


delay(250);

digitalWrite(2, HIGH);

digitalWrite(2, LOW);

delay(250);

digitalWrite(2, HIGH);
intakeReset();

go(1, 2000, 2500, 4.8, 1.5);

TaskHandle mogo = taskCreate(mobileLift, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);

go(1, 1000, 1500, 4.8, 1.5);
turnGo(45, 2, 3,2, 900);
go(1, 375, 700, 4.8, 1.5);
turnGo(45, 1, 3,2, 900);
go(1, 500, 1500, 4.8, 1.5);
taskDelete(mogo);
mogoStop();
digitalWrite(2,LOW);
delay(500);
digitalWrite(2, HIGH);


go(2, 500, 850, 4.8, 1.5);
turnGo(90, 2, 3,1, 1800);
go(1, 600, 900, 4.8, 1.5);
turnGo(90, 2, 3,1, 1800);
delay(500);
go(2, 450, 750, 4.8, 1.5);
intakeReset();

go(1, 2000, 2500, 4.8, 1.5);

TaskHandle mogo2 = taskCreate(mobileLift, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);

go(1, 1000, 1500, 4.8, 1.5);
turnGo(45, 2, 3,2, 900);
go(1, 375, 700, 4.8, 1.5);
turnGo(45, 1, 3,2, 900);
go(1, 500, 1500, 4.8, 1.5);
taskDelete(mogo);
mogoStop();
digitalWrite(2,LOW);
delay(500);
digitalWrite(2, HIGH);


go(2, 500, 1500, 4.8, 1.5);


meme(35);
motorsStop();
delay(250);
go(2, 200, 1500, 4.8, 1.5);
turnGo(90, 2, 3,2, 2000);

go(2, 1300, 2200, 4.8, 1.5);

/////////squared

go(1, 775, 2000, 4.8, 1.5);
turnGo(90, 2, 3,2, 2500);
intakeReset();
go(1, 1350, 2400, 4.8, 1.5);
TaskHandle mogo3 = taskCreate(mobileLift2, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
delay(800);
go(2, 350, 1400, 4.8, 1.5);
turnGo(90, 2, 3,1, 2500);

taskDelete(mogo3);
intakeReset();
turnGo(90, 2, 3,1, 2500);
TaskHandle mogoa = taskCreate(mobileLift2, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
go(2, 120, 750, 4.8, 1.5);
turnGo(90, 1, 3,2, 4000);
taskDelete(mogoa);
intakeReset();
go(1, 470, 1500, 4.8, 1.5);
TaskHandle mogo4 = taskCreate(mobileLift, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
delay(500);
go(2, 1900, 4000, 4.8, 1.5);
turnGo(155, 1, 3, 2.5, 4000);
meme(60);
go(2, 200, 750, 4.8, 1.5);
motorsStop();
digitalWrite(2, LOW);
delay(500);
digitalWrite(2, HIGH);
taskDelete(mogo4);
*/

go(2, 500, 2000, 1.5 , 0.25 );

lcdPrint(uart1, 1, "val is %d", abs(encoderGet(driveEncRight)));


}
