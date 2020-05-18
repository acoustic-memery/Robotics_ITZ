#ifndef AUTODEFAULTS_H_
#define AUTODEFAULTS_H_
#include "main.h"

void go(int way, int distance, int timeOut, int deriv, int gain);
void turnGo(int distance, int way, float gain, float kd, int timeOut);

#define DERIVATIVE 6
#define GYRODERIV 5

void drive (int distance);
//hi
void driveBack (int distance);

void liftScore3(void*parameter);

void chainResetTask(void*parameter);

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

void liftDown(void*parameter);

void chainUp(int distance);

void chainDown(int distance, int timeut);

void chainGrabTask(void*parameter);

void chainScoreTask(void*parameter);

void chainBackTask(void*parameter);

void liftScore2(void*parameter);

void liftPidUp(int timeOut, int target, float gain);

void liftPidDown(int timeOut, int target, float gain);

void clawOpen(int distance, int timeOut);

void clawClosed(int distance);

void mobileLiftUp();

void mobileLiftDown();

void mobileLiftStop();

void resetAxis(float gain, int timeOut);

void liftScore (void*parameter);

#endif
