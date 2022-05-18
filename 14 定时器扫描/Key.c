#include <REGX52.H>


unsigned char Key_KeyNumber;

unsigned char Key(void)   //主函数用
{
	unsigned char temp=0;
	temp=Key_KeyNumber;
	Key_KeyNumber=0;
	return temp;
}

unsigned char Key_GetState()
{
	unsigned char KeyNumber=0;
	
	if(P3_1==0){KeyNumber=1;}
	else if(P3_0==0){KeyNumber=2;}
	else if(P3_2==0){KeyNumber=3;}
	else if(P3_3==0){KeyNumber=4;}
	
	return KeyNumber;
}

//void KeyTime()  //定时器扫描函数
unsigned char KeyTime()  //定时器扫描函数
{
	static unsigned char NowState,LastState;
	static unsigned char temp;
	LastState=NowState;				//按键状态更新
	NowState=Key_GetState();		//获取当前按键状态
	
	//如果上个状态有按键按下，现在没有则返回上个按键值
	if(LastState && NowState==0)
	{
		Key_KeyNumber=LastState;
		temp=LastState;
	}
	return temp;
}
