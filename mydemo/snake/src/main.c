#include "snake.h"
#include "../lib/leddt.h"
void main()
{

    struct snakeNode *ccSnake;
    uchar i = 0;
    ccSnake = initSnake();
    ccSnake->x = 3;
    while (1)
    {
        ccSnake = initSnake();
        while (ccSnake != NULL)
        {
            digDisplay(i, ccSnake->x);
            ccSnake = ccSnake->nextBody;
            i++;
        }

        // digDisplay(1, 3);
        // ccSnake = initSnake();
        // for (i = 0; i < 8; i++)
        // {

        //     // ccSnake = ccSnake->nextBody;
        // }
        // for (i = 0; i < 8; i++)
        // {
        //     digDisplay(i, (&ccSnake)->x);
        // }

        // choice88Led(1, 1, 1);
    }
}
