/****************************************************************
**********************
ʵ���������س���󣬲��� K3 ����ʹ D1 ״̬ȡ��
����˵���� (�������ͼ�ɼ��������Զ�Ӧʵ��ġ�ʵ�������½�)
1����Ƭ��-->LED&��ͨ��ģ��
P20-->D1
2����Ƭ��-->��������ģ��
P32-->K3
ע�����
*****************************************************************
**********************/
#include "reg52.h"        //���ļ��ж����˵�Ƭ����һЩ���⹦�ܼĴ���
typedef unsigned int u16; //���������ͽ�����������
typedef unsigned char u8;
sbit k3 = P3 ^ 2;  //���尴�� K3
sbit led = P2 ^ 0; //���� P20 ���� led
/****************************************************************
***************
* �� �� �� : delay
* �������� : ��ʱ������i=1 ʱ����Լ��ʱ 10us
*****************************************************************
**************/
void delay(u16 i)
{
    while (i--)
        ;
}
/****************************************************************
***************
* �� �� �� : Int1Init()
* �������� : �����ⲿ�ж� 1
* �� �� : ��
* �� �� : ��
*****************************************************************
**************/
void Int0Init()
{
    //���� INT0
    IT0 = 1; //�����س�����ʽ���½��أ�
    EX0 = 1; //�� INT0 ���ж�������
    EA = 1;  //�����ж�
}
/****************************************************************
***************
* �� �� �� : main
* �������� : ������
* �� �� : ��
* �� �� : ��
*****************************************************************
**************/
void main()
{
    Int0Init(); // �����ⲿ�ж� 0
    while (1)
        ;
}
/****************************************************************
***************
* �� �� �� : Int0() interrupt 0
* �������� : �ⲿ�ж� 0 ���жϺ���
* �� �� : ��
* �� �� : ��
*****************************************************************
**************/
void Int0() interrupt 0 //�ⲿ�ж� 0 ���жϺ���
{
    delay(1000); //��ʱ����
    if (k3 == 0)
    {
        led = ~led;
    }
}