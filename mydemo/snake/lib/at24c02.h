#ifndef _AT24C02_H
#define _AT24C02_H
#include "global.h"

sbit SCL = P2 ^ 1;
sbit SDA = P2 ^ 0;

void i2cStart();
void i2cStop();
uchar i2cSendByte(uchar dat);
uchar i2cReadByte();
void at24c02Write(uchar addr, uchar dat);
uchar at24c02Read(uchar addr);
//
void i2cStart()
{
    SDA = 1;
    delay(1);
    SCL = 1;
    delay(1);
    ; //建立时间是SDA保持时间>4.7us
    SDA = 0;
    delay(1);
    ; //保持时间是>4us
    SCL = 0;
    delay(1);
}
void i2cStop()
{
    SDA = 0;
    delay(1);
    SCL = 1;
    delay(1); //建立时间大于4.7us
    SDA = 1;
    delay(1);
}
uchar i2cSendByte(uchar dat)
{
    uchar a = 0, b = 0;     //最大255，一个机器周期为1us，最大延时255us。
    for (a = 0; a < 8; a++) //要发送8位，从最高位开始
    {
        SDA = dat >> 7; //起始信号之后SCL=0，所以可以直接改变SDA信号
        dat = dat << 1;
        delay(1);
        SCL = 1;
        delay(1); //建立时间>4.7us
        SCL = 0;
        delay(1); //时间大于4us
    }
    SDA = 1;
    delay(1);
    SCL = 1;
    while (SDA) //等待应答，也就是等待从设备把SDA拉低
    {
        b++;
        if (b > 200) //如果超过2000us没有应答发送失败，或者为非应答，表示接收结束
        {
            SCL = 0;
            delay(1);
            return 0;
        }
    }
    SCL = 0;
    delay(1);
    return 1;
}
uchar i2cReadByte()
{
    uchar a = 0, dat = 0;
    SDA = 1; //起始和发送一个字节之后SCL都是0
    delay(1);
    for (a = 0; a < 8; a++) //接收8个字节
    {
        SCL = 1;
        delay(1);
        dat <<= 1;
        dat |= SDA;
        delay(1);
        SCL = 0;
        delay(1);
    }
    return dat;
}
//3个地址
void at24c02Write(uchar addr, uchar dat)
{
    i2cStart();
    i2cSendByte(0xa0); //发送写器件地址
    i2cSendByte(addr); //发送要写入内存地址
    i2cSendByte(dat);  //发送数据
    i2cStop();
}
uchar at24c02Read(uchar addr)
{
    uchar num;
    i2cStart();
    i2cSendByte(0xa0); //发送写器件地址
    i2cSendByte(addr); //发送要读取的地址
    i2cStart();
    i2cSendByte(0xa1);   //发送读器件地址
    num = i2cReadByte(); //读取数据
    i2cStop();
    return num;
}
#endif
