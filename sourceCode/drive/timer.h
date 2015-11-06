#ifndef __LHG_MYTIMER_H__
#define __LHG_MYTIMER_H__

#include "INCLUDES.h"

volatile unsigned int count0,flag0;
volatile unsigned int count1,flag1;
volatile unsigned int count2,flag2;
volatile unsigned int count3,flag3;

void Timer0_Init(void);  // 初始化timer0，1ms count++
void Timer1_Init(void);
void Timer2_Init(void);
void Timer3_Init(void);
void mytimer_init(void); // 初始化全部定时器
void delayms(int ms);	 // 延时1ms，使用timer0


#endif

