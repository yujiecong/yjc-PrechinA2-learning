#ifndef _SNAKE_H
#define _SNAKE_H
#include "../lib/global.h"
#include "../lib/74hc595.h"
#include "../lib/keyboard.h"
#include "../lib/infrared.h"
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
// - 关机键-0x45
// - MODE-0x46
// - 静音键-0x47
// - 暂停/播放-0x44
// - 往前退-0x40
// - 往后退-0x43
// - EQ-0x07
// - vol↓-0x15
// - vol↑-0x09
// - 0-0x16
// - 1-0x0c
// - 2-0x18
// - 3-0x5e
// - 4-0x08
// - 5-0x1c
// - 6-0x5a
// - 7-0x42
// - 8-0x52
// - 9-0x4a
void ctrlSnake()
{
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
    irInitInter0();
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

void irl() interrupt 0
{
    uchar j, k;
    uint err;
    uchar Time = 0;

    delay(700);    //7ms
    if (IRIN == 0) //确认是否真的接收到正确的信号
    {

        err = 1000; //1000*10us=10ms,超过说明接收到错误的信号
        /*当两个条件都为真是循环，如果有一个条件为假的时候跳出循环，免得程序出错的时
		侯，程序死在这里*/
        while ((IRIN == 0) && (err > 0)) //等待前面9ms的低电平过去
        {
            delay(1);
            err--;
        }
        if (IRIN == 1) //如果正确等到9ms低电平
        {
            err = 500;
            while ((IRIN == 1) && (err > 0)) //等待4.5ms的起始高电平过去
            {
                delay(1);
                err--;
            }
            for (k = 0; k < 4; k++) //共有4组数据
            {
                for (j = 0; j < 8; j++) //接收一组数据
                {

                    err = 60;
                    while ((IRIN == 0) && (err > 0)) //等待信号前面的560us低电平过去
                    {
                        delay(1);
                        err--;
                    }
                    err = 500;
                    while ((IRIN == 1) && (err > 0)) //计算高电平的时间长度。
                    {
                        delay(10); //0.1ms
                        Time++;
                        err--;
                        if (Time > 30)
                        {
                            return;
                        }
                    }
                    IrValue[k] >>= 1; //k表示第几组数据
                    if (Time >= 8)    //如果高电平出现大于565us，那么是1
                    {
                        IrValue[k] |= 0x80;
                    }
                    Time = 0; //用完时间要重新赋值
                }
            }
        }
        if (IrValue[2] != ~IrValue[3])
        {
            return;
        }
        switch (IrValue[2])
        {
        case 0x08:
            left();
            break;
        case 0x5a:
            right();
            break;
        case 0x18:
            up();
            break;
        case 0x52:
            down();
            break;
        default:
            break;
        }
    }
}
#endif
