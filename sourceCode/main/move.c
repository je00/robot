/**
	
**/

#include "INCLUDES.h"


/**
	������
	@author: Ting
**/

#define PUSHCHESSGEAR1 800
#define PUSHCHESSGEAR2 1000
#define PUSHCHESSRATION 2000
void pushChess()
{
	init_device();		// ��ʼ��avr��Դ
	_delay_ms(1000);	// ȷ����ȫ����
	ready();			// Ԥ�����ȴ��ڵ��Һ��⴫����
	int i = 0;
	_delay_ms(1200);
	

/*	while(sensor.io_bld == 0) {
		switch(sensor.edgeCode & 0x0c) {		// ��������Ե���
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
	���ű�Ե��ȷ���˵����䣬ǰ���ǵ�ǰ���ڱ�Ե����
	@parameter: 
				rOl : ѡ���������Ҳ��ر�Ե 
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








