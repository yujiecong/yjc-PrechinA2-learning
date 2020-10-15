#include <stdio.h>
#include <stdlib.h>

#define SNAKELENG 3
typedef unsigned int uint; //对数据类型进行声明定义
typedef unsigned char uchar;
//
struct snakeNode
{
    uchar x, y;
    struct snakeNode *nextBody;
};
//
struct snakeNode *initSnake();
void printSnake(struct snakeNode *head);
void drawSnake(struct snakeNode *s);
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

void drawSnake(struct snakeNode *s)
{

    while (s != NULL)
    {
        //choice88Led(s->y, s->x, 1);

        s = s->nextBody;
    }
}
void printSnake(struct snakeNode *s)
{
    while (s != NULL)
    {
        printf("(x,y)=(%d,%d)\n", s->x, s->y);
        s = s->nextBody;
    }
}
int main()
{

    printf("%d", -61 % 3);
}
