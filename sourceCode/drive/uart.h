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
#define WAIT_UART0() while ( !( UCSR0A & (1<<5)) ); // 等待串口空闲
#define WAIT

void myuart_init(void);						// void uart_put_char(unsigned char data);		// void uart_put_str(char *str);				// void uart1_put_str(char * str);				// 发送一个字符串
void uart1_put_char( unsigned char data);	// 发送字节
void uart1_put_int(int num);				// 发送一个整型
unsigned char uart1_get_char(void);					// 接收一个字符
void uart1_put_hex(int data);				// 将int数据转换为16进制并发送

#endif
