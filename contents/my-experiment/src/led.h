#ifndef _LED_H
#define _LED_H
#include "global.h"
/*
有些是以ms作为单位的


*/
//
void ledTurnOn();
void lednTurn(uchar n, uchar swch);
void ledTurnoff();
void ledWater();
//
void ledWater(uint ms, uchar n)
{
    uchar i;
    lednTurn(n, 1);

    for (i = 0; i < 7; i++)
    {
        P2 = _crol_(P2, 1);
        delay(ms * 100);
    }
}
void ledTurnoff()
{
    P2 = 0xff;
}

void ledTurnOn()
{
    P2 = 0x00;
}

void lednTurn(uchar n, uchar swch)
{
    if (n >= 0 && n < 8)
    {
        //选择P2 ^ 4~7
        uchar i, j = 1;
        for (i = 0; i < n; i++)
            j <<= 2;
        if (!swch)
        {
            P2 = P2 & j;
        }
        else
        {
            if (n == 0)
            {
                P2 = P2 & 0xfe;
            }
            else
                P2 = P2 & (j - 1);
        }
    }
    else
        ;
}
#endif