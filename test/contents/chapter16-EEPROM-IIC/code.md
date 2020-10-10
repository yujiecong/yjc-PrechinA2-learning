# 代码解析
如果我们想控制这个存储器，当然用按键是比较合适的，即按一下存一下数据，再按别的读取一下数据，听起来就真不错！  
看起来会像这样
```
void Keypros()
{
	if(k1==0)
	{
		delay(1000);  //消抖处理
		if(k1==0)
		{
			At24c02Write(1,num);   //在地址1内写入数据num
		}
		while(!k1);
	}
	if(k2==0)
	{
		delay(1000);  //消抖处理
		if(k2==0)
		{
			num=At24c02Read(1);	  //读取EEPROM地址1内的数据保存在num中
		}
		while(!k2);
	}
	if(k3==0)
	{
		delay(100);  //消抖处理
		if(k3==0)
		{
			num++;	   //数据加1
			if(num>255)num=0;
		}
		while(!k3);
	}
	if(k4==0)
	{
		delay(1000);  //消抖处理
		if(k4==0)
		{
			num=0;		 //数据清零
		}
		while(!k4);
	}		
}
```
接下来想跟at24c02通信，就先写一个这样的函数
```
void At24c02Write(unsigned char addr,unsigned char dat)
{
	I2cStart();
	I2cSendByte(0xa0);//发送写器件地址
	I2cSendByte(addr);//发送要写入内存地址
	I2cSendByte(dat);	//发送数据
	I2cStop();
}
```
这里的解析刚刚的[README.md](README.md)有提到.例如对于这句代码
```
I2cStart();
```
> SCL线为高电平期间，SDA线由高电平向低电平的变化表示起始信号；
```
void I2cStart()
{
	SDA=1;
	Delay10us();
	SCL=1;
	Delay10us();//建立时间是SDA保持时间>4.7us
	SDA=0;
	Delay10us();//保持时间是>4us
	SCL=0;			
	Delay10us();		
}
```
然后对于这一句代码
```
I2cSendByte(0xa0);//发送写器件地址
```
有
> 在起始信号后必须传送一个从机的地址（7位），第8位是数据的传送方向位（R/T），用“0”表示主机发送数据（T），“1”表示主机接收数据（R）。
> 写入过程 AT24C系列E2PROM芯片地址的固定部分为1010，A2、A1、A0引脚接高、低电平后得到确定的3位编码。形成的7位编码即为该器件的地址码。

这里的at24c02已经固定了她的硬件地址，即是1010 000  
还有一位叫R/T位，用于控制读写，如果是写器件那么就是0xa0   

然后到内存地址，就是代表at24c02的3个地址，即3个存储空间，总共有3个，1，2,3嘛。A0,A1,A2
所以要
```
I2cSendByte(addr);//发送要写入内存地址
```
> 每一个字节必须保证是8位长度。数据传送时，先传送最高位（MSB），每一个被传送的字节后面都必须跟随一位应答位（即一帧共有9位）。

那么这个就是I2Csendbyte的原型了.
```
unsigned char I2cSendByte(unsigned char dat)
{
	unsigned char a=0,b=0;//最大255，一个机器周期为1us，最大延时255us。		
	for(a=0;a<8;a++)//要发送8位，从最高位开始
	{
		SDA=dat>>7;	 //起始信号之后SCL=0，所以可以直接改变SDA信号
		dat=dat<<1;
		Delay10us();
		SCL=1;
		Delay10us();//建立时间>4.7us
		SCL=0;
		Delay10us();//时间大于4us		
	}
	SDA=1;
	Delay10us();
	SCL=1;
	while(SDA)//等待应答，也就是等待从设备把SDA拉低
	{
		b++;
		if(b>200)	 //如果超过2000us没有应答发送失败，或者为非应答，表示接收结束
		{
			SCL=0;
			Delay10us();
			return 0;
		}
	}
	SCL=0;
	Delay10us();
 	return 1;		
}
```

__总体来说这种传输协议熟悉后还是比较简单的(仅限看懂代码)，对于我这种刚刚正式接触的人来说，哈哈。__


