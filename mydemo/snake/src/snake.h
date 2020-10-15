#ifndef _SNAKE_H
#define _SNAKE_H
#include "../lib/global.h"
#include "../lib/74hc595.h"
#include "../lib/keyboard.h"

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
struct pos
{
    char sy, sx;
};
//
uchar SNAKELENG = 3;
uchar map[8][8] = {0}; //记录snake坐标数据
struct pos snakePos[8] = {{0, 2}, {0, 1}, {0, 0}};
// struct pos snakePos[3] = {{2, 0}, {1, 0}, {0, 0}};
uchar direction = LEFT;
uchar lastDirection = LEFT;
uchar turnFlag = 0;
uchar vertical = 0;
uchar horizontal = 1;
uchar food = 0;
//蛇神位置

//
void initSnake();
void draw();
void ctrlSnake();
void up();
void down();
void left();
void right();
void createFood();
//
void createFood()
{
    uchar i, j;

    i = rand() % 8;
    j = rand() % 8;
    if (map[i][j] != 1)
    {
        map[i][j] = 2;
        food = 1;
    }
    else
    {
        createFood();
    }
}
void up()
{
    lastDirection = direction;
    if (lastDirection != DOWN)
    {

        vertical = 1;
        horizontal = 0;
        turnFlag = 1;
        direction = UP;
    }
}
void down()
{
    lastDirection = direction;
    if (lastDirection != UP)
    {

        vertical = -1;
        horizontal = 0;
        turnFlag = 1;
        direction = DOWN;
    }
}
void left()

{
    lastDirection = direction;
    if (lastDirection != RIGHT)
    {

        vertical = 0;
        horizontal = 1;
        turnFlag = 1;

        direction = LEFT;
    }
}

void right()
{
    lastDirection = direction;
    if (lastDirection != LEFT)
    {

        vertical = 0;
        horizontal = -1;
        turnFlag = 1;
        direction = RIGHT;
    }
}

void ctrlSnake()
{
    keyListen(up, 1);
    keyListen(down, 2);
    keyListen(left, 3);
    keyListen(right, 4);
}
void moveSnake()
{
    //将蛇身全部移动
    //TODO
    //待优化
    char i, j;
    if (turnFlag)
    {
        for (j = 0; j < SNAKELENG - 1; j++)
        {
            for (i = 0; i < SNAKELENG; i++)
            {

                if ((lastDirection == LEFT || lastDirection == RIGHT) && (direction == UP || direction == DOWN))
                {
                    if (map[snakePos[0].sx] != map[snakePos[i].sx])
                    {
                        if (lastDirection == LEFT)
                        {
                            snakePos[i].sx += 1;
                        }
                        else
                        {
                            snakePos[i].sx -= 1;
                        }
                    }
                    else
                    {
                        snakePos[i].sy += vertical;
                    }
                }
                else if ((lastDirection == UP || lastDirection == DOWN) && (direction == LEFT || direction == RIGHT))
                {
                    if (map[snakePos[0].sy] != map[snakePos[i].sy])
                    {
                        if (lastDirection == UP)
                            snakePos[i].sy += 1;
                        else
                        {
                            snakePos[i].sy += -1;
                        }
                    }
                    else
                    {
                        snakePos[i].sx += horizontal;
                    }
                }

                if (snakePos[i].sx % 8 == 0)
                {
                    snakePos[i].sx = 0;
                }
                if (vertical == -1)
                {
                    if (snakePos[i].sy < 0)
                    {
                        snakePos[i].sy += 8;
                    }
                }
                else if (vertical == 1)
                {
                    if (snakePos[i].sy % 8 == 0)
                        snakePos[i].sy = 0;
                    /* code */
                }

                if (i == 0)
                {

                    map[snakePos[SNAKELENG - 1].sy][snakePos[SNAKELENG - 1].sx] = 0;

                    if (map[snakePos[i].sy][snakePos[i].sx] == 2)
                    {
                        map[snakePos[0].sy][snakePos[0].sx] = 1;
                        snakePos[SNAKELENG].sy = snakePos[SNAKELENG - 1].sy -= vertical;
                        snakePos[SNAKELENG].sx = snakePos[SNAKELENG - 1].sx -= horizontal;
                        SNAKELENG += 1;
                        createFood();
                    }
                    else
                    {
                        map[snakePos[i].sy][snakePos[i].sx] = 1;
                    }
                }
                draw();

                delay(5000);
            }
        }
        turnFlag = 0;
    }

    map[snakePos[SNAKELENG - 1].sy][snakePos[SNAKELENG - 1].sx] = 0;

    for (i = SNAKELENG - 1; i >= 0; i--)
    {
        snakePos[i].sy += vertical;
        snakePos[i].sx += horizontal;
        if (snakePos[i].sx % 8 == 0)
        {
            snakePos[i].sx = 0;
        }
        if (vertical == -1)
        {
            if (snakePos[i].sy < 0)
            {
                snakePos[i].sy += 8;
            }
        }
        else if (vertical == 1)
        {
            if (snakePos[i].sy % 8 == 0)
                snakePos[i].sy = 0;
            /* code */
        }
    }
    if (map[snakePos[0].sy][snakePos[0].sx] == 2)
    {
        map[snakePos[0].sy][snakePos[0].sx] = 1;

        snakePos[SNAKELENG].sy = snakePos[SNAKELENG - 1].sy -= vertical;
        snakePos[SNAKELENG].sx = snakePos[SNAKELENG - 1].sx -= horizontal;
        SNAKELENG += 1;
        createFood();
    }
    else
        map[snakePos[0].sy][snakePos[0].sx] = 1;

    draw();

    delay(5000);
}

void initSnake()
{
    uchar i, j;
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            map[i][j] = 0;
        }
    }

    for (i = 0; i < SNAKELENG; i++)
    {
        map[snakePos[i].sy][snakePos[i].sx] = 1;
    }
}

void draw()
{
    uchar i, j;
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {

            if (map[i][j] == 1)
            {
                choice88Led(i, j, 1);
            }
            else if (map[i][j] == 2)
            {
                choice88Led(i, j, 1);
            }
        }
    }
}

// void ctrlDirection() interrupt 0
// {
//     if (k1 == 0)
//     {
//         delay(100);
//         if (k1 == 0)
//         {
//         }
//     }
//     else if (k2 == 0)
//     {
//         delay(100);
//         if (k2 == 0)
//         {
//         }
//     }
//     else if (k3 == 0)
//     {
//         delay(100);
//         if (k3 == 0)
//     }
// }
// else if (k4 == 0)
// {
//     delay(100);
//     if (k4 == 0)
//     {
//     }
// }
#endif
