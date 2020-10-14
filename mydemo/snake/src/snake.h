#ifndef _SNAKE_H
#define _SNAKE_H
#include "../lib/global.h"

#include "../lib/74hc595.h"
#define SNAKELENG 3
//

struct snakeNode
{
    uchar x, y;
    struct snakeNode *nextBody;
};
//
struct snakeNode *initSnake();
void printSnake(struct snakeNode *head);
void drawSnake(struct snakeNode s);
//

struct snakeNode *initSnake()
{
    struct snakeNode *snakeHead = (struct snakeNode *)malloc(sizeof(struct snakeNode));
    struct snakeNode *snakeTail = (struct snakeNode *)malloc(sizeof(struct snakeNode));
    uchar i;
    //if fail 。。。
    snakeTail->x = 0;
    snakeTail->y = 0;
    snakeTail->nextBody = NULL;

    //头插法
    for (i = 1; i < SNAKELENG; i++)
    {
        snakeHead = (struct snakeNode *)malloc(sizeof(struct snakeNode));
        snakeHead->nextBody = snakeTail;
        snakeHead->x = i;
        snakeHead->y = 0;
        snakeTail = snakeHead;
    }
    //free
    return snakeTail;
}

void drawSnake(struct snakeNode s)
{
    uchar i;
    for (i = 0; i < 3; i++)
    {
        choice88Led(s.y, s.x, 1);
        // struct snakeNode *t = s.nextBody;
    }
    // while (s != NULL)
    // {
    // }
}

#endif
