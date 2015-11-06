#include "INCLUDES.h"


void uart_put_char( unsigned char data)//�����ֽ�
{
	/* �ȴ����ͻ�����Ϊ�� */
	while ( !( UCSR0A & (1<<UDRE)) ) ;
	/* �����ݷ��뻺�������������� */
	UDR0 = data;	
}

void uart1_put_char( unsigned char data)//�����ֽ�
{
	/* �ȴ����ͻ�����Ϊ�� */
	while ( !( UCSR1A & (1<<UDRE)) )
	;
	/* �����ݷ��뻺�������������� */
	UDR1 = data;
	while ( !( UCSR1A & (1<<6)) )
	;	
}
void uart1_put_str(char * str)//����һ���ַ���
{
	char *tmp=str;
	while ( *tmp!=0 )
	{
		uart1_put_char(*tmp);
		tmp++;
	}
}

void uart_put_str(char * str)//����һ���ַ���
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
	��int����ת��Ϊ16���Ʋ�����
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
  
  cli();				//�����ж�
  //16MHZ�������ò�����
 // UCSR0A &= ~(0x02); //����Ƶ
  UCSR0A=0;
  INT16U baud;
 // baud = 103; //9600
  baud = 0; //1M
  UBRR0H = (unsigned char)(baud>>8);
  UBRR0L = (unsigned char)baud;
  // ����֡��ʽ: 8 ������λ, 1��ֹͣλ
  UCSR0C = (3<<UCSZ0);

  // �������뷢����ʹ�ܣ������ж�����
  UCSR0B = (1<<RXEN)|(1<<TXEN)|(1<<RXCIE);

 //16MHZ�������ò�����
 // UCSR0A &= ~(0x02); //����Ƶ
  UCSR1A=0;
  //baud = 16;//57600
  //baud = 8;//115200
  baud = 103; //9600
  //baud = 0; //1M
  UBRR1H = (unsigned char)(baud>>8);
  UBRR1L = (unsigned char)baud;
  // ����֡��ʽ: 8 ������λ, 1��ֹͣλ
  UCSR1C = (3<<UCSZ0);

  // �������뷢����ʹ�ܣ������ж�����
  UCSR1B = (1<<RXEN)|(1<<TXEN) | (1<<RXCIE);
 


  //�����ж�
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
