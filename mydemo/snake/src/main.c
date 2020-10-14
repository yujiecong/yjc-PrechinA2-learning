#include "snake.h"
#include "../lib/leddt.h"
struct test
{
    uchar showdata;
};

void main()
{

    struct test *testPointer = (struct test *)malloc(sizeof(struct test));
    testPointer->showdata = 3;
    while (1)
    {
        digDisplay(0, testPointer->showdata);
        delay(1000);
        digDisplay(1, 3);
    }

    // struct snakeNode *ccSnake;
    // uchar i = 0;
    // ccSnake = initSnake();
    // ccSnake->x = 3;
    // while (1)
    // {
    //     ccSnake = initSnake();
    //     while (ccSnake != NULL)
    //     {
    //         digDisplay(i, ccSnake->x);
    //         ccSnake = ccSnake->nextBody;
    //         i++;
    //     }

    //     // digDisplay(1, 3);
    //     // ccSnake = initSnake();
    //     // for (i = 0; i < 8; i++)
    //     // {

    //     //     // ccSnake = ccSnake->nextBody;
    //     // }
    //     // for (i = 0; i < 8; i++)
    //     // {
    //     //     digDisplay(i, (&ccSnake)->x);
    //     // }

    //     // choice88Led(1, 1, 1);
    // }
}
