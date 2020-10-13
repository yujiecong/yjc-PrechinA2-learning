#include "global.h"
#include "leddt.h"
#include "infrared.h"
#include "74HC595.h"
#include "beep.h"
void main()
{
    uchar i;
    irInitInter0();

    while (1)
    {
        uchar v = irGetValue();

        // for (i = 0; i < 8; i++)
        // {
        //     digDisplay(i, 0x01 & v);
        //     v = v >> 1;
        // }

        digDisplay(0, 0);
        digDisplay(1, 16);
        digDisplay(2, v / 16);
        digDisplay(3, v % 16);
        if (v == 0x16)
        {
            beeP(1000);
        }
    }
}
void ReadIr() interrupt 0
{
    irLiesten();
}
