#include <REGX52.H>
#include "Delay.h"
//10显示小数点,11显示空，12横杠
unsigned char code number[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x80,0x00,0x40};
void Nixie(unsigned char num,i)
{
	P0=0x00;
	switch(num) 
	{
		case 1:P2_4=1,P2_3=1,P2_2=1;break;
		case 2:P2_4=1,P2_3=1,P2_2=0;break;
		case 3:P2_4=1,P2_3=0,P2_2=1;break;
		case 4:P2_4=1,P2_3=0,P2_2=0;break;
		case 5:P2_4=0,P2_3=1,P2_2=1;break;
		case 6:P2_4=0,P2_3=1,P2_2=0;break;
		case 7:P2_4=0,P2_3=0,P2_2=1;break;
		case 8:P2_4=0,P2_3=0,P2_2=0;break;		
	}
	/* 数码管控制总线：P0 */;
	P0=number[i];
}

unsigned char Nixie_Buf[9]={0,11,11,11,11,11,11,11,11};
void Nixie_SetScan(unsigned char i,num)  //更改扫描显示
{
	Nixie_Buf[i]=num;
}
void Nixie_Time()   //不断扫描8位0，需要显示的单独给值使其显示
{
	static unsigned char i=1;   //1-8不断扫描
	Nixie(i,Nixie_Buf[i]);
	i++;
	if(i>=9){	i=1;}
}
