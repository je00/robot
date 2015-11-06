#include "INCLUDES.h"

/**
	��AD��,chΪѡ��ͨ��,ת����������Ϊ1023,ת��ʧ�ܷ���false
**/
unsigned char read_adc(INT8U ch,INT16U *ad)
{
	
	INT16U i;
	ch=(ch+7)&7;
	ADMUX=(0<<6)|ch;			//�ο���ѹѡ��AREF�ڲ�Vref�ر�,ͨ��ѡ��
	ADCSRA=(1<<7)|(1<<6)|7;		//��ʼADת��,����ADת��,Ԥ��ƵΪ

	i=0;
	while( ADCSRA&(1<<6) )
	{
		i++;
		if(i>16000)
		{
			ADCSRA=3;			//��ADת��
			return -1;			//ת��ʧ�ܷ���-1
		}
	}
	*ad=ADC;
	if(*ad>1023)
	{
		*ad=1023;
	}
	ADCSRA=7;					//��ADת��
 	return 1;
}

int read_adc2(INT8U ch){
	INT16U i;					//��ʱ��
	ch=(ch+7)&7;
	ADMUX=(0<<6)|ch;			//�ο���ѹѡ��AREF�ڲ�Vref�ر�,ͨ��ѡ��
	ADCSRA=(1<<7)|(1<<6)|7;		//��ʼADת��,����ADת��,Ԥ��ƵΪ

	i=0;
	while( ADCSRA&(1<<6) )
	{
		i++;
		if(i>16000)
		{
			ADCSRA=3;			//��ADת�� 
			return -1;			//ת��ʧ�ܷ���-1
		}
	}
	if(ADC>1023)
	{
		ADC=1023;
	}
	ADCSRA=7;					//��ADת��
	return ADC;
}


