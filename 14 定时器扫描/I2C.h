#ifndef _I2C_H_
#define _I2C_H_
/*AT24C02的子文件*/

void I2C_Start(); //起始条件

void I2C_Stop();  //终止条件

void I2C_SendByte(unsigned char Byte);  //发送一个字节

unsigned char I2C_ReceiveByte();  //接收一个字节

void I2C_SendACK(unsigned char ACK);  //发送应答

unsigned char I2C_ReceiveACK();  //接收应答
#end