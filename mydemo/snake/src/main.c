#include "snake.h"
#include "../lib/leddt.h"
#include "../lib/interruption.h"
#include "../lib/global.h"
#include "../lib/keyboard.h"
void main()
{

    initSnake();
    //设置 INT0
    while (1)
    {
        /* code */
        drawSnake();
        moveSnake();
        ctrlSnakeUp();
    }
}
