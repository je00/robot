/**
	参数设置程序，PC端通过超级中断接收和发送串口数据，实现对小车参数的设置
	@author: Ting
	@date:	 	24th July, 2014
	@history:
		1、在菜单中将各轨道最小灰度计算完毕存入eeprom，不保存原始采样结果
			@corrector：Ting
			@date: 4th April, 2014
**/
#include "INCLUDES.h"

char select;
char buf[6];
int i;

void menu() 
{
	myuart_init();
	_delay_ms(1000);

	uart1_put_str("\n\n\r设置模式启动，正在读取信息...");

	//从EEPROM中读取参数
	eeprom_rOw_par(EEP_R);

	uart1_put_str("\n\r读取成功！");
	
	while(1) {

		buf[0] = 'n'; buf[1] = 'n'; buf[2] = 'n'; buf[3] = 'n'; buf[4] = 'n';

		do {
			uart1_put_str("\n\n\r您要进行哪项操作?");
			uart1_put_str("\n\r1.打印当前信息");
			uart1_put_str("\t2.设置推棋参数");
			uart1_put_str("\t3.进行灰度采样");
			uart1_put_str("\t4.设置角落权值");
			uart1_put_str("\n\r5.设置状态周期");
			uart1_put_str("\t6.设置记忆周期");
			uart1_put_str("\t7.设置上台参数");
			uart1_put_str("\t8.设置电机参数");
			uart1_put_str("\n\rl.重读");
			uart1_put_str("\tw.保存");
			uart1_put_str("\n\r-> ");
			select = uart1_get_char();
			uart1_put_char(select);
		} while(	select != '1' && select != '2' && select != '3' && select != '4' && select != '5'
			 && 	select != '6' && select != '7' && select != '8' && select != 'l' && select != 'w' 
				);

		switch(select) {
		
		case '1':	// 打印当前信息
			printMessage();
		break;

		case '2':	// 设置推棋子参数
			setPush();
		break;

		case '3':	// 灰度采样
			refresh_stage_AD();
		break;	

		case '4':	// 设置角落权值
			setCornerRation();
		break;

		case '5':	// 设置状态周期
			setStateCycle();
		break;	

		case '6':	// 设置记忆周期
			setMemoryCycle();
		break;

		case '7':	// 设置上台参数
			setReady();
		break;

		case '8':	// 设置电机参数
			setMotor();
		break;

		case 'w':	// 保存
			uart1_put_str("\n\n\r正在保存...");
			eeprom_rOw_par(EEP_W);
			uart1_put_str("\n\r保存成功!");
		break;

		case 'l':	// 重新读取
			uart1_put_str("\n\n\r正在重新读取信息...");
			eeprom_rOw_par(EEP_R);
			uart1_put_str("\n\r读取成功！");
		break;
		}
	}
}	

/**
	打印当前信息
**/
void printMessage() 
{
	uart1_put_str("\n\n\r-------------------------------------------------------------------");

	uart1_put_str("\n\r状态周期：");
	uart1_put_int(STATECYCLE); uart1_put_str("ms");

	uart1_put_str("\t记忆周期：");
	uart1_put_int(MEMORYCYCLE_INIT); uart1_put_str("ms");

	uart1_put_str("\n\r上台参数：");
	uart1_put_str("\n\r\t  速度：");
	uart1_put_str("\t左：");	uart1_put_int(READYSPEEDL);	
	uart1_put_str("\t右：");	uart1_put_int(READYSPEEDR);
	uart1_put_str("\t爬升时延：");	
	uart1_put_int(MSGOUP); uart1_put_str("ms");
	
	uart1_put_str("\n\r推棋参数：");
	uart1_put_str("\n\r\t  速度："); uart1_put_int(SPEEDPUSH);	
	uart1_put_str("\t  状态周期：");uart1_put_int(MEMORYCYCLE_PUSH); uart1_put_str("ms");
		
	uart1_put_str("\n\r灰度信息：");
	uart1_put_str("\n\r\t  灰度偏置：");
	uart1_put_str("\t左：");	uart1_put_int(AD_ADJUST_L);	
	uart1_put_str("\t右：");	uart1_put_int(AD_ADJUST_R);
	uart1_put_str("\n\r\t  各灰度值：");
	uart1_put_str("\t武：");	uart1_put_int(AD_WU);	
	uart1_put_str("\t白：");	uart1_put_int(AD_WHITE);
	uart1_put_str("\t黑：");	uart1_put_int(AD_BLACK);
	uart1_put_str("\n\r\t  角落权值：\t");
	uart1_put_int(CORNERRATION);

	uart1_put_str("\n\r电机信息:");
	uart1_put_str("\n\r\t  电机ID：");
	uart1_put_str("\t左："); uart1_put_int(NODE_L);
	uart1_put_str("\t右："); uart1_put_int(NODE_R);
	uart1_put_str("\n\r\t  最大速度：\t"); 	uart1_put_int(TOPSPEED);
	uart1_put_str("\n\r\t  转弯速度：\t");	uart1_put_int(TURNSPEED);
	uart1_put_str("\n\r\t  安全速度：\t"); 	uart1_put_int(SAFESPEED);
	uart1_put_str("\n\r\t  安全加速：\t"); 	uart1_put_int(SAFERATION);
	uart1_put_str("\n\r\t  攻击速度："); 
	uart1_put_str("\t一档："); 				uart1_put_int(ATTACKGEAR1);	
	uart1_put_str("\t二档："); 				uart1_put_int(ATTACKGEAR2);
	uart1_put_str("\n\r\t\t\t三档：");		uart1_put_int(ATTACKGEAR3);
	uart1_put_str("\t四档："); 				uart1_put_int(ATTACKGEAR4);
	uart1_put_str("\n\r\t  攻击加速：\t");	uart1_put_int(ATTACKRATION);

	uart1_put_str("\n\r-------------------------------------------------------------------");
}

