#include <REGX52.H>


unsigned char Key_KeyNumber;

unsigned char Key(void)   //��������
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

//void KeyTime()  //��ʱ��ɨ�躯��
unsigned char KeyTime()  //��ʱ��ɨ�躯��
{
	static unsigned char NowState,LastState;
	static unsigned char temp;
	LastState=NowState;				//����״̬����
	NowState=Key_GetState();		//��ȡ��ǰ����״̬
	
	//����ϸ�״̬�а������£�����û���򷵻��ϸ�����ֵ
	if(LastState && NowState==0)
	{
		Key_KeyNumber=LastState;
		temp=LastState;
	}
	return temp;
}
