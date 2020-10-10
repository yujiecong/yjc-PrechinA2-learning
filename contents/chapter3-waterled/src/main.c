/**************************************************************************************
ʵ���������س����"LED&��ͨ��ģ��"��D1-D8������ˮ��Ч��
����˵���� ��Ƭ��-->LED&��ͨ��ģ��(�������ͼ�ɼ��������Զ�Ӧʵ��ġ�ʵ�������½�)
		   P00-->D1
		   P01-->D2	
		   ...
		   P07-->D8
ע�����																				  
***************************************************************************************/

#include "reg52.h"			 //���ļ��ж����˵�Ƭ����һЩ���⹦�ܼĴ���
#include<intrins.h>		//��ΪҪ�õ������ƺ��������Լ������ͷ�ļ�

typedef unsigned int u16;	  //���������ͽ�����������
typedef unsigned char u8;

#define led P2	   //��P2�ڶ���Ϊled ����Ϳ���ʹ��led����P2��

/*******************************************************************************
* �� �� ��         : delay
* ��������		   : ��ʱ������i=1ʱ����Լ��ʱ10us
*******************************************************************************/
void delay(u16 i)
{
	while(i--);	
}

/*******************************************************************************
* �� �� ��       : main
* ��������		 : ������
* ��    ��       : ��
* ��    ��    	 : ��
*******************************************************************************/
void main()
{
	u8 i;
	led=~0x01;
	delay(50000); //��Լ��ʱ450ms	
	while(1)
	{	
		for(i=0;i<8;i++)
		{
			P2=~(0x01<<i);	 //��1����iλ��Ȼ�󽫽����ֵ��P2��
			delay(50000); //��Լ��ʱ450ms
		}

		
/*		for(i=0;i<7;i++)	 //��led����һλ
		{
			led=_crol_(led,1);
			delay(50000); //��Լ��ʱ450ms	
		}
		for(i=0;i<7;i++)	//��led����һλ
		{
			led=_cror_(led,1);
			delay(50000); //��Լ��ʱ450ms	
		}
*/
	}		
}