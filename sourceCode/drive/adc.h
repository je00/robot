#ifndef __ROBOTIS_ADC_H__
#define __ROBOTIS_ADC_H__


#include "INCLUDES.h"

// ��AD��,chΪѡ��ͨ��,ת����������Ϊ1023,ת��ʧ�ܷ���-1
unsigned char read_adc(INT8U ch,INT16U *ad);

// ��AD��,chΪѡ��ͨ��,ת����������Ϊ1023,ת���ɹ�����ת�����
int read_adc2(INT8U ch);

#endif
