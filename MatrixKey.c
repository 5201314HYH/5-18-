#include <REGX52.H>
#include "Delay.H"
unsigned char MkNum;

unsigned char MatrixKey()   //定时器扫描到后返回
{
	unsigned char temp;
	temp=MkNum;
	MkNum=0;
	return temp;
}
unsigned char MatrixKey_Private()  //定时器扫描私有函数
{
	unsigned char MK=0;
	
	//Delay(1);   //防止篡位
	
	P1=0x0f;
	if(P1!=0x0f)
	{
			P1=0x0f;
			switch(P1)   //检测是哪一列有按键按下;
			{
				case(0x07):MK=1;break;
				case(0x0b):MK=2;break;
				case(0x0d):MK=3;break;
				case(0x0e):MK=4;break;
			}
			P1=0xf0;
			switch(P1)   //检测是哪一行有按键按下;       
			{
				case(0x70):MK+=0;break;
				case(0xb0):MK+=4;break;
				case(0xd0):MK+=8;break;
				case(0xe0):MK+=12;break;
			}
	}
	
	return MK;
}



void MK_TimerScan()
{
	static unsigned char LastState=0,NowState=0; //上一个状态和现在状态
	LastState=NowState;
	NowState=MatrixKey_Private();
	
	if(LastState && NowState==0)  //如果上一个瞬间有按下，现在松手
	{
		MkNum=LastState;
	}
}

