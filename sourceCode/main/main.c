

#include "INCLUDES.h"

int main()
{	
	// 无按键连接 AD_CHECK_IO 或 按下按键，进入比赛程序
	if( read_adc2(AD_CHECK_IO) < 512 ) { _delay_ms(200);	// 消抖
	if( read_adc2(AD_CHECK_IO) < 512 ) { 
		init_device();
		fight();
	}}

	// 按键连接 AD_CHECK_IO 且 按键弹起, 进入参数设置程序（使用超级终端）
	else	
		menu();
}

