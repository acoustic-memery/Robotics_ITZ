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
 *int timeOut
 * The autonomous task may exit, unlike operatorControl() which should never exit. If it does
 * so, the robot will await a switch to another mode or disable/enable cycle.
 */
void postRed(){

  motorsClawClosed();
  taskCreate(liftScore, TASK_DEFAULT_STACK_SIZE, NULL , TASK_PRIORITY_DEFAULT);
  delay(750);
  TaskHandle score = taskCreate(chainScoreTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
  go(1, 350, 900, 5.5, 1.7);
  motorsClawOpen();
  delay(100);
  motorSet(4,-10);


  go(2, 150, 500, 5.5, 1.7);
  taskDelete(score);
  TaskHandle chainDown = taskCreate(chainBackTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
  TaskHandle liftDown1 = taskCreate(liftDown, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
  turnGo(90, 1, 3, 1, 1000);
  go(1, 200, 800, 5.5, 1.7);
  motorsClawClosed();
  delay(200);
  taskDelete(chainDown);
  taskDelete(liftDown1);
  TaskHandle score1 = taskCreate(chainResetTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
  taskCreate(liftScore, TASK_DEFAULT_STACK_SIZE, NULL , TASK_PRIORITY_DEFAULT);
  go(2, 225, 800, 5.5, 1.7);
  turnGo(90, 2, 3, 1, 1000);
  taskDelete(score1);
  //delay(200);

  TaskHandle score2 = taskCreate(chainScoreTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
    go(1, 50, 300, 5.5, 1.7);
delay(400);
  motorsClawOpen();
  delay(100);
  taskDelete(score2);
  motorSet(4,-10);

  go(2, 50, 300, 5.5, 1.7);

  TaskHandle chainDown2 = taskCreate(chainBackTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
  TaskHandle liftDown3 = taskCreate(liftDown, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
delay(200);
  turnGo(90, 1, 3, 1, 1000);
  go(1, 500, 850, 5.5, 1.7);
  motorsClawClosed();
  delay(200);
  taskDelete(chainDown2);
  taskDelete(liftDown3);
  TaskHandle score3 = taskCreate(chainResetTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
  go(2, 550, 900, 5.5, 1.7);
  turnGo(90, 2, 3, 1, 1000);
    go(1, 75, 500, 5.5, 1.7);
  taskDelete(score3);
  taskCreate(liftScore, TASK_DEFAULT_STACK_SIZE, NULL , TASK_PRIORITY_DEFAULT);
  delay(650);

  TaskHandle score4 = taskCreate(chainScoreTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
delay(500);
  motorsClawOpen();
  delay(100);
  taskDelete(score4);
  motorSet(4,-10);
  go(2, 75, 500, 5.5, 1.7);
}


void mogoRed(){
  motorsClawClosed();
  taskCreate(liftScore, TASK_DEFAULT_STACK_SIZE, NULL , TASK_PRIORITY_DEFAULT);
  delay(750);
  TaskHandle score = taskCreate(chainScoreTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
  go(1, 350, 900, 5.5, 1.7);
  motorsClawOpen();
  delay(100);
motorsClawStop();



  taskDelete(score);
  TaskHandle chainDown = taskCreate(chainResetTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
//  TaskHandle liftDown1 = taskCreate(liftDown, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
  //turnGo(89, 1, 3, 1, 1200);
//taskDelete(liftDown1);
  taskDelete(score);
  //  go(1, 1000, 3000, 5.5, 1.7);
      turnGo(90, 1, 3, 1, 1000);

      go(1, 1500, 2300, 5.5, 1.7);
      TaskHandle liftDown1 = taskCreate(liftDown, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);

        turnGo(75, 2, 3, 1, 1000);
    taskDelete(liftDown1);
            go(1, 2000, 4000, 5.5, 1.7);
}


void mogoBlue(){

    motorsClawClosed();
    taskCreate(liftScore, TASK_DEFAULT_STACK_SIZE, NULL , TASK_PRIORITY_DEFAULT);
    delay(750);
    TaskHandle score = taskCreate(chainScoreTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
    go(1, 350, 900, 5.5, 1.7);
    motorsClawOpen();
    delay(100);
  motorsClawStop();



    taskDelete(score);
    TaskHandle chainDown = taskCreate(chainResetTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
  //  TaskHandle liftDown1 = taskCreate(liftDown, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
    //turnGo(89, 1, 3, 1, 1200);
  //taskDelete(liftDown1);
    taskDelete(score);
    //  go(1, 1000, 3000, 5.5, 1.7);
        turnGo(90, 2, 3, 1, 1000);

        go(1, 1500, 2300, 5.5, 1.7);
        TaskHandle liftDown1 = taskCreate(liftDown, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);

          turnGo(75, 1, 3, 1, 1000);
      taskDelete(liftDown1);
              go(1, 2000, 4000, 5.5, 1.7);
}


void postBlue() {

      motorsClawClosed();
      taskCreate(liftScore, TASK_DEFAULT_STACK_SIZE, NULL , TASK_PRIORITY_DEFAULT);
      delay(750);
      TaskHandle score = taskCreate(chainScoreTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
      go(1, 350, 900, 5.5, 1.7);
      motorsClawOpen();
      delay(100);
      motorSet(4,-10);


      go(2, 150, 500, 5.5, 1.7);
      taskDelete(score);
      TaskHandle chainDown = taskCreate(chainBackTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
      TaskHandle liftDown1 = taskCreate(liftDown, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
      turnGo(90, 2, 3, 1, 1000);
      go(1, 200, 700, 5.5, 1.7);
      motorsClawClosed();
      delay(200);
      taskDelete(chainDown);
      taskDelete(liftDown1);
      TaskHandle score1 = taskCreate(chainResetTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
      taskCreate(liftScore, TASK_DEFAULT_STACK_SIZE, NULL , TASK_PRIORITY_DEFAULT);
      go(2, 220, 900, 5.5, 1.7);
      turnGo(90, 1, 3, 1, 1000);
      taskDelete(score1);
      //delay(200);

      TaskHandle score2 = taskCreate(chainScoreTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
        go(1, 50, 300, 5.5, 1.7);
    delay(400);
      motorsClawOpen();
      delay(100);
      taskDelete(score2);
      motorSet(4,-10);

      go(2, 50, 300, 5.5, 1.7);

      TaskHandle chainDown2 = taskCreate(chainBackTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
      TaskHandle liftDown3 = taskCreate(liftDown, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
    delay(200);
      turnGo(90, 2, 3, 1, 1000);
      go(1, 500, 850, 5.5, 1.7);
      motorsClawClosed();
      delay(200);
      taskDelete(chainDown2);
      taskDelete(liftDown3);
      TaskHandle score3 = taskCreate(chainResetTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
      go(2, 550, 900, 5.5, 1.7);
      turnGo(90, 1, 3, 1, 1000);
        go(1, 50, 500, 5.5, 1.7);
      taskDelete(score3);
      taskCreate(liftScore, TASK_DEFAULT_STACK_SIZE, NULL , TASK_PRIORITY_DEFAULT);
      delay(650);

      TaskHandle score4 = taskCreate(chainScoreTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
    delay(500);
      motorsClawOpen();
      delay(100);
      taskDelete(score4);
      motorSet(4,-10);
      go(2, 75, 500, 5.5, 1.7);

}


void autonomous() {
  if (program == 1) {
    postRed();
}
else if (program == 2) {
  mogoRed();
}
else if (program == 3) {
  mogoBlue();

}
else if (program == 4) {
  postBlue();
}
else if (program == 5) {

}

}
