#ifndef _XPT2046_H
#define _XPT2046_H
#include "global.h"

sbit DOUT = P3 ^ 7; //输出
sbit CLK = P3 ^ 6;  //时钟
sbit DIN = P3 ^ 4;  //输入
sbit CS = P3 ^ 5;   //片选
uint readAD_Data(uchar cmd);
uint sPI_Read(void);
void sPI_Write(uchar dat);
uint getAD_Data(uchar word);
//

uint getAD_Data(uchar word)
{
    // 	如果要检测转换电位器模拟信号，控制字命令寄存器值为0X94或者0XB4.
    // 如果要检测转换热敏电阻模拟信号，控制字命令寄存器值为0XD4.
    // 如果要检测转换光敏电阻模拟信号，控制字命令寄存器值为0XA4.
    // 如果要检测转换AIN3通道上模拟信号，控制字命令寄存器值为0XE4.
    return readAD_Data(word);
}

/****************************************************************************
*函数名：SPI_Write
*输  入：dat：写入数据
*输  出：无
*功  能：使用SPI写入数据
****************************************************************************/

void sPI_Write(uchar dat)
{
    uchar i;
    CLK = 0;
    for (i = 0; i < 8; i++)
    {
        DIN = dat >> 7; //放置最高位
        dat <<= 1;
        CLK = 0; //上升沿放置数据

        CLK = 1;
    }
}
/****************************************************************************
*函数名：SPI_Read
*输  入：无
*输  出：dat：读取 到的数据
*功  能：使用SPI读取数据
****************************************************************************/

uint sPI_Read(void)
{
    uint i, dat = 0;
    CLK = 0;
    for (i = 0; i < 12; i++) //接收12位数据
    {
        dat <<= 1;

        CLK = 1;
        CLK = 0;

        dat |= DOUT;
    }
    return dat;
}

/****************************************************************************
*函数名：Read_AD_Data
*输  入：cmd：读取的X或者Y
*输  出：endValue：最终信号处理后返回的值
*功  能：读取触摸数据
****************************************************************************/
uint readAD_Data(uchar cmd)
{
    uchar i;
    uint AD_Value;
    CLK = 0;
    CS = 0;
    sPI_Write(cmd);
    for (i = 6; i > 0; i--)
        ;    //延时等待转换结果
    CLK = 1; //发送一个时钟周期，清除BUSY
    _nop_();
    _nop_();
    CLK = 0;
    _nop_();
    _nop_();
    AD_Value = sPI_Read();
    CS = 1;
    return AD_Value;
}

#endif
