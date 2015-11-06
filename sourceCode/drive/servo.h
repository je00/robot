
#ifndef __ROBOTIS_UART_H__
#define __ROBOTIS_UART_H__


#define INT8U char
#define INT16U int

typedef unsigned char BOOLEAN;

//限制每条指令最大的参数个数，包含状态位和检测位2个字节
#define READ_PRA_MAX  20


#define TXD_EN() (DDRA|=0x3,PORTA&=~0x3,PORTA|=1)	//发送允许
#define RXD_EN() (DDRA|=0x3,PORTA&=~0x3,PORTA|=2)	//接收允许
#define UART_PACKET_READ  0x02 						//读指令
#define UART_PACKET_WRITE 0x03						//写指令


void TxPacket(INT8U ID,INT8U ParameterLength,INT8U *Parameter,INT8U Instruction);//发送指令包
void servo_action_now(INT8U id,INT16U location,INT16U speed);					 //舵机运动到location位置

#endif
