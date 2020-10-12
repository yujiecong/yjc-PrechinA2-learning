#ifndef _74HC595_H
#define _74HC595_H
#include "global.h"
sbit SRCLK = P3 ^ 6; //移位 时钟 输入 相当于 SH_CP
//这里有冲突，因为reg52已经定义过RCLK了所以换一下
sbit RCLK_ = P3 ^ 5; //输出 时钟 输入 相当于 ST_CP
sbit SER = P3 ^ 4;   //输入的数据 例如0x0f 会输出并行的0000 1111
sbit LED = P0 ^ 7;   //外接线的一个脚，用来把OE置0
//

void sendByte(uint dat);
void choice88Led(uchar line, uchar column);
void send2Byte(uchar dat1, uchar dat2);
void choice88Led(uchar line, uchar column)
{

    uchar i, j = 1, l = 1;
    for (i = 0; i < line; i++)
        j <<= 2;
    for (i = 1; i < 8 - column; i++)
        l <<= 2;

    P0 = (0xff - l);
    sendByte(j);
}

//dat1是P0 dat2 是hc595的输出
void send2Byte(uchar dat1, uchar dat2)
{

    uchar a;

    SRCLK = 1;
    RCLK_ = 1;

    for (a = 0; a < 8; a++) //发送8位数
    {
        SER = dat1 >> 7; //从最高位开始发送
        dat1 <<= 1;

        SRCLK = 0; //发送时序
        _nop_();
        _nop_();
        SRCLK = 1;
    }

    for (a = 0; a < 8; a++) //发送8位数
    {
        SER = dat2 >> 7; //从最高位开始发送
        dat2 <<= 1;

        SRCLK = 0; //发送时序
        _nop_();
        _nop_();
        SRCLK = 1;
    }

    RCLK_ = 0;
    _nop_();
    _nop_();
    RCLK_ = 1;
}
void sendByte(uint dat)
{
    uchar a;
    SRCLK = 1; //右移输入时钟有效
    RCLK_ = 1; //输出有效
    //这一个for循环的意思是把8位数据先存入74hc595
    for (a = 0; a < 8; a++) //发送8位数
    {
        //输出有效
        SER = dat >> 7; //从最高位开始发送
        dat <<= 1;

        SRCLK = 0; //发送时序
        //nop 的作用，产生一个几十微秒的脉冲产生上升沿
        _nop_(); //相当于python的pass 或者说C语言的; 即空语句,在这里占用一个机器周期
        _nop_(); //相当于python的pass 或者说C语言的; 即空语句,在这里占用一个机器周期
        SRCLK = 1;
    }
    RCLK_ = 0;
    _nop_(); //相当于python的pass 或者说C语言的; 即空语句,在这里占用一个机器周期
    _nop_(); //相当于python的pass 或者说C语言的; 即空语句,在这里占用一个机器周期
    RCLK_ = 1;
}
#endif
