#ifndef __LHG_MY_UART_H__
#define __LHG_MY_UART_H__

#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>


#include "avr/io.h"
#include "avr/interrupt.h"



#define UDRE   5 
#define RXEN   4
#define TXEN   3
#define UCSZ0  1
#define RXC    7
#define RXCIE  7

#define SET_1(a,b) a|=(1<<b)
#define CLE_0(a,b) a&=~(1<<b)
#define NOP() asm("nop")
#define WAIT_UART0() while ( !( UCSR0A & (1<<5)) ); // �ȴ����ڿ���
#define WAIT

void myuart_init(void);						// void uart_put_char(unsigned char data);		// void uart_put_str(char *str);				// void uart1_put_str(char * str);				// ����һ���ַ���
void uart1_put_char( unsigned char data);	// �����ֽ�
void uart1_put_int(int num);				// ����һ������
unsigned char uart1_get_char(void);					// ����һ���ַ�
void uart1_put_hex(int data);				// ��int����ת��Ϊ16���Ʋ�����

#endif
