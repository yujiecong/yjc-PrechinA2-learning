#include "global.h"
#include "xpt2046.h"
#include "leddt.h"
void main()
{
    uint temp;
    while (1)
    {
        temp = getAD_Data(0x94);
        digDisplay(0, temp / 1000);
        digDisplay(1, temp % 1000 / 100);
        digDisplay(2, temp % 1000 % 100 / 10);
        digDisplay(3, temp % 1000 % 100 % 10);
    }
}
