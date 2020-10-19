#include "snake.h"
#include "../lib/global.h"
#include "../lib/keyboard.h"

void main()
{

    initSnake();
    //设置 INT0
    createFood();
    while (1)
    {
        /* code */
        ctrlSnake();
        moveSnake();
    }
}
