#ifndef _KEYBOARDS_H
#define _KEYBOARDS_H
#include "global.h"
#define GPIO_KEY P1
uchar keyValue;
/*
矩阵键盘S版本从0到15,
并且是左上角到右下角
*/
void keyListenS(void(*listenFunc)(), uchar keyn);
void keyListenS(void(*listenFunc)(), uchar keyn)//0~15取值
{
    char a = 0;
    GPIO_KEY = 0x0f;
    if (GPIO_KEY != 0x0f) //读取按键是否按下
    {
        delay(1000);          //延时10ms进行消抖
        if (GPIO_KEY != 0x0f) //再次检测键盘是否按下
        {
            //测试列
            GPIO_KEY = 0X0F;
            switch (GPIO_KEY)
            {
            case (0X07):
                keyValue = 0;
                break;
            case (0X0b):
                keyValue = 1;
                break;
            case (0X0d):
                keyValue = 2;
                break;
            case (0X0e):
                keyValue = 3;
                break;
            }
            //测试行
            GPIO_KEY = 0XF0;
            switch (GPIO_KEY)
            {
            case (0X70):
                keyValue = keyValue;
                break;
            case (0Xb0):
                keyValue = keyValue + 4;
                break;
            case (0Xd0):
                keyValue = keyValue + 8;
                break;
            case (0Xe0):
                keyValue = keyValue + 12;
                break;
            }
        }
    }
    while ((a < 50) && (GPIO_KEY != 0xf0)) //检测按键松手检测
    {
        delay(100);
        a++;
    }
    if(keyValue==keyn){
        listenFunc();
    }

}

#endif