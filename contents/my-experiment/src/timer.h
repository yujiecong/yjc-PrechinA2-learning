#ifndef _TIMER_H
#define _TIMER_H
#include "global.h"
//中断号1
void timer0Init()
{
    TMOD |= 0X01; //选择为定时器0模式，工作方式1，仅用TR0打开启动。

    TH0 = 0XFC; //给定时器赋初值，定时1ms
    TL0 = 0X18;
    ET0 = 1; //打开定时器0中断允许
    EA = 1;  //打开总中断
    TR0 = 1; //打开定时器
}
//中断号3
void timer1Init()
{
    TMOD |= 0X10; //选择为定时器1模式，工作方式1，仅用TR1打开启动。

    TH1 = 0XFC; //给定时器赋初值，定时1ms
    TL1 = 0X18;
    ET1 = 1; //打开定时器1中断允许
    EA = 1;  //打开总中断
    TR1 = 1; //打开定时器
    void Timer0() interrupt 1
    {
        static u16 i;
        TH0 = 0XFC; //给定时器赋初值，定时1ms
        TL0 = 0X18;
        i++;
        if (i == 1000)
        {
            i = 0;
            led = ~led;
        }
    }
}
#endif
