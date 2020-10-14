#ifndef _INTERRUPTION_H
#define _INTERRUPTION_H
#include "global.h"
void int0InitInter0()
{
    //设置 INT0
    IT0 = 1; //跳变沿出发方式（下降沿）
    EX0 = 1; //打开 INT0 的中断允许。
    EA = 1;  //打开总中断
}
void int1InitInter2()
{
    //设置INT1
    IT1 = 1; //跳变沿出发方式（下降沿）
    EX1 = 1; //打开INT1的中断允许。
    EA = 1;  //打开总中断
}

#endif
