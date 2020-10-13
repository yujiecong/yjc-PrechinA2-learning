#ifndef _DCM_H
#define _DCM_H
#include "global.h"
sbit moto = P1 ^ 0;
//

void motoRun(uint ms);
void endMoto();
void startMoto();
//
void motoRun(uint ms)
{
    uchar i;
    moto = 0; //关闭电机
    delay(ms * 100);
    moto = 0; //关闭电机
}
void endMoto()
{
    moto = 0;
}
void startMoto()
{
    moto = 1;
}
#endif
