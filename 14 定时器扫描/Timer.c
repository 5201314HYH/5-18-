#include <REGX52.H>

void Timer0_Init()  //1ms
{
	TMOD &=0xF0;
	TMOD |=0x01;
	
	TH0=(65535-921)/256;
	TL0=(65535-921)/256;
	
	TF0=0;
	EA=1;
	ET0=1;  //中断开
	TR0=1;  
	PT0=0;  //低优先级
}
void Timer1_Init()  //1ms
{
	TMOD &=0x0F;
	TMOD |=0x10;
	
	TH1=(65535-921)/256;
	TL1=(65535-921)/256;
	
	TF1=0;
	EA=1;
	ET1=1;  //中断开
	TR1=1;  
	PT1=0;  //低优先级
}
