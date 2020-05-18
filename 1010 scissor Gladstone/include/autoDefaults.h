#ifndef AUTODEFAULTS_H_
#define AUTODEFAULTS_H_
#include "main.h"

void go (int way, int distance, int timeOut);
void turnGo(int distance, int way, float gain, int timeOut);

#define INTEGRAL 0
#define DERIVATIVE 6
#define GYRODERIV 5

void drive (int distance);

void driveBack (int distance);

void driveRight (int amount);

void driveleft (int amount);

void motorsForewards();

void motorsBack();

void motorsLeft();

void motorsRight();

void motorsStop();

void motorsLiftUp();

void motorsLiftDown();

void motorsLiftStop();

void motorsChainUp();

void motorsChainDown();

void motorsChainStop();

void motorsClawOpen();

void motorsClawClosed();

void motorsClawStop();

void motorsMobileUp();

void motorsMobileDown();

void motorsMobileStop();


void liftUp(int distance);

void liftDown(int distance);

void chainUp(int distance);

void chainDown(int distance);

void clawOpen(int distance, int timeOut);

void clawClosed(int distance);

void mobileLiftUp();

void mobileLiftDown();

void mobileLiftStop();

void resetAxis(float gain, int timeOut);

#endif
