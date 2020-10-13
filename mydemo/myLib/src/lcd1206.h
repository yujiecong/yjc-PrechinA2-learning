#ifndef _LCD1206_H
#define _LCD1206_H
#include"global.h"
#define LCD1602_DATAPINS P0
sbit LCD1602_E=P2^7;
sbit LCD1602_RW=P2^5;
sbit LCD1602_RS=P2^6;
/**********************************
函数声明
**********************************/
/*在51单片机12MHZ时钟下的延时函数*/
void lcd1602_Delay1ms(uint c);   //误差 0us
/*LCD1602写入8位命令子函数*/
void lcdWriteCom(uchar com);
/*LCD1602写入8位数据子函数*/	
void lcdWriteData(uchar dat)	;
/*LCD1602初始化子程序*/		
void lcdInit();						  

/*******************************************************************************
* 函 数 名         : Lcd1602_Delay1ms
* 函数功能		   : 延时函数，延时1ms
* 输    入         : c
* 输    出         : 无
* 说    名         : 该函数是在12MHZ晶振下，12分频单片机的延时。
*******************************************************************************/

void lcd1602_Delay1ms(uint c)   //误差 0us
{
    uchar a,b;
	for (; c>0; c--)
	{
		 for (b=199;b>0;b--)
		 {
		  	for(a=1;a>0;a--);
		 }      
	}
    	
}
/*******************************************************************************
* 函 数 名         : LcdWriteCom
* 函数功能		   : 向LCD写入一个字节的命令
* 输    入         : com
* 输    出         : 无
*******************************************************************************/
void lcdWriteCom(uchar com)	  //写入命令
{
	LCD1602_E = 0;     //使能
	LCD1602_RS = 0;	   //选择发送命令
	LCD1602_RW = 0;	   //选择写入
	
	LCD1602_DATAPINS = com;     //放入命令
	lcd1602_Delay1ms(1);		//等待数据稳定

	LCD1602_E = 1;	          //写入时序
	lcd1602_Delay1ms(5);	  //保持时间
	LCD1602_E = 0;
}

void lcdWriteData(uchar dat)			//写入数据
{
	LCD1602_E = 0;	//使能清零
	LCD1602_RS = 1;	//选择输入数据
	LCD1602_RW = 0;	//选择写入

	LCD1602_DATAPINS = dat; //写入数据
	lcd1602_Delay1ms(1);

	LCD1602_E = 1;   //写入时序
	lcd1602_Delay1ms(5);   //保持时间
	LCD1602_E = 0;
}
void lcdInit()						  //LCD初始化子程序
{
 	lcdWriteCom(0x38);  //开显示
	lcdWriteCom(0x0c);  //开显示不显示光标
	lcdWriteCom(0x06);  //写一个指针加1
	lcdWriteCom(0x01);  //清屏
	lcdWriteCom(0x80);  //设置数据指针起点
}