/**
	设置推棋子参数
**/
void setPush()
{
	while(1) {
		do {
			uart1_put_str("\n\n\r推棋参数：");
			uart1_put_str("\n\r1.设置速度");
			uart1_put_str("\n\r2.设置记忆周期");
			uart1_put_str("\n\r0.返回");
			uart1_put_str("\n\r-> ");
			select = uart1_get_char();
			uart1_put_char(select);
		} while( select != '1' && select != '2' && select != '3' && select != '0');
		if(select == '0') break;
		switch(select) {
		case '1':  // 设置推棋子速度
			do{
				uart1_put_str("\n\n\r设置推棋子速度(0000~9999)：");
				for(i=0; i<4; i++) {
					buf[i] = uart1_get_char();	
					uart1_put_char(buf[i]);
				}
				buf[4] = '\0';
				SPEEDPUSH = atoi(buf);
			} while(SPEEDPUSH < 0 || SPEEDPUSH > 9999);
			uart1_put_str("\n\r设置成功！");
			break;

		case '2': // 设置推棋子记忆周期
			do {
				uart1_put_str("\n\r推棋子记忆周期(0000~9999): ");
				for(i=0; i<4; i++) {
					buf[i] = uart1_get_char();	
					uart1_put_char(buf[i]);
				}
				buf[4] = '\0';
				MEMORYCYCLE_PUSH = atoi(buf);
			} while( MEMORYCYCLE_PUSH > 9999 ||MEMORYCYCLE_PUSH < 0 );
			uart1_put_str("\n\r设置成功！");

		break;

		default:
		break;
		}
	}
}

/**
	设置状态周期
**/
void setStateCycle()
{
	do {
		uart1_put_str("\n\n\r设置状态周期(000~999ms)：");
		for(i=0; i<3; i++) {
			buf[i] = uart1_get_char();	
			uart1_put_char(buf[i]);
		}
		buf[3] = '\0';
		STATECYCLE = atoi(buf);
	} while( STATECYCLE < 0 || STATECYCLE > 999);	
	uart1_put_str("\n\r设置成功！");
}

/**
	设置记忆周期
**/
void setMemoryCycle()
{
	do {
		uart1_put_str("\n\n\r设置记忆周期(0000~9999ms)：");
		for(i=0; i<4; i++) {
			buf[i] = uart1_get_char();	
			uart1_put_char(buf[i]);
		}
		buf[4] = '\0';
		MEMORYCYCLE_INIT = atoi(buf);
	} while( MEMORYCYCLE_INIT < 0 || MEMORYCYCLE_INIT > 9999);	
	uart1_put_str("\n\r设置成功！");
}

/**
	设置角落权值
**/
void setCornerRation()
{
	do {
		uart1_put_str("\n\n\r设置角落权值(0~9)：");
		buf[0] = uart1_get_char();	
		uart1_put_char(buf[0]);
		buf[1] = '\0';
		CORNERRATION = atoi(buf);
	} while( CORNERRATION < 0 || CORNERRATION > 9);	
	uart1_put_str("\n\r设置成功！");
}

