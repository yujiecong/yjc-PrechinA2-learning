# 嗯。终于可以控制这个sb马达了
这个接线我自己摸索出来了，即通过一个正极+和一个上面的A引脚接在一起即可。
## 如何使用?
看电路图可以知道控制引脚在P1^0~5除了P1^4没有外。总共这四个脚可以控制马达。。  
刚好四个轮子啊狗头
```
sbit moto=P1^0;	  	 
```
主逻辑也很简单  

```
	u8 i;
	moto=0;			//关闭电机
	for(i=0;i<100;i++)	  //循环100次，也就是大约5S
	{
		moto=1;			 //开启电机
		delay(5000);	//大约延时50ms
	}
	moto=0;			//关闭电机
```

就可以看到你的马达转起来了

