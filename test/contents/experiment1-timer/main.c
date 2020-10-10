#include <REG52.H>
//oscillation period
#define OP 1 / 11.0592
#define NUM P0 //数码管的数字
typedef unsigned char uchar;
typedef unsigned int uint;
sbit k4 = P3 ^ 2; //红色按键k3
sbit k5 = P3 ^ 3; //红色按键k4

sbit beep = P1 ^ 5; //蜂鸣器
sbit LSA = P2 ^ 2;
sbit LSB = P2 ^ 3;
sbit LSC = P2 ^ 4;


bit stop = 1;
unsigned char code numTable[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d,
								 0x07, 0x7f, 0x6f};
uchar timeNum[6] = {0};
uchar hour = 0, sec = 0, min = 0, count = 0;
uchar time_count;

void delay(uchar i);
void choice(uchar n);
void display();
int computeTH0(uint us);
int computeTL0(uint us);
void timerInit();
void startTimer();
void stopTimer();
void keyListen();

void delay(uchar i)
{
	int j, k;
	for (j = i; j > 0; j--)
		for (k = 125; k > 0; k--)
			;
}
void choice(uchar n)
{
	// 0011 1000 第1个
	// 0011 0000 第2个
	// 0010 1000 3

	//选择P2 ^ 4~7
	switch (n) //位选，选择点亮的数码管，
	{
	case (0):
		LSA = 1;
		LSB = 1;
		LSC = 1;
		break; //显示第0位
	case (1):
		LSA = 0;
		LSB = 1;
		LSC = 1;
		break; //显示第1位
	case (2):
		LSA = 1;
		LSB = 0;
		LSC = 1;
		break; //显示第2位
	case (3):
		LSA = 0;
		LSB = 0;
		LSC = 1;
		break; //显示第3位
	case (4):
		LSA = 1;
		LSB = 1;
		LSC = 0;
		break; //显示第4位
	case (5):
		LSA = 0;
		LSB = 1;
		LSC = 0;
		break; //显示第5位
	case (6):
		LSA = 1;
		LSB = 0;
		LSC = 0;
		break; //显示第6位
	case (7):
		LSA = 0;
		LSB = 0;
		LSC = 0;
		break; //显示第7位
	}
}
void display()
{
	int i;

	for (i = 2; i < 8; i++)
	{
		choice(i);
		NUM = numTable[timeNum[i - 4]]; //numTable[timeNum[8 - i-1]]
		delay(5);
		P0 = 0x00; //消隐
	}
}
int computeTH0(uint us)
{
	//
	return (65536 - ((int)(us / (OP * 12)))) / 256;
}
int computeTL0(uint us)
{
	return (65536 - ((int)(us / (OP * 12)))) % 256;
}
void timerInit()
{
	TMOD = 0x01; //定时器0选择工作方式1
	//初始值设置公式
	/*
    设要设定的秒数为t(单位是μs)这里以50ms为例就是50000μs
    先计算计数值=t/(1/11.0592*12)
    所以初始值TH0+TL0=65536-t
    但是由于是两个八位的寄存器，所以还要做相应的处理
    */
	TH0 = computeTH0(50000);
	TL0 = computeTL0(50000);
}
void startTimer()
{
	EA = 1;	 //打开总中断
	ET0 = 1; //打开定时器0中断
	TR0 = 1; //启动定时器0
}
void stopTimer()
{
	EA = 0;
	ET0 = 0;
	TR0 = 0;
}
void keyListen()
{
	while (1)
	{
		if (k4 == 0) //判断是否有按下按键的信号
		{
			delay(10);	 //延时10ms 消抖
			if (k4 == 0) //再次判断按键是否被按下
			{
				while (k4 == 0)
					; //直到按键判断松开
				{
					if (stop)
						startTimer(); //打开定时器
					else
						stopTimer(); //关闭定时器
					stop = ~stop;
					beep = 1;
					P2 = 0xff; //流水灯搞起来
				}
			}
		}
		else if (k5 == 0) //判断是否有按下按键的信号
		{
			delay(10);	 //延时10ms 消抖
			if (k5 == 0) //再次判断按键是否被按下
			{
				while (k5 == 0)
					; //直到按键判断松开
				{
					stopTimer(); //关闭定时器
					stop = 1;
					beep = 1;
					P2 = 0xff;
					count = 0;
					time_count = 0;
					sec = 0; //计时清零
					min = 0;
					hour = 0;
				}
			}
		}

		//
		//

		if (stop)
		{
			count++;
			if (count == 100)
			{
				P2 = ~P2;
			}
		}
		else if (time_count == 20) //计数20次0.05秒为一秒
		{
			count = 0;
			time_count = 0;
			sec++;
			if (sec == 60)
			{
				sec = 0; //若到了60s，则归零
				min++;
			}
			if (min == 60)
			{
				hour++;
				min = 0; //若到了60min，则归零
			}
			if (hour == 24)
			{
				sec = 0;
				min = 0;
			}
			beep = 0;
			delay(10);
			beep = 1;
		}
		timeNum[0] = min / 10;
		timeNum[1] = min % 10;
		timeNum[2] = sec / 10;
		timeNum[3] = sec % 10;
		timeNum[4] = hour / 10;
		timeNum[5] = hour % 10;
		display(); //显示
	}
}
void main()
{
	//
	timerInit();
	keyListen();
}
void update() interrupt 1
{
	TH0 = computeTH0(50000);
	TL0 = computeTL0(50000);
	time_count++;
}
