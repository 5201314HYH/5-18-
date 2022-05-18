#include <REGX52.H>
#include "Delay.h"
unsigned char MatrixKey()
{
	unsigned char MK=0;
	
	Delay(1);   //防止篡位
	P1=0xff;
	
	P1_3=0x0;   //选中	
	if(P1_7==0){	Delay(15);	while(P1_7==0);	Delay(15); MK=1;	}
	if(P1_6==0){	Delay(15);	while(P1_6==0);	Delay(15); MK=5;	}
	if(P1_5==0){	Delay(15);	while(P1_5==0);	Delay(15); MK=9;	}
	if(P1_4==0){	Delay(15);	while(P1_4==0);	Delay(15); MK=13;	}
	
	P1_2=0x0;   //选中	
	if(P1_7==0){	Delay(15);	while(P1_7==0);	Delay(15); MK=2;	}
	if(P1_6==0){	Delay(15);	while(P1_6==0);	Delay(15); MK=6;	}
	if(P1_5==0){	Delay(15);	while(P1_5==0);	Delay(15); MK=10;	}
	if(P1_4==0){	Delay(15);	while(P1_4==0);	Delay(15); MK=14;	}
	
	P1_1=0x0;   //选中	
	if(P1_7==0){	Delay(15);	while(P1_7==0);	Delay(15); MK=3;	}
	if(P1_6==0){	Delay(15);	while(P1_6==0);	Delay(15); MK=7;	}
	if(P1_5==0){	Delay(15);	while(P1_5==0);	Delay(15); MK=11;	}
	if(P1_4==0){	Delay(15);	while(P1_4==0);	Delay(15); MK=15;	}
	
	P1_0=0x0;   //选中	
	if(P1_7==0){	Delay(15);	while(P1_7==0);	Delay(15); MK=4;	}
	if(P1_6==0){	Delay(15);	while(P1_6==0);	Delay(15); MK=7;	}
	if(P1_5==0){	Delay(15);	while(P1_5==0);	Delay(15); MK=12;	}
	if(P1_4==0){	Delay(15);	while(P1_4==0);	Delay(15); MK=16;	}
	
	return MK;
}