#ifndef _I2C_H_
#define _I2C_H_
/*AT24C02�����ļ�*/

void I2C_Start(); //��ʼ����

void I2C_Stop();  //��ֹ����

void I2C_SendByte(unsigned char Byte);  //����һ���ֽ�

unsigned char I2C_ReceiveByte();  //����һ���ֽ�

void I2C_SendACK(unsigned char ACK);  //����Ӧ��

unsigned char I2C_ReceiveACK();  //����Ӧ��
#end