/**
	设置上台参数
**/
void setReady()
{
	while(1) {
		do {
			uart1_put_str("\n\n\r上台参数：");
			uart1_put_str("\n\r1.设置速度");
			uart1_put_str("\n\r2.设置上台时延");
			uart1_put_str("\n\r0.返回");
			uart1_put_str("\n\r-> ");
			select = uart1_get_char();
			uart1_put_char(select);
		} while( select != '1' && select != '2' && select != '3' && select != '0');
		if(select == '0') break;
		switch(select) {
		case '1':  // 设置左速度
			uart1_put_str("\n\n\r设置上台速度：");
			do {
				uart1_put_str("\n\r速度左(-9999~09999): ");
				for(i=0; i<5; i++) {
					buf[i] = uart1_get_char();	
					uart1_put_char(buf[i]);
				}
				buf[5] = '\0';
				READYSPEEDL = atoi(buf);
			} while(READYSPEEDL < -9999 || READYSPEEDL > 9999);

			do {
				uart1_put_str("\n\r速度右(-9999~09999): ");
				for(i=0; i<5; i++) {
					buf[i] = uart1_get_char();	
					uart1_put_char(buf[i]);
				}
				buf[5] = '\0';
				READYSPEEDR = atoi(buf);
			} while(READYSPEEDR < -9999 || READYSPEEDR > 9999);
			uart1_put_str("\n\r设置成功！");
			break;

		case '2': // 设置上台时延
			do {
				uart1_put_str("\n\r上台时延(0000~9999): ");
				for(i=0; i<4; i++) {
					buf[i] = uart1_get_char();	
					uart1_put_char(buf[i]);
				}
				buf[4] = '\0';
				MSGOUP = atoi(buf);
			} while( MSGOUP > 9999 ||MSGOUP < 0 );
			uart1_put_str("\n\r设置成功！");

		break;

		default:
		break;
		}
	}
}

