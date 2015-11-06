/**
	�������
	@history��
		1���򻯣�����������
		@corroctor�� Ting
		@date:		 27th July, 2014
**/

#include "INCLUDES.h"

/**
	����һ��ָ���
	@para��
		ID:    Ŀ����id		Instruction��ָ��
		array������Ӧ��ָ������,����˴�Ϊ0��ʹ��Ĭ�ϵ�ȫ�ֱ���read_state.array����������
**/
void TxPacket(INT8U ID,INT8U ParameterLength,INT8U *Parameter,INT8U Instruction)
{
	INT8U  i;
	INT8U  temp;
	INT16U checksum;								//У����
	INT8U  *arr;									//ָ���ָ�������
	cli();
	TXD_EN();										//��������
	_delay_us(100);	
	uart_put_char(0xff);							//���Ͱ�ͷ
	uart_put_char(0xff);
	uart_put_char(ID);
	uart_put_char(ParameterLength+2);
	uart_put_char(Instruction);
	checksum = ID+ParameterLength+2+Instruction;
	for (i=0;i<ParameterLength;i++)
	{
		uart_put_char(*(Parameter+i));				//��ַ
		checksum += *(Parameter+i);
	}
	checksum=~(checksum%256);
	checksum&=0x00ff;
	uart_put_char((INT8U)checksum);
	WAIT_UART0();
}

/**
	��ָ������˶���locationλ��
	@para�� 
			id��	  ָ�����id		
			location��Ŀ��λ��
			speed:	  �ٶ�	
**/
void servo_action_now(INT8U id,INT16U location,INT16U speed)//ͬ��ָ�������̶���
{
   INT8U par[5];
   //�ж�ֵ�Ƿ���󣬴����򲻷�
   if( (location>1023)||(speed>1023) )
   return;
   cli();
   par[0]=30;//���Ʊ��ַ
   par[1]=location&0xff;
   par[2]=(location>>8)&0xff;
   par[3]=speed&0xff;
   par[4]=(speed>>8)&0xff;
   TxPacket(id,5,par,3);//����ָ���
   sei();
}



