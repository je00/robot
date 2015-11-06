#include "INCLUDES.h"


void uart_put_char( unsigned char data)//发送字节
{
	/* 等待发送缓冲器为空 */
	while ( !( UCSR0A & (1<<UDRE)) ) ;
	/* 将数据放入缓冲器，发送数据 */
	UDR0 = data;	
}

void uart1_put_char( unsigned char data)//发送字节
{
	/* 等待发送缓冲器为空 */
	while ( !( UCSR1A & (1<<UDRE)) )
	;
	/* 将数据放入缓冲器，发送数据 */
	UDR1 = data;
	while ( !( UCSR1A & (1<<6)) )
	;	
}
void uart1_put_str(char * str)//发送一个字符串
{
	char *tmp=str;
	while ( *tmp!=0 )
	{
		uart1_put_char(*tmp);
		tmp++;
	}
}

void uart_put_str(char * str)//发送一个字符串
{
	char *tmp=str;
	while ( *tmp!=0 )
	{
		uart_put_char(*tmp);
		tmp++;
	}
}

void uart1_put_int(int num)
{
	char buf[64];
	sprintf(buf, "%d", num);
	uart1_put_str(buf);

}

unsigned char uart1_get_char(void)
{
    while( !(UCSR1A & (1<<RXC1)) ) ;
     
     return UDR1 ;
}

/**
	将int数据转换为16进制并发送
**/
void uart1_put_hex(int data) 
{
	uart1_put_char(data/256);
	uart1_put_char(data%256);
		
}

SIGNAL(SIG_USART1_RECV) {
	unsigned char buf = uart1_get_char();;
	if(queue_full())
		queue_out_char();
	queue_append(buf);
//	uart1_put_str("\ntt\n");
}

void myuart_init(void)
{
  
  cli();				//关总中断
  //16MHZ晶振，设置波特率
 // UCSR0A &= ~(0x02); //不倍频
  UCSR0A=0;
  INT16U baud;
 // baud = 103; //9600
  baud = 0; //1M
  UBRR0H = (unsigned char)(baud>>8);
  UBRR0L = (unsigned char)baud;
  // 设置帧格式: 8 个数据位, 1个停止位
  UCSR0C = (3<<UCSZ0);

  // 接收器与发送器使能，接收中断允许
  UCSR0B = (1<<RXEN)|(1<<TXEN)|(1<<RXCIE);

 //16MHZ晶振，设置波特率
 // UCSR0A &= ~(0x02); //不倍频
  UCSR1A=0;
  //baud = 16;//57600
  //baud = 8;//115200
  baud = 103; //9600
  //baud = 0; //1M
  UBRR1H = (unsigned char)(baud>>8);
  UBRR1L = (unsigned char)baud;
  // 设置帧格式: 8 个数据位, 1个停止位
  UCSR1C = (3<<UCSZ0);

  // 接收器与发送器使能，接收中断允许
  UCSR1B = (1<<RXEN)|(1<<TXEN) | (1<<RXCIE);
 


  //开总中断
//  sei();
}



void enable_uart1(INT8U c)
{
	if(c==1)
	{
		UCSR1B |= (1<<RXCIE);
	}else
	{
		UCSR1B &= ~(1<<RXCIE);
	}
}