/**
	设置电机
**/
void setMotor()
{
	while(1) {
		do {
			uart1_put_str("\n\n\r电机选项：");
			uart1_put_str("\n\r1.设置电机ID");
			uart1_put_str("\n\r2.设置最大速度");
			uart1_put_str("\n\r3.设置转弯速度");
			uart1_put_str("\n\r4.设置安全参数");
			uart1_put_str("\n\r5.设置攻击参数");
			uart1_put_str("\n\r0.返回");
			uart1_put_str("\n\r-> ");
			select = uart1_get_char();
			uart1_put_char(select);
		} while( select != '1' && select != '2' && select != '3' && select != '4' 
				&& select != '5' && select != '0');
		if( select == '0') break;
		switch(select) {
		case '1':	// 设置电机ID
			uart1_put_str("\n\n\r设置电机ID：");
			do {
				uart1_put_str("\n\r电机左(00~99): ");
				for(i=0; i<2; i++) {
					buf[i] = uart1_get_char();	
					uart1_put_char(buf[i]);
				}
				buf[2] = '\0';
				NODE_L = atoi(buf);
			} while( NODE_L < 0 || NODE_L > 99);

			do {
				uart1_put_str("\n\r电机右(00~99): ");
				for(i=0; i<2; i++) {
					buf[i] = uart1_get_char();	
					uart1_put_char(buf[i]);
				}
				buf[2] = '\0';
				NODE_R = atoi(buf);
			} while(NODE_R < 0 || NODE_R > 99);
			uart1_put_str("\n\r设置成功！");
		break;

		case '2':	// 设置最大速度
			uart1_put_str("\n\n\r设置最大速度(00000 ~ 20000)：");
			do {
				for(i=0; i<5; i++) {
					buf[i] = uart1_get_char();
					uart1_put_char(buf[i]);
				}
				buf[5] = '\0';
				TOPSPEED = atoi(buf);
			} while(TOPSPEED < 0 || TOPSPEED > 20000);
			uart1_put_str("\n\r设置成功！");
		break;	
		
		case '3':	// 设置转弯速度
			uart1_put_str("\n\n\r设置转弯速度(00000 ~ 20000)：");
			do {
				for(i=0; i<5; i++) {
					buf[i] = uart1_get_char();
					uart1_put_char(buf[i]);
				}
				buf[5] = '\0';
				TURNSPEED = atoi(buf);
			} while(TURNSPEED < 0 || TURNSPEED > 20000);
			uart1_put_str("\n\r设置成功！");
		break;

		case '4':	// 设置安全参数
			uart1_put_str("\n\n\r设置安全参数：");
			uart1_put_str("\n\r安全速度(00000~20000)：");
			do {
				for(i=0; i<5; i++) {
					buf[i] = uart1_get_char();
					uart1_put_char(buf[i]);
				}
				buf[5] = '\0';
				SAFESPEED = atoi(buf);
			} while(SAFESPEED < 0 || SAFESPEED > 20000);

			uart1_put_str("\n\r安全加、减速度(00000~10000)：");
			do {
				for(i=0; i<5; i++) {
					buf[i] = uart1_get_char();
					uart1_put_char(buf[i]);
				}
				buf[5] = '\0';
				SAFERATION = atoi(buf);
			} while(SAFERATION < 0 || SAFERATION > 10000);

			uart1_put_str("\n\r设置成功！");

		break;

		case '5':	// 设置攻击参数
			uart1_put_str("\n\n\r设置攻击参数：");

			uart1_put_str("\n\r一档速度(00000~20000)：");
			do {
				for(i=0; i<5; i++) {
					buf[i] = uart1_get_char();
					uart1_put_char(buf[i]);
				}
				buf[5] = '\0';
				ATTACKGEAR1 = atoi(buf);
			} while(ATTACKGEAR1 < 0 || ATTACKGEAR1 > 20000);
				
			uart1_put_str("\n\r二档速度(00000~20000)：");
			do {
				for(i=0; i<5; i++) {
					buf[i] = uart1_get_char();
					uart1_put_char(buf[i]);
				}
				buf[5] = '\0';
				ATTACKGEAR2 = atoi(buf);
			} while(ATTACKGEAR2 < 0 || ATTACKGEAR2 > 20000);

			uart1_put_str("\n\r三档速度(00000~20000)：");
			do {
				for(i=0; i<5; i++) {
					buf[i] = uart1_get_char();
					uart1_put_char(buf[i]);
				}
				buf[5] = '\0';
				ATTACKGEAR3 = atoi(buf);
			} while(ATTACKGEAR3 < 0 || ATTACKGEAR3 > 20000);

			uart1_put_str("\n\r四档速度(00000~20000)：");
			do {
				for(i=0; i<5; i++) {
					buf[i] = uart1_get_char();
					uart1_put_char(buf[i]);
				}
				buf[5] = '\0';
				ATTACKGEAR4 = atoi(buf);
			} while(ATTACKGEAR4 < 0 || ATTACKGEAR4 > 20000);

			uart1_put_str("\n\r攻击加、减速度(00000~50000)：");
			do {
				for(i=0; i<5; i++) {
					buf[i] = uart1_get_char();
					uart1_put_char(buf[i]);
				}
				buf[5] = '\0';
				ATTACKRATION = atoi(buf);
			} while(ATTACKRATION < 0 || ATTACKRATION > 50000);

			uart1_put_str("\n\r设置成功！");
		break;

		}
	}
}
/**
	通过按键来获取比赛不同舞台的白色部分与黑色部分的灰度值
**/
void refresh_stage_AD()
{ 
	int i =0, j=0, k=0;

	int white[3][4];
	int black[3][4];
	int ad_port[3] = {AD_F, AD_L, AD_R};
	char* ad_loc[3] = {"\tF:", "\tL:", "\tR:"};
	int white_f[4];
	int white_l[4];
	int white_r[4];

	int black_f[4];
	int black_l[4];
	int black_r[4];

	int ad_white[3];
	int ad_black[3];
	int ad_red[3];
	int ad_wu[3];

	int t = 50;
	
	// 程序刚启动时按紧按键无效，等待按键松开
	while( read_adc2(AD_CHECK_IO)  < 512) 	
		_delay_ms(1000);	

	uart1_put_str("灰度取样程序启动...\n\r");
	
	uart1_put_str("\n\n\r白色区域：");
	for(j = 0; j < 4; j++) {
		uart1_put_str("\n\r白");
		uart1_put_int(j);
		uart1_put_str(":");
		for(i = 0; i < 3; i++) {
			uart1_put_str(ad_loc[i]);
			while(1) {
				if( read_adc2(AD_CHECK_IO) < 512 ) { _delay_ms(t); // 消抖
				if( read_adc2(AD_CHECK_IO) < 512 ) {
					white[i][j] = 0;
					k = 0;
					while(k < 10) {
						white[i][j] += read_adc2(ad_port[i]);
						_delay_ms(t);
						k ++;
					}
					white[i][j] /= 10;

					uart1_put_int(white[i][j]);

					while( read_adc2(AD_CHECK_IO) < 512);
					break;
				}}
			}
		}
	}

	uart1_put_str("\n\n\r武字区域：");

	uart1_put_str("\n\r武");
	uart1_put_str(":");
	for(i = 0; i < 3; i++) {
		uart1_put_str(ad_loc[i]);
		while(1) {
			if( read_adc2(AD_CHECK_IO) < 512 ) { _delay_ms(t); // 消抖
			if( read_adc2(AD_CHECK_IO) < 512 ) {
				ad_wu[i] = 0;
				k = 0;
				while(k < 10) {
					ad_wu[i] += read_adc2(ad_port[i]);
					_delay_ms(t);
					k ++;
				}
				ad_wu[i] /= 10;

				uart1_put_int(ad_wu[i]);

				while( read_adc2(AD_CHECK_IO) < 512);
				break;
			}}
		}
	}
	
	uart1_put_str("\n\n\r黑色区域：");
	for(j = 0; j < 4; j++) {
		uart1_put_str("\n\r黑");
		uart1_put_int(j);
		uart1_put_str(":");
		for(i = 0; i < 3; i++) {
			uart1_put_str(ad_loc[i]);
			while(1) {
				if( read_adc2(AD_CHECK_IO) < 512 ) { _delay_ms(t); // 消抖
				if( read_adc2(AD_CHECK_IO) < 512 ) {
					black[i][j] = 0;
					k = 0;
					while(k < 10) {
						black[i][j] += read_adc2(ad_port[i]);
						_delay_ms(t);
						k ++;
					}
					black[i][j] /= 10;

					uart1_put_int(black[i][j]);

					while( read_adc2(AD_CHECK_IO) < 512);
					break;
				}}
			}
		}
	}


	
	// 现在三个灰度传感器在黑色跟白色区域分别有四组取样值，存储在两个一维数组内
	// 每四组取样值均进行快速排序
	uart1_put_str("\n\r取样结束，正在进行快速排序...");

	for(i = 0; i < 3; i++) {
		quickSort(white[i], 0, 3);
		quickSort(black[i], 0, 3);
	}
	uart1_put_str("\n\r排序完成!");

	uart1_put_str("\n\r正在计算有效采样值...");
	
	// 去除最大值跟最小值，其余两个值求均值
	for(i = 0; i < 3; i++) {
		ad_white[i] = (white[i][1] + white[i][2]) / 2;
		ad_black[i] = (black[i][1] + black[i][2]) /2;
	}
	
	uart1_put_str("\n\r计算完毕！");
	
	uart1_put_str("\n\n\r正在计算灰度偏置值...");

	AD_ADJUST_L = ( (ad_white[0] - ad_white[1]) + (ad_black[0] - ad_black[1]) 
						+ (ad_wu[0] - ad_wu[1]) ) / 3;
	AD_ADJUST_R = ( (ad_white[0] - ad_white[2]) + (ad_black[0] - ad_black[2]) 
						+ (ad_wu[0] - ad_wu[2]) ) / 3;

	uart1_put_str("\n\r计算完毕!");
	
	AD_WU = (ad_wu[0] + ad_white[0]) /2;
	
	uart1_put_str("\n\n\r写EEPROM中...");
	
	AD_WHITE = ad_white[0];
	AD_BLACK = ad_black[0];

	eeprom_write_word(AD_WHITE_ADD, AD_WHITE);
	eeprom_write_word(AD_BLACK_ADD, AD_BLACK);
	eeprom_write_word(AD_WU_ADD, AD_WU);
	eeprom_write_word(AD_ADJUST_L_ADD, AD_ADJUST_L);
	eeprom_write_word(AD_ADJUST_R_ADD, AD_ADJUST_R);
	
	uart1_put_str("\n\r写入成功！");


	uart1_put_str("\n\n\r采样结束！\n\r");
}

