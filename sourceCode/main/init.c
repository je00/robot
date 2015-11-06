/*
 * 机器人初始化、预备的相关方法
 * @Author: Ting
 * @Date: 24th July, 2014
 */

#include "INCLUDES.h"

/*
 * 初始化AVR资源，从EEPROM中读取机器人参数，然后预备等待登场手势
 */
void init_device(void)
{
	cli();

	/* 1.初始化串口、定时器 */
	myuart_init();	
	mytimer_init();

	/* 2.从EEPROM中获取参数 */
	globalVarInit();
	
	/* 3.设置速度参数 */

	// 设置攻击加速度
	setSpeedRation(NODE_L, ATTACKRATION, ATTACKRATION);
	setSpeedRation(NODE_R, ATTACKRATION, ATTACKRATION);
	// 设置最大、最小速度
	setNatureSpeed(NODE_L, 0, TOPSPEED); 
	setNatureSpeed(NODE_R, 0, TOPSPEED);
	
	/* 4.预备 */
	ready();
	// 开总中断
	sei();
}

/*
 * 从EEPOM中获取机器人参数，设置全局变量
 */
void globalVarInit(void)
{
	uart1_put_str("正在读取eeprom...\n");
	eeprom_rOw_par(EEP_R);	

	// 轨道参数初始化
	sensor.trackCode = 0; 
	MEMORYCYCLE = MEMORYCYCLE_INIT;
	minGreyTrack2 = AD_BLACK + (AD_WHITE - AD_BLACK) /CORNERRATION;
	AD_MAXGAP = (AD_WHITE - minGreyTrack2) /3;
	minGreyTrack1 = minGreyTrack2 + AD_MAXGAP; 
	minGreyTrack0 = minGreyTrack1 + AD_MAXGAP; 

	// 最大灰度突变，当两灰度差大于最大灰度突变，视为步入红色
	AD_MAXGAP += 10;

	myFriend.id = 0x34;
	myFriend.detectCode = 0xff;
	// 开启定时器2，用来记录两次数据包的间隔时间
	flag2 = 1;

}

/*
 * 在阶梯处做准备，直到遮挡右侧红外开关
 */
void ready()
{
	unsigned char i = 0;
	unsigned char j = 0;
	while(1)	
	{
		i = 0;
		sensor.io_r	=READ_GPIO(IO_R);
		while(sensor.io_r == 0) {
			uart1_put_str("\n\rMODE: FIGHT\n\r");
	        	sensor.io_r = READ_GPIO(IO_R);
			sensor.io_l = READ_GPIO(IO_L);
			if(i++ > 10) // 经10次确定是正常启动
				goto OK;
			_delay_ms(10);
		}
	}
OK:
	//  下面三个参数要经过仔细调试，保证机器人能冲到擂台中央
	setSpeed(READYSPEEDL, READYSPEEDR);
	_delay_ms(MSGOUP);

	// 在擂台中央停住
	goOnSpeed(0);
}
