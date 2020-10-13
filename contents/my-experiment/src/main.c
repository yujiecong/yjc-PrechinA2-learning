#include "global.h"
#include "lcd1206.h"
void main()
{
    uchar Disp[] = " HELLO WORLD ";
    uchar i;
    lcdInit();
    for (i = 0; i < sizeof(Disp) / sizeof(uchar) - 1 i++)
    {
        lcdWriteData(Disp[i]);
    }
    while (1)
        ;
}
