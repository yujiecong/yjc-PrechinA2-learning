#include "global.h"
#include "led.h"
#include "74HC595.h"
void main()
{
    uchar n = 0xfe;
    P2 = n;
    while (1)
    {
        sendByte(n);
        n = _crol_(n, 1);
        P2 = n;
        delay(50000);
    }
}
