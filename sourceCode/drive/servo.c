/**
	舵机驱动
	@history：
		1、简化，不接受数据
		@corroctor： Ting
		@date:		 27th July, 2014
**/

#include "INCLUDES.h"

/**
	发送一个指令包
	@para：
		ID:    目标舵机id		Instruction：指令
		array：接收应答指令数组,如果此处为0将使用默认的全局变量read_state.array数组来接收
**/
void TxPacket(INT8U ID,INT8U ParameterLength,INT8U *Parameter,INT8U Instruction)
{
	INT8U  i;
	INT8U  temp;
	INT16U checksum;								//校验码
	INT8U  *arr;									//指令保存指令的数组
	cli();
	TXD_EN();										//发送允许
	_delay_us(100);	
	uart_put_char(0xff);							//发送包头
	uart_put_char(0xff);
	uart_put_char(ID);
	uart_put_char(ParameterLength+2);
	uart_put_char(Instruction);
	checksum = ID+ParameterLength+2+Instruction;
	for (i=0;i<ParameterLength;i++)
	{
		uart_put_char(*(Parameter+i));				//地址
		checksum += *(Parameter+i);
	}
	checksum=~(checksum%256);
	checksum&=0x00ff;
	uart_put_char((INT8U)checksum);
	WAIT_UART0();
}

/**
	让指定舵机运动到location位置
	@para： 
			id：	  指定舵机id		
			location：目标位置
			speed:	  速度	
**/
void servo_action_now(INT8U id,INT16U location,INT16U speed)//同步指令，舵机立刻动作
{
   INT8U par[5];
   //判断值是否错误，错误则不发
   if( (location>1023)||(speed>1023) )
   return;
   cli();
   par[0]=30;//控制表地址
   par[1]=location&0xff;
   par[2]=(location>>8)&0xff;
   par[3]=speed&0xff;
   par[4]=(speed>>8)&0xff;
   TxPacket(id,5,par,3);//发送指令包
   sei();
}



