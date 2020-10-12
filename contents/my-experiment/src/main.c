#include "global.h"
#include "led.h"
#include "74HC595.h"
void main()
{
    P0 = 0x00;
    while (1)
    {
        choice88Led((uchar)0xfe, (uchar)0x00);
        // send2Byte(0xfe, 0x01);
    }
}
