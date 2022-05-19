#include <REGX52.H>
#include "Delay.H"
unsigned char MkNum;

unsigned char MatrixKey()   //��ʱ��ɨ�赽�󷵻�
{
	unsigned char temp;
	temp=MkNum;
	MkNum=0;
	return temp;
}
unsigned char MatrixKey_Private()  //��ʱ��ɨ��˽�к���
{
	unsigned char MK=0;
	
	//Delay(1);   //��ֹ��λ
	
	P1=0x0f;
	if(P1!=0x0f)
	{
			P1=0x0f;
			switch(P1)   //�������һ���а�������;
			{
				case(0x07):MK=1;break;
				case(0x0b):MK=2;break;
				case(0x0d):MK=3;break;
				case(0x0e):MK=4;break;
			}
			P1=0xf0;
			switch(P1)   //�������һ���а�������;       
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
	static unsigned char LastState=0,NowState=0; //��һ��״̬������״̬
	LastState=NowState;
	NowState=MatrixKey_Private();
	
	if(LastState && NowState==0)  //�����һ��˲���а��£���������
	{
		MkNum=LastState;
	}
}

