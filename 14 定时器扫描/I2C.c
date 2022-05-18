
#include <REGX52.H>
#include "Tools.h"

sbit I2C_SCL=P2^1;
sbit I2C_SDA=P2^0;

void I2C_Start() //起始条件
{
	//起始条件：SCL高电平期间，SDA从高电平切换到低电平
	I2C_SDA=1;   //在结束应答位之后可能是0或1，确保SDA是从高电平到低电平，置1
	I2C_SCL=1;   //SCL高电平期间
	I2C_SDA=0;   //切换到低电平
	I2C_SCL=0;   
}

void I2C_Stop()  //终止条件
{
	//终止条件：SCL高电平期间，SDA从低电平切换到高电平
	I2C_SDA=0;   //拉低，确保能够产生上升沿
	I2C_SCL=1;
	I2C_SDA=1;   //产生上升沿
	//I2C_SCL，I2C_SDA操作结束后均为高电平，符合空闲状态标准
}

void I2C_SendByte(unsigned char Byte)  //发送一个字节
{
	/*
	发送一个字节：SCL低电平期间，主机将数据位依次放到SDA线上（高位在前）
	然后拉高SCL，从机将在SCL高电平期间读取数据位
	所以SCL高电平期间SDA不允许有数据变化，依次循环上述过程8次，即可发送一个字节
	*/
	//I2C_Start()已将SCL置0
	unsigned char i;
	for(i=0;i<8;i++)
	{
		I2C_SDA=Byte & (0x80>>i);  //（高位在前）
		I2C_SCL=1;   //然后拉高SCL
		I2C_SCL=0;   //拉低电平，放数据 		
	}
}

unsigned char I2C_ReceiveByte()  //接收一个字节
{
	/*（主机在接收之前，需要释放SDA）
	接收一个字节：SCL低电平期间，从机将数据位依次放到SDA线上（高位在前）
	然后拉高SCL，主机将在SCL高电平期间读取数据位
	所以SCL高电平期间SDA不允许有数据变化，依次循环上述过程8次
	即可接收一个字节（主机在接收之前，需要释放SDA）
	*/
	unsigned char Byte=0x00,i;
	I2C_SDA=1;  //释放SDA,将控制权给从机
	for(i=0;i<8;i++)
	{
		I2C_SCL=1;    //主机将在SCL高电平期间读取数据位
		if(I2C_SDA) {Byte|=(0x80>>i);}
		I2C_SCL=0;		//SCL低电平期间，从机将数据位依次放到SDA线上，所以SDA可能是0或1
	}
	return Byte;
}

void I2C_SendACK(unsigned char ACK)  //发送应答
{
	/*发送应答：在接收完一个字节之后，主机在下一个时钟发送一位数据
	数据0表示应答，数据1表示非应答*/
	//发送应答相当于发送一个字节：SCL低电平期间，主机/从机将数据位依次放到SDA线上（高位在前）
	//然后拉高SCL，从机将在SCL高电平期间读取数据位
	
	//每个函数结束后都将I2C_SCL拉低了
	I2C_SDA=ACK;//SCL低电平期间，主机/从机将数据位依次放到SDA线
	I2C_SCL=1;    //然后拉高SCL，从机将在SCL高电平期间读取数据位
	I2C_SCL=0; 
}

unsigned char I2C_ReceiveACK()  //接收应答
{
	/*（主机在接收之前，需要释放SDA）
	接收应答：在发送完一个字节之后，主机在下一个时钟接收一位数据
	判断从机是否应答，数据0表示应答，数据1表示非应答*/
	/*相当于接收一个字节：SCL低电平期间，从机将数据位依次放到SDA线上（高位在前）
	然后拉高SCL，主机将在SCL高电平期间读取数据位*/
	unsigned char ACK;
	I2C_SDA=1;   //释放SDA控制权，由主机/从机控制SDA
	I2C_SCL=1;   //在SCL高电平期间读取数据位
	ACK=I2C_SDA;    
	I2C_SCL=0;   //恢复
	return ACK;
}

