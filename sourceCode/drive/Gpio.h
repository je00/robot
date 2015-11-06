/*******************************************************Copyright*********************************************************
**                                            ����������ʢ�����˼������޹�˾
**                                                       �з���
**                                               http://robot.up-tech.com
**
**-------------------------------------------------------�ļ���Ϣ---------------------------------------------------------
** �ļ�����:			Gpio.h
** ����޶�����:		2009-03-17
** ���汾:			1.0
** ����:				Gpio���ƺ����ӿڣ�������PPM����˿ڵĶ���(API)
**
**------------------------------------------------------------------------------------------------------------------------
** ������:			����
** ��������:			2009-03-17
** �汾:				1.0
** ����:				�Խӿڵķ��򼰵�ƽ������ֱ��ӳ��AVR����Ĺ��ܣ����ṩ��51��MCU�Ľӿڿ��Ʒ����ļ���(API)
**
**------------------------------------------------------------------------------------------------------------------------
** �޶���:
** �޶�����:
** �汾:
** ����:
**
**------------------------------------------------------------------------------------------------------------------------
** �޶���:
** �޶�����:
** �汾:
** ����:
**
*************************************************************************************************************************/
#ifndef GPIO_H_
#define GPIO_H_




/*************************************************************************************************************************
                                                  GPIO�˿ڶ���
*************************************************************************************************************************/
#define GPIO1_PORT			PORTE							// ����GPIO�����ʹ�õĶ˿����ݼĴ���
#define GPIO1_PORT_BIT		PE4								// ����˿���ÿһλ��GPIO��ŵĶ�Ӧ��ϵ
#define GPIO1_DDR			DDRE							// ����GPIO�����ʹ�õĶ˿ڷ���Ĵ���
#define GPIO1_DDR_BIT		DDE4
#define GPIO1_PIN			PINE							// ����GPIO�����ʹ�õĶ˿ڵ�״̬�Ĵ���
#define GPIO1_PIN_BIT		PINE4
#define GPIO1_BIT			4

#define GPIO0_PORT			PORTE		
#define GPIO0_PORT_BIT		PE5	
#define GPIO0_DDR			DDRE	
#define GPIO0_DDR_BIT		DDE5
#define GPIO0_PIN			PINE
#define GPIO0_PIN_BIT		PINE5
#define GPIO0_BIT			5

#define GPIO3_PORT			PORTE		
#define GPIO3_PORT_BIT		PE6	
#define GPIO3_DDR			DDRE	
#define GPIO3_DDR_BIT		DDE6
#define GPIO3_PIN			PINE
#define GPIO3_PIN_BIT		PINE6
#define GPIO3_BIT			6

#define GPIO2_PORT			PORTE		
#define GPIO2_PORT_BIT		PE7	
#define GPIO2_DDR			DDRE	
#define GPIO2_DDR_BIT		DDE7
#define GPIO2_PIN			PINE
#define GPIO2_PIN_BIT		PINE7
#define GPIO2_BIT			7


#define GPIO5_PORT			PORTB	
#define GPIO5_PORT_BIT		PB6		
#define GPIO5_DDR			DDRB	
#define GPIO5_DDR_BIT		DDB6
#define GPIO5_PIN			PINB
#define GPIO5_PIN_BIT		PINB6
#define GPIO5_BIT			6

#define GPIO4_PORT			PORTB	
#define GPIO4_PORT_BIT		PB5		
#define GPIO4_DDR			DDRB	
#define GPIO4_DDR_BIT		DDB5
#define GPIO4_PIN			PINB
#define GPIO4_PIN_BIT		PINB5
#define GPIO4_BIT			5

#define GPIO7_PORT			PORTE	
#define GPIO7_PORT_BIT		PE2		
#define GPIO7_DDR			DDRE	
#define GPIO7_DDR_BIT		DDE2
#define GPIO7_PIN			PINE
#define GPIO7_PIN_BIT		PINE2
#define GPIO7_BIT			2

#define GPIO6_PORT			PORTE		
#define GPIO6_PORT_BIT		PE3			
#define GPIO6_DDR			DDRE	
#define GPIO6_DDR_BIT		DDE3
#define GPIO6_PIN			PINE
#define GPIO6_PIN_BIT		PINE3
#define GPIO6_BIT			3