/**
	从eeprom中读取参数
	@parameter: 
		ifbak 是否是备份还原操作（ifbak == EEP_BAK时，从备份地址读取或保存，否则从普通地址读取）
		rOw	  读写标志
**/
void eeprom_rOw_par(unsigned char rOw)
{
	switch(rOw) {
	case EEP_R:
		AD_WU = eeprom_read_word(AD_WU_ADD);
		AD_WHITE = eeprom_read_word(AD_WHITE_ADD);
		AD_BLACK = eeprom_read_word(AD_BLACK_ADD);
		AD_ADJUST_L = eeprom_read_word(AD_ADJUST_L_ADD);
		AD_ADJUST_R = eeprom_read_word(AD_ADJUST_R_ADD);
		CORNERRATION = eeprom_read_word(CORNERRATION_ADD);
		MODE = eeprom_read_word(MODE_ADD);
		NODE_L = eeprom_read_word(NODE_L_ADD);
		NODE_R = eeprom_read_word(NODE_R_ADD);
		ATTACKGEAR4 = eeprom_read_word(ATTACKGEAR4_ADD);
		ATTACKGEAR3 = eeprom_read_word(ATTACKGEAR3_ADD);
		ATTACKGEAR2 = eeprom_read_word(ATTACKGEAR2_ADD);
		ATTACKGEAR1 = eeprom_read_word(ATTACKGEAR1_ADD);
		ATTACKRATION = eeprom_read_word(ATTACKRATION_ADD);
		SAFESPEED = eeprom_read_word(SAFESPEED_ADD);
		SAFERATION = eeprom_read_word(SAFERATION_ADD);
		TOPSPEED = eeprom_read_word(TOPSPEED_ADD);
		STATECYCLE = eeprom_read_word(STATECYCLE_ADD);
		MEMORYCYCLE_INIT = eeprom_read_word(MEMORYCYCLE_INIT_ADD);
		TURNSPEED = eeprom_read_word(TURNSPEED_ADD);
		MSGOUP = eeprom_read_word(MSGOUP_ADD);
		READYSPEEDL = eeprom_read_word(READYSPEEDL_ADD);
		READYSPEEDR = eeprom_read_word(READYSPEEDR_ADD);
		SPEEDPUSH = eeprom_read_word(SPEEDPUSH_ADD);
		MEMORYCYCLE_PUSH = eeprom_read_word(MEMORYCYCLE_PUSH_ADD);
		break;

	case EEP_W:
		eeprom_write_word(AD_WU_ADD, AD_WU);
		eeprom_write_word(AD_WHITE_ADD, AD_WHITE);
		eeprom_write_word(AD_BLACK_ADD, AD_BLACK);
		eeprom_write_word(AD_ADJUST_L_ADD, AD_ADJUST_L );
		eeprom_write_word(AD_ADJUST_R_ADD, AD_ADJUST_R );
		eeprom_write_word(CORNERRATION_ADD, CORNERRATION );
		eeprom_write_word(MODE_ADD, MODE);	
		eeprom_write_word(NODE_L_ADD, NODE_L);
		eeprom_write_word(NODE_R_ADD, NODE_R);
		eeprom_write_word(ATTACKGEAR4_ADD, ATTACKGEAR4);
		eeprom_write_word(ATTACKGEAR3_ADD, ATTACKGEAR3);
		eeprom_write_word(ATTACKGEAR2_ADD, ATTACKGEAR2);
		eeprom_write_word(ATTACKGEAR1_ADD, ATTACKGEAR1);
		eeprom_write_word(ATTACKRATION_ADD, ATTACKRATION);
		eeprom_write_word(SAFESPEED_ADD, SAFESPEED);
		eeprom_write_word(SAFERATION_ADD, SAFERATION);
		eeprom_write_word(TOPSPEED_ADD, TOPSPEED);
		eeprom_write_word(STATECYCLE_ADD, STATECYCLE);
		eeprom_write_word(MEMORYCYCLE_INIT_ADD, MEMORYCYCLE_INIT);
		eeprom_write_word(TURNSPEED_ADD, TURNSPEED);
		eeprom_write_word(MSGOUP_ADD, MSGOUP);
		eeprom_write_word(READYSPEEDL_ADD, READYSPEEDL);
		eeprom_write_word(READYSPEEDR_ADD, READYSPEEDR);
		eeprom_write_word(SPEEDPUSH_ADD, SPEEDPUSH);
		eeprom_write_word(MEMORYCYCLE_PUSH_ADD, MEMORYCYCLE_PUSH);
		break;
	}	
}

/**
	快速排序
**/
void quickSort(int *a, int i, int j) 
{
	int m, n, temp;
	int k;
	m = i;
	n = j;
	k = a[(i+j)/2];
	do {
		while( a[m]<k && m<j ) m++;
		while( a[n]>k && n>i ) n--;
		if( m <= n ) {
			temp = a[m];
			a[m] = a[n];
			a[n] = temp;
			m++;
			n--;
		}
	} while(m <= n);
	if(m < j) quickSort(a, m, j);
	if(n > j) quickSort(a, i, n);
}
