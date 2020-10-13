#include "global.h"
#include "xpt2046.h"
#include "leddt.h"
void main()
{
    uint temp, i = 0;
    temp = getAD_Data(0xD4);
    while (1)
    {
        if (i == 50)
        {
            temp = getAD_Data(0xD4);
            i = 0;
        }
        i++;
        digDisplay(0, temp / 1000);
        digDisplay(1, temp % 1000 / 100);
        digDisplay(2, temp % 1000 % 100 / 10);
        digDisplay(3, temp % 1000 % 100 % 10);
    }
}
