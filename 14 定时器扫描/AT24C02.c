
#include <REGX52.H>
#include "I2C.h"

//从机地址：AT24C02的固定地址为1010，可配置地址本开发板上为000
#define AT24C02_ADDRESS 0xA0   //R/W

void AT24C02_WriteByte(unsigned char WordAddress,Data)  //字节写
{
	I2C_Start(); //起始配置
	I2C_SendByte(AT24C02_ADDRESS);  //发送AT24C02(从机)字地址
  I2C_ReceiveACK();      //接收一个应答
	I2C_SendByte(WordAddress);  //发送一个字地址
  I2C_ReceiveACK();      //接收一个应答
	I2C_SendByte(Data);  //发送一个数据
  I2C_ReceiveACK();      //接收一个应答
	I2C_Stop(); //终止配置
}

////随机读：读出在WORD ADDRESS处的数据DATA
unsigned char AT24C02_ReadByte(unsigned char WordAddress)
{
	unsigned char Data;
	/* 在那读出数据 */
	I2C_Start(); //起始配置
	I2C_SendByte(AT24C02_ADDRESS);  //发送AT24C02(从机)字地址
  I2C_ReceiveACK();      //接收一个应答
	I2C_SendByte(WordAddress);  //发送字地址
  I2C_ReceiveACK();      //接收一个应答
	
	/* 读出数据 */
	I2C_Start(); //起始配置
	I2C_SendByte(AT24C02_ADDRESS|0x01);  //R/W,进入接收模式 
  I2C_ReceiveACK();      //接收一个应答
	Data=I2C_ReceiveByte();  //接收一个字节，I2C_SDA=1将控制权交给从机，接收从机的数据
	I2C_SendACK(1);//主机读到数据了，发送非应答表示接收或者发送一帧数据结束,发0也可以
	I2C_Stop(); //终止配置
	return Data;
}



