#ifndef _NIXIE_H_
#define _NIXIE_H_

void Nixie(unsigned char num,number);//@11.0592MHz @0-65535

void Nixie_glint(unsigned char num);

//ɨ����ʾ0,
void Nixie_Time();   //��ʱ��ɨ�������
//����ɨ����ʾ
void Nixie_SetScan(unsigned char i,num);   //��������
#endif