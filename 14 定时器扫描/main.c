#include <REGX52.H>
#include "Delay.h"
#include "Key.h"
#include "MatrixKey.h"
#include "Nixie.h"
#include "Timer.h"
#include "AT24C02.h"
unsigned char i;   //�������ʾ
unsigned char WriteNum,index;   //������
unsigned char keyNum;  
unsigned char RunFlag;      //��ͣ
unsigned char Min,Sec,Msel;   //ʱ�� 
void ShowTime();   //��ʾʱ��
void UpdateTime();    //����ʱ��
void main()
{
	Timer0_Init();
	while(1)
	{
		keyNum=Key();
		if(keyNum)  //����а�������
		{
			if(keyNum==1){	RunFlag=!RunFlag;	}   //1��ͣ
			if(keyNum==2){	Min=0;Sec=0;Msel=0;RunFlag=0;}   //2����
			if(keyNum==3 && RunFlag==0)   //3����
			{	
				AT24C02_WriteByte(3,Min);
				Delay(5);
				AT24C02_WriteByte(4,Sec);
				Delay(5);
				AT24C02_WriteByte(5,Msel);
				Delay(5);
			}
			} 
			if(keyNum==4 && RunFlag==0)   //4����
			{	
				Min=AT24C02_ReadByte(3);
				Sec=AT24C02_ReadByte(4);
				Msel=AT24C02_ReadByte(5);
			}  
		ShowTime();   //��ʾʱ��
	}
}
//ʱ���ʱ��
void Timer0_Routine() interrupt 1  //INT0->T0->INT1->T1->UART
{
	static unsigned int count1=0,count2=0,count3=0;
	TH0=(65535-921)/256;
	TL0=(65535-921)/256;
	
	if(count1++==10)  //ɨ�谴��
	{
		count1=0;
		KeyTime();
	}
	if(count2++==2)    //ɨ�������
	{
		count2=0;
		Nixie_Time();  
		//Ĭ��ɨ����ʾ�գ�ͨ��������ʾ����ʾ����
	}
	if(count3++>=10)
	{
		count3=0;
		UpdateTime();
	}
	
}

void ShowTime()   //��ʾʱ��
{
		//����ɨ����ʾ
		Nixie_SetScan(1,Min/10);
		Nixie_SetScan(2,Min%10);
		Nixie_SetScan(3,12);
		Nixie_SetScan(4,Sec/10);
		Nixie_SetScan(5,Sec%10);
		Nixie_SetScan(6,12);
		Nixie_SetScan(7,Msel/10);
		Nixie_SetScan(8,Msel%10);
}	

void UpdateTime()    //����ʱ��
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
//void save_time()    //����ʱ�����ʾʱ�亯��
//{
//		if(t1==2)  //��2���浱ǰ��¼
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
//		if(t1==3 && stop==0)   //��ͣ��3��ʾ���4����¼
//		{
//			while(t1!=4)
//			{
//				 t1=Key(); //��ѭ���л�ȡ�ź�
//				 mtest=MatrixKey();
//				 if(mtest>=1 && mtest<=4)
//					 i=mtest-1;
//	       Nixie(8,i);
//	       Nixie(index+2,10);  //С����
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