#define GPIO11_PORT			PORTD		
#define GPIO11_PORT_BIT		PD6			
#define GPIO11_DDR			DDRD	
#define GPIO11_DDR_BIT		DDD6
#define GPIO11_PIN			PIND
#define GPIO11_PIN_BIT		PIND6
#define GPIO11_BIT			6

#define GPIO8_PORT			PORTD		
#define GPIO8_PORT_BIT		PD4			
#define GPIO8_DDR			DDRD	
#define GPIO8_DDR_BIT		DDD4
#define GPIO8_PIN			PIND
#define GPIO8_PIN_BIT		PIND4
#define GPIO8_BIT			4

#define GPIO10_PORT			PORTB		
#define GPIO10_PORT_BIT		PB7			
#define GPIO10_DDR			DDRB	
#define GPIO10_DDR_BIT		DDB7
#define GPIO10_PIN			PINB
#define GPIO10_PIN_BIT		PINB7
#define GPIO10_BIT			7

#define GPIO9_PORT			PORTD		
#define GPIO9_PORT_BIT		PD1			
#define GPIO9_DDR			DDRD	
#define GPIO9_DDR_BIT		DDD1
#define GPIO9_PIN			PIND
#define GPIO9_PIN_BIT		PIND1
#define GPIO9_BIT			1





#define PPM1_PORT			PORTC							// ����PPM�����ʹ�õĶ˿����ݼĴ���
#define PPM1_PORT_BIT		PC0								// ����˿���ÿһλ��PPM��ŵĶ�Ӧ��ϵ
#define PPM1_DDR			DDRC							// ����PPM�����ʹ�õĶ˿ڷ���Ĵ���
#define PPM1_DDR_BIT		DDC0
#define PPM1_BIT			0
#define PPM1_PIN			PINC
#define PPM1_PIN_BIT		PINC0

#define PPM0_PORT			PORTC		
#define PPM0_PORT_BIT		PC1	
#define PPM0_DDR			DDRC	
#define PPM0_DDR_BIT		DDC1
#define PPM0_BIT			1
#define PPM0_PIN			PINC
#define PPM0_PIN_BIT		PINC1

#define PPM2_PORT			PORTC		
#define PPM2_PORT_BIT		PC3	
#define PPM2_DDR			DDRC	
#define PPM2_DDR_BIT		DDC3
#define PPM2_BIT			3
#define PPM2_PIN			PINC
#define PPM2_PIN_BIT		PINC3

#define PPM3_PORT			PORTC		
#define PPM3_PORT_BIT		PC2	
#define PPM3_DDR			DDRC	
#define PPM3_DDR_BIT		DDC2
#define PPM3_BIT			2
#define PPM3_PIN			PINC
#define PPM3_PIN_BIT		PINC2


#define PPM5_PORT			PORTC	
#define PPM5_PORT_BIT		PC4		
#define PPM5_DDR			DDRC	
#define PPM5_DDR_BIT		DDC4
#define PPM5_BIT			4
#define PPM5_PIN			PINC
#define PPM5_PIN_BIT		PINC4

#define PPM4_PORT			PORTC	
#define PPM4_PORT_BIT		PC5		
#define PPM4_DDR			DDRC	
#define PPM4_DDR_BIT		DDC5
#define PPM4_BIT			5
#define PPM4_PIN			PINC
#define PPM4_PIN_BIT		PINC5

#define PPM7_PORT			PORTC	
#define PPM7_PORT_BIT		PC6		
#define PPM7_DDR			DDRC	
#define PPM7_DDR_BIT		DDC6
#define PPM7_BIT			6
#define PPM7_PIN			PINC
#define PPM7_PIN_BIT		PINC6

