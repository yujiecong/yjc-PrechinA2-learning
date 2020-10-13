#include "global.h"
#include "led.h"
#include "74HC595.h"

void main()
{

    uchar i;
    while (1)
    {
        for (i = 0; i < 8; i++)
        {
            choice88Led(i, i, 1);
            delayS();
            choice88Led(i, i, 0);
        }

        /* code */
    }
}
