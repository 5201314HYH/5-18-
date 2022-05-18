
#include <REGX52.H>
#include "I2C.h"

//�ӻ���ַ��AT24C02�Ĺ̶���ַΪ1010�������õ�ַ����������Ϊ000
#define AT24C02_ADDRESS 0xA0   //R/W

void AT24C02_WriteByte(unsigned char WordAddress,Data)  //�ֽ�д
{
	I2C_Start(); //��ʼ����
	I2C_SendByte(AT24C02_ADDRESS);  //����AT24C02(�ӻ�)�ֵ�ַ
  I2C_ReceiveACK();      //����һ��Ӧ��
	I2C_SendByte(WordAddress);  //����һ���ֵ�ַ
  I2C_ReceiveACK();      //����һ��Ӧ��
	I2C_SendByte(Data);  //����һ������
  I2C_ReceiveACK();      //����һ��Ӧ��
	I2C_Stop(); //��ֹ����
}

////�������������WORD ADDRESS��������DATA
unsigned char AT24C02_ReadByte(unsigned char WordAddress)
{
	unsigned char Data;
	/* ���Ƕ������� */
	I2C_Start(); //��ʼ����
	I2C_SendByte(AT24C02_ADDRESS);  //����AT24C02(�ӻ�)�ֵ�ַ
  I2C_ReceiveACK();      //����һ��Ӧ��
	I2C_SendByte(WordAddress);  //�����ֵ�ַ
  I2C_ReceiveACK();      //����һ��Ӧ��
	
	/* �������� */
	I2C_Start(); //��ʼ����
	I2C_SendByte(AT24C02_ADDRESS|0x01);  //R/W,�������ģʽ 
  I2C_ReceiveACK();      //����һ��Ӧ��
	Data=I2C_ReceiveByte();  //����һ���ֽڣ�I2C_SDA=1������Ȩ�����ӻ������մӻ�������
	I2C_SendACK(1);//�������������ˣ����ͷ�Ӧ���ʾ���ջ��߷���һ֡���ݽ���,��0Ҳ����
	I2C_Stop(); //��ֹ����
	return Data;
}