#define PPM6_PORT			PORTC		
#define PPM6_PORT_BIT		PC7
#define PPM6_DDR			DDRC	
#define PPM6_DDR_BIT		DDC7
#define PPM6_BIT			7
#define PPM6_PIN			PINC
#define PPM6_PIN_BIT		PINC7
/*
#define GPIO_GROUP0_PIN		PINB
#define GPIO_GROUP1_PIN		PIND
#define GPIO_GROUP2_PIN		PINE


#define GPIO_GROUP0_MASK	(1 << GPIO4_BIT) | (1 << GPIO5_BIT) | (1 << GPIO10_BIT)
#define GPIO_GROUP1_MASK	(1 << GPIO8_BIT) | (1 << GPIO9_BIT) | (1 << GPIO11_BIT)
#define GPIO_GROUP2_MASK	(1 << GPIO0_BIT) | (1 << GPIO1_BIT) | (1 << GPIO2_BIT) | (1 << GPIO3_BIT) | (1 << GPIO6_BIT) | (1 << GPIO7_BIT)
*/

//��GPIO��GPIOΪ�˿�ѡ��,ע�⣬���⴫���������谭��ʱ���ص���0 
#define READ_GPIO(GPIO) _READ_GPIO(GPIO)
#define _READ_GPIO(GPIO) ( (GPIO##_PORT&=~(1<<GPIO##_BIT)),(GPIO##_DDR&=~(1<<GPIO##_BIT)),((GPIO##_PIN>>GPIO##_BIT)&0x01) )
//дGPIO��GPIOΪ�˿�ѡ��bitΪд0����1��ע�⣬��ɫ�źŵƵ͵�ƽ�ŵ���
#define WRITE_GPIO(GPIO,bit) _WRITE_GPIO(GPIO,bit)
#define _WRITE_GPIO(GPIO,bit) ( (GPIO##_DDR|=1<<GPIO##_BIT),bit?(GPIO##_PORT|=1<<GPIO##_BIT):(GPIO##_PORT&=~(1<<GPIO##_BIT)) )
#define SetGpio(id,bit)\
{\
	switch(id)\
	{\
		case 0:\
			WRITE_GPIO(GPIO0,bit);\
		break;\
		case 1:\
			WRITE_GPIO(GPIO1,bit);\
		break;\
		case 2:\
			WRITE_GPIO(GPIO2,bit);\
		break;\
		case 3:\
			WRITE_GPIO(GPIO3,bit);\
		break;\
		case 4:\
			WRITE_GPIO(GPIO4,bit);\
		break;\
		case 5:\
			WRITE_GPIO(GPIO5,bit);\
		break;\
		case 6:\
			WRITE_GPIO(GPIO6,bit);\
		break;\
		case 7:\
			WRITE_GPIO(GPIO7,bit);\
		break;\
		case 8:\
			WRITE_GPIO(GPIO8,bit);\
		break;\
		case 9:\
			WRITE_GPIO(GPIO9,bit);\
		break;\
		case 10:\
			WRITE_GPIO(GPIO10,bit);\
		break;\
		case 11:\
			WRITE_GPIO(GPIO11,bit);\
		break;\
		case 12:\
			WRITE_GPIO(PPM0,bit);\
		break;\
	}\
}

#define GetGpio(id,bit) \
{\
	switch(id)\
	{\
		case 0:\
			*bit=READ_GPIO(GPIO0);\
		break;\
		case 1:\
			*bit=READ_GPIO(GPIO1);\
		break;\
		case 2:\
			*bit=READ_GPIO(GPIO2);\
		break;\
		case 3:\
			*bit=READ_GPIO(GPIO3);\
		break;\
		case 4:\
			*bit=READ_GPIO(GPIO4);\
		break;\
		case 5:\
			*bit=READ_GPIO(GPIO5);\
		break;\
		case 6:\
			*bit=READ_GPIO(GPIO6);\
		break;\
		case 7:\
			*bit=READ_GPIO(GPIO7);\
		break;\
		case 8:\
			*bit=READ_GPIO(GPIO8);\
		break;\
		case 9:\
			*bit=READ_GPIO(GPIO9);\
		break;\
		case 10:\
			*bit=READ_GPIO(GPIO10);\
		break;\
		case 11:\
			*bit=READ_GPIO(GPIO11);\
		break;\
	}\
}


#endif
/*************************************************************************************************************************
**                                                      �ļ�����
*************************************************************************************************************************/
