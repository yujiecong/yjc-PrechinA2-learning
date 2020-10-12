#ifndef _INTERRUPTION_H
#define _INTERRUPTION_H
#include"global.h"
void int0Init()
{
    //设置 INT0
    IT0 = 1; //跳变沿出发方式（下降沿）
    EX0 = 1; //打开 INT0 的中断允许。
    EA = 1;  //打开总中断
}


#endif
