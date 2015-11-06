/**
	
**/

#include "INCLUDES.h"


/**
	推棋子
	@author: Ting
**/

#define PUSHCHESSGEAR1 800
#define PUSHCHESSGEAR2 1000
#define PUSHCHESSRATION 2000
void pushChess()
{
	init_device();		// 初始化avr资源
	_delay_ms(1000);	// 确保完全启动
	ready();			// 预备，等待遮挡右红外传感器
	int i = 0;
	_delay_ms(1200);
	

/*	while(sensor.io_bld == 0) {
		switch(sensor.edgeCode & 0x0c) {		// 屏蔽左侧边缘检测
		case 0x00:
			setSpeed(-1*PUSHCHESSGEAR2, -1*PUSHCHESSGEAR1, PUSHCHESSRATION, PUSHCHESSRATION);
		break;	

		case FRRI_EDGE:
			turnOnSpeed(-1*PUSHCHESSGEAR1, PUSHCHESSRATION, PUSHCHESSRATION);
		break;

		case BARI_EDGE:
			turnOnSpeed(PUSHCHESSGEAR1, PUSHCHESSRATION, PUSHCHESSRATION);
		break;

		case RIGHT_EDGE:
			setSpeed(-1*PUSHCHESSGEAR1, -1*PUSHCHESSGEAR2, PUSHCHESSRATION, PUSHCHESSRATION);
		break;
		}
	}
	goOnSpeed(0, PUSHCHESSRATION, PUSHCHESSRATION); 
	_delay_ms(1000);
	while(sensor.io_f == 1) {
		turnOnSpeed(-1*500, 2000, 2000);
	}
	goOnSpeed(0, 0, 0); 
	_delay_ms(1000);
	while(sensor.io_frd == 0 && sensor.io_fld == 0) {
		if(sensor.io_f == 0)
			goOnSpeed(2000, 2000, 2000);
		else {
			turnOnSpeed(500, 2000, 2000);
			delayms(200);
			
		}
	}
	goOnSpeed(0, 4000, 4000);
	*/

}

/**
	沿着边缘精确后退到角落，前提是当前处于边缘附近
	@parameter: 
				rOl : 选择左侧或者右侧沿边缘 
**/
#define R 1
#define L 0
void backToCorner(unsigned char rOl) {
	switch(rOl) {
	case R: 
		;
	case L:
		;
	}
}








