#include "INCLUDES.h"

/**
	读AD置,ch为选择通道,转换结果最大置为1023,转换失败返回false
**/
unsigned char read_adc(INT8U ch,INT16U *ad)
{
	
	INT16U i;
	ch=(ch+7)&7;
	ADMUX=(0<<6)|ch;			//参考电压选择AREF内部Vref关闭,通道选择
	ADCSRA=(1<<7)|(1<<6)|7;		//开始AD转换,连续AD转换,预分频为

	i=0;
	while( ADCSRA&(1<<6) )
	{
		i++;
		if(i>16000)
		{
			ADCSRA=3;			//关AD转换
			return -1;			//转换失败返回-1
		}
	}
	*ad=ADC;
	if(*ad>1023)
	{
		*ad=1023;
	}
	ADCSRA=7;					//关AD转换
 	return 1;
}

int read_adc2(INT8U ch){
	INT16U i;					//延时用
	ch=(ch+7)&7;
	ADMUX=(0<<6)|ch;			//参考电压选择AREF内部Vref关闭,通道选择
	ADCSRA=(1<<7)|(1<<6)|7;		//开始AD转换,连续AD转换,预分频为

	i=0;
	while( ADCSRA&(1<<6) )
	{
		i++;
		if(i>16000)
		{
			ADCSRA=3;			//关AD转换 
			return -1;			//转换失败返回-1
		}
	}
	if(ADC>1023)
	{
		ADC=1023;
	}
	ADCSRA=7;					//关AD转换
	return ADC;
}


