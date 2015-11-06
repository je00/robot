
#ifndef __ROBOTIS_UART_H__
#define __ROBOTIS_UART_H__


#define INT8U char
#define INT16U int

typedef unsigned char BOOLEAN;

//����ÿ��ָ�����Ĳ�������������״̬λ�ͼ��λ2���ֽ�
#define READ_PRA_MAX  20


#define TXD_EN() (DDRA|=0x3,PORTA&=~0x3,PORTA|=1)	//��������
#define RXD_EN() (DDRA|=0x3,PORTA&=~0x3,PORTA|=2)	//��������
#define UART_PACKET_READ  0x02 						//��ָ��
#define UART_PACKET_WRITE 0x03						//дָ��


void TxPacket(INT8U ID,INT8U ParameterLength,INT8U *Parameter,INT8U Instruction);//����ָ���
void servo_action_now(INT8U id,INT16U location,INT16U speed);					 //����˶���locationλ��

#endif
