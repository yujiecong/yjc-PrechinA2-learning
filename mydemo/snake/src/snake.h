#ifndef _SNAKE_H
#define _SNAKE_H
#include "../lib/global.h"
#include "../lib/interruption.h"
#include "../lib/74hc595.h"
#include "../lib/keyboard.h"
#define SNAKELENG 3
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
struct pos
{
    uchar sy, sx;
};
//
uchar map[8][8] = {0}; //记录snake坐标数据
struct pos snakePos[3] = {{0, 0}, {0, 1}, {0, 2}};
uchar direction = LEFT;
static uint interruptionCount = 0;
//蛇神位置

//
void initSnake();
void printSnake(struct snakeNode *head);
void drawSnake();
void listenCrtl();
void ctrlSnakeUp();
void up();
//
void up()
{
    direction = UP;
}
void listenCrtl()
{
    ctrlSnakeUp();
}
void ctrlSnakeUp()
{
    interruptionCount = 0;
    keyListen(up, 1);
}
void moveSnake()
{
    uchar i;
    switch (direction)
    {
    case UP:
        map[snakePos[0].sy][snakePos[0].sx] = 0;
        for (i = 0; i < SNAKELENG; i++)
        {

            snakePos[i].sy += 1;
            if (snakePos[i].sx % 8 == 0)
            {
                snakePos[i].sx = 0;
            }
            if (snakePos[i].sy % 8 == 0)
            {
                snakePos[i].sy = 0;
            }
            map[snakePos[i].sy][snakePos[i].sx] = 1;
        }
        break;
    case LEFT:
        map[snakePos[0].sy][snakePos[0].sx] = 0;
        for (i = 0; i < SNAKELENG; i++)
        {

            snakePos[i].sx += 1;
            if (snakePos[i].sx % 8 == 0)
            {
                snakePos[i].sx = 0;
            }
            if (snakePos[i].sy % 8 == 0)
            {
                snakePos[i].sy = 0;
            }
            map[snakePos[i].sy][snakePos[i].sx] = 1;
        }
        break;
    case RIGHT:
        map[snakePos[0].sy][snakePos[0].sx] = 0;
        for (i = 0; i < SNAKELENG; i++)
        {

            snakePos[i].sx -= 1;
            if (snakePos[i].sx % 8 == 0)
            {
                snakePos[i].sx = 0;
            }
            if (snakePos[i].sy % 8 == 0)
            {
                snakePos[i].sy = 0;
            }
            map[snakePos[i].sy][snakePos[i].sx] = 1;
        }
        break;
    case DOWN:
        map[snakePos[0].sy][snakePos[0].sx] = 0;
        for (i = 0; i < SNAKELENG; i++)
        {

            snakePos[i].sy -= 1;
            if (snakePos[i].sx % 8 == 0)
            {
                snakePos[i].sx = 0;
            }
            if (snakePos[i].sy % 8 == 0)
            {
                snakePos[i].sy = 0;
            }
            map[snakePos[i].sy][snakePos[i].sx] = 1;
        }
        break;
    default:
        break;
    }

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
    int0InitInter0();

    for (i = 0; i < SNAKELENG; i++)
    {
        map[snakePos[i].sy][snakePos[i].sx] = 1;
    }
}

void drawSnake()
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
        }
    }
}

#endif
