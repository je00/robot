#ifndef __ROBOTIS_ADC_H__
#define __ROBOTIS_ADC_H__


#include "INCLUDES.h"

// 读AD置,ch为选择通道,转换结果最大置为1023,转换失败返回-1
unsigned char read_adc(INT8U ch,INT16U *ad);

// 读AD置,ch为选择通道,转换结果最大置为1023,转换成功返回转换结果
int read_adc2(INT8U ch);

#endif
