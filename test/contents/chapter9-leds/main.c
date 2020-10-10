/**************************************************************************************
实验现象：下载程序后，LED点阵左上角第一个点的LED被点亮果
		  
接线说明： (具体接线图可见开发攻略对应实验的“实验现象”章节)
	
注意事项：																				

  
***************************************************************************************/

#include "reg51.h"			 //此文件中定义了单片机的一些特殊功能寄存器
#include "intrins.h"

typedef unsigned int u16;	  //对数据类型进行声明定义
typedef unsigned char u8;

//--定义使用的IO口--//
sbit SRCLK=P3^6;
sbit RCLK=P3^5;
sbit SER=P3^4;
sbit LED=P0^7;

/*******************************************************************************
* 函 数 名         : Hc595SendByte(u8 dat1,u8 dat2)
* 函数功能		   : 通过595发送2个字节的数据
* 输    入         : dat1：第2个595输出数值
*                  * dat2: 第1个595输出数值
* 输    出         : 无
*******************************************************************************/
void Hc595SendByte(u8 dat1,u8 dat2)
{
	u8 a;

	SRCLK = 1;
	RCLK = 1;

	for(a=0;a<8;a++)		 //发送8位数
	{
		SER = dat1 >> 7;		 //从最高位开始发送
		dat1 <<= 1;

		SRCLK = 0;			 //发送时序
		_nop_();
		_nop_();
		SRCLK = 1;	
	}

	for(a=0;a<8;a++)		 //发送8位数
	{
		SER = dat2 >> 7;		 //从最高位开始发送
		dat2 <<= 1;

		SRCLK = 0;			 //发送时序
		_nop_();
		_nop_();
		SRCLK = 1;	
	}

	RCLK = 0;
	_nop_();
	_nop_();
	RCLK = 1;
}


/*******************************************************************************
* 函 数 名       : main
* 函数功能		 : 主函数
* 输    入       : 无
* 输    出    	 : 无
*******************************************************************************/
void main()
{	LED=0;  //使第一列为低电平。
	
	while(1)
	{
	   Hc595SendByte(0xfe,0x01);
	}		
}
