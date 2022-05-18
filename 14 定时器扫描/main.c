#include <REGX52.H>
#include "Delay.h"
#include "Key.h"
#include "MatrixKey.h"
#include "Nixie.h"
#include "Timer.h"
#include "AT24C02.h"
unsigned char i;   //数码管显示
unsigned char WriteNum,index;   //保存用
unsigned char keyNum;  
unsigned char RunFlag;      //暂停
unsigned char Min,Sec,Msel;   //时间 
void ShowTime();   //显示时间
void UpdateTime();    //更新时间
void main()
{
	Timer0_Init();
	while(1)
	{
		keyNum=Key();
		if(keyNum)  //如果有按键按下
		{
			if(keyNum==1){	RunFlag=!RunFlag;	}   //1暂停
			if(keyNum==2){	Min=0;Sec=0;Msel=0;RunFlag=0;}   //2归零
			if(keyNum==3 && RunFlag==0)   //3保存
			{	
				AT24C02_WriteByte(3,Min);
				Delay(5);
				AT24C02_WriteByte(4,Sec);
				Delay(5);
				AT24C02_WriteByte(5,Msel);
				Delay(5);
			}
			} 
			if(keyNum==4 && RunFlag==0)   //4读出
			{	
				Min=AT24C02_ReadByte(3);
				Sec=AT24C02_ReadByte(4);
				Msel=AT24C02_ReadByte(5);
			}  
		ShowTime();   //显示时间
	}
}
//时间计时用
void Timer0_Routine() interrupt 1  //INT0->T0->INT1->T1->UART
{
	static unsigned int count1=0,count2=0,count3=0;
	TH0=(65535-921)/256;
	TL0=(65535-921)/256;
	
	if(count1++==10)  //扫描按键
	{
		count1=0;
		KeyTime();
	}
	if(count2++==2)    //扫描数码管
	{
		count2=0;
		Nixie_Time();  
		//默认扫描显示空，通过更改显示来显示数字
	}
	if(count3++>=10)
	{
		count3=0;
		UpdateTime();
	}
	
}

void ShowTime()   //显示时间
{
		//更改扫描显示
		Nixie_SetScan(1,Min/10);
		Nixie_SetScan(2,Min%10);
		Nixie_SetScan(3,12);
		Nixie_SetScan(4,Sec/10);
		Nixie_SetScan(5,Sec%10);
		Nixie_SetScan(6,12);
		Nixie_SetScan(7,Msel/10);
		Nixie_SetScan(8,Msel%10);
}	

void UpdateTime()    //更新时间
{
	if(RunFlag)   
	{
		Msel++;
		if(Msel>=100)
		{
			Msel=0;
			Sec++;
			if(Sec>=60)
			{
				Sec=0;
				Min++;
				if(Min>=60)
				{
					Min=0;
				}
			}
		}
	}//RunFlag
}
//void save_time()    //保存时间和显示时间函数
//{
//		if(t1==2)  //按2保存当前记录
//		{
//			i=3;
//			do
//			{
//				i--;
//				mArr[i+1]=mArr[i];
//				sArr[i+1]=sArr[i];
//				msArr[i+1]=msArr[i];
//			}while(i);
//			i=0;
//			mArr[0]=m;
//			sArr[0]=s;
//			msArr[0]=ms;
//		}
//		if(t1==3 && stop==0)   //暂停后按3显示最近4条记录
//		{
//			while(t1!=4)
//			{
//				 t1=Key(); //在循环中获取信号
//				 mtest=MatrixKey();
//				 if(mtest>=1 && mtest<=4)
//					 i=mtest-1;
//	       Nixie(8,i);
//	       Nixie(index+2,10);  //小数点
//	       Nixie(index+0,10);
//	       
//	       Nixie(index+3,msArr[i]);
//	       Nixie(index+2,sArr[i]%10);
//	       Nixie(index+1,sArr[i]/10);
//	       Nixie(index+0,mArr[i]%10);
//	       Nixie(index-1,mArr[i]/10);
//			}
//		}
//}

