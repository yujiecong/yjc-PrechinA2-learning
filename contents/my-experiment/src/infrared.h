#ifndef _INFRARED_H
#define _INFRARED_H
#include "global.h"
sbit IRIN = P3 ^ 2;
void irInit();
void irInit()
{
    IT0 = 1;  //下降沿触发
    EX0 = 1;  //打开中断0允许
    EA = 1;   //打开总中断
    IRIN = 1; //初始化端口
}
#endif
