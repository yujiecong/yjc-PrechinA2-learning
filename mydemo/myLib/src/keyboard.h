#ifndef _KEYBOARD_H
#define _KEYBOARD_H
#include"global.h"
sbit k1 = P3 ^ 1;
sbit k2 = P3 ^ 0; 
sbit k3 = P3 ^ 2; 
sbit k4 = P3 ^ 3; 
uchar keyValue;
void keyListen(void (*listenFunc)(),uchar keyn); //无参函数作为函参

void keyListen(void(*listenFunc)(), uchar keyn)
{
    uchar t=P3<<4;
    if(t!=0xf0){
        switch(t){
            case(0xd0):keyValue=1;break;
            case(0xe0):keyValue=2;break;
            case(0xb0):keyValue=3;break;
            case(0x70):keyValue=4;break;
        }
        if(keyValue==keyn){
            listenFunc();
        }
    }
    // switch (keyn)
    // {
    // case 1:
    //     if (k1 == 0) //检测按键K1是否按下
    //     {
    //         delay(1000); //消除抖动 一般大约10ms
    //         if (k1 == 0) //再次判断按键是否按下
    //         {
    //             listenFunc();
    //         }
    //         while (!k1)
    //             ; //检测按键是否松开
    //     }
    //     break;
    // case 2:
    //     if (k2 == 0) //检测按键K2是否按下
    //     {
    //         delay(1000); //消除抖动 一般大约10ms
    //         if (k2 == 0) //再次判断按键是否按下
    //         {
    //             listenFunc();
    //         }
    //         while (!k2)
    //             ; //检测按键是否松开
    //     }
    //     break;
    // case 3:
    //     if (k3 == 0) //检测按键K3是否按下
    //     {
    //         delay(1000); //消除抖动 一般大约10ms
    //         if (k3 == 0) //再次判断按键是否按下
    //         {
    //             listenFunc();
    //         }
    //         while (!k3)
    //             ; //检测按键是否松开
    //     }
    //     break;
    // case 4:
    //     if (k4 == 0) //检测按键K4是否按下
    //     {
    //         delay(1000); //消除抖动 一般大约10ms
    //         if (k4 == 0) //再次判断按键是否按下
    //         {
    //             listenFunc();
    //         }
    //         while (!k4)
    //             ; //检测按键是否松开
    //     }
    //     break;
    // }
}

#endif