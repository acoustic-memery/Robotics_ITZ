#ifndef AUTOFUNCTIONS_H_
#define AUTOFUNCTIONS_H_
#include "main.h"


void motorsForeward(int speed);

void motorsBackward(int speed);

void motorsStop();

void motorsRight(int speed);

void mobileLift(void*parameter);

void mobileLift2(void*parameter);

void motorsLeft(int speed);

void mogoUp(int speed);

void mogoDown(int speed);

void mogoLift1(void*parameter);

void mogoStop();

void go(int way, int distance, int timeout, float deriv, float gain);

void turnGo (int distance, int way, float gain, float kd, int timeout);

void autoDrop(void*parameter);

void intakeUp(int amount, int hDistance);
void intakeTurn(int amount, int hDistance);

void intakeControl(void*parameter);

void intakeReset();

void intakeDelay(int amount);

#endif
