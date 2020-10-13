#ifndef _GLOBAL_H
#define _GLOBAL_H
#include "reg52.h"
#include <stdio.h>
#include <stdlib.h>
#include <intrins.h>
typedef unsigned int uint; //对数据类型进行声明定义
typedef unsigned char uchar;
// function statement
void delay(uint i);
void delayS();

void delay(uint us10)
{
	while (us10--)
		;
}
void delayS()
{
	delay(100 * 1000);
}
#endif
