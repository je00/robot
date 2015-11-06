#ifndef _CODE_H_
#define _CODE_H_

/**
	1、轨道编码（灰度传感器、vehicle.track）
	2、00(无效) --(front) --(left) --(right)
	3、track0: 00	track1: 01	track2: 10	`corner: 11
	@author: Ting
**/
#define	IN_TRACK0 0x00	// 处于轨道0 (00 00 00 00）
#define IN_TRACK1 0x15 	// 处于轨道1 (00 01 01 01)
#define IN_TRACK2 0x2A	// 处于轨道2 (00 10 10 10)
#define IN_CORNER 0x3f	// 处于角落	 (00 11 11 11)

// 从一个轨道进入另一个轨道，直接进入（前轮已进入，后轮未进入）
#define TRACK0_TRACK1_STRI 0x10	// 从轨道0进入轨道1 (00 01 00 00)
#define TRACK1_TRACK2_STRI 0x25	// 从轨道1进入轨道2 (00 10 01 01)
#define TRACK2_CORNER_STRI 0x3A	// 从轨道2进入角落  (00 11 10 10)

#define CORNER_TRACK2_STRI 0x2F	// 从角落进入轨道2  (00 10 11 11)
#define TRACK2_TRACK1_STRI 0x1A	// 从轨道2进入轨道1 (00 01 10 10)
#define TRACK1_TRACK0_STRI 0x05	// 从轨道1进入轨道0 (00 00 01 01)

// 从一个轨道进入另一个轨道，右侧先进入（右轮进入，左轮停留原轨道）
#define TRACK0_TRACK1_SiR 0x11	// 从轨道0进入轨道1 (00 01 00 01)
#define TRACK1_TRACK2_SiR 0x26	// 从轨道1进入轨道2 (00 10 01 10)
#define TRACK2_CORNER_SiR 0x3B	// 从轨道2进入角落  (00 11 10 11)

#define CORNER_TRACK2_SiR 0x2E	// 从角落进入轨道2  (00 10 11 10)
#define TRACK2_TRACK1_SiR 0x19	// 从轨道2进入轨道1 (00 01 10 01)
#define TRACK1_TRACK0_SiR 0x04	// 从轨道1进入轨道0 (00 00 01 00)

// 从一个轨道进入另一个轨道，左侧先进入（左轮进入，右轮停留原轨道）
#define TRACK0_TRACK1_SiL 0x14	// 从轨道0进入轨道1 (00 01 01 00)
#define TRACK1_TRACK2_SiL 0x29	// 从轨道1进入轨道2 (00 10 10 01)
#define TRACK2_CORNER_SiL 0x3E	// 从轨道2进入角落  (00 11 11 10)

#define CORNER_TRACK2_SiL 0x2B	// 从角落进入轨道2  (00 10 10 11)
#define TRACK2_TRACK1_SiL 0x16	// 从轨道2进入轨道1 (00 01 01 10)
#define TRACK1_TRACK0_SiL 0x01	// 从轨道1进入轨道0 (00 00 00 01)


/**
	1、红色区域标志位（trackCode的10、9、8位），右移8位后再判断
	2、00 00 0(无效) -(front) -(left) -(right)
	3、0：不处于红色区域 	1：处于红色区域
	@author: Ting
**/
#define IN_MIDDLE 		0x07	// 整体处于红色区域			(111)			
#define FACE_MIDDLE		0x04	// 前轮进入红色区域			(100)
#define BACK_MIDDLE		0x03	// 两个后轮进入红色区域		(011)	
#define LEFT_MIDDLE		0x06	// 前轮与左轮进入红色区域	(110)
#define RIGHT_MIDDLE	0x05	// 前轮和右轮进入红色区域	(101)
#define BALE_MIDDLE 	0x02	// 只有左轮进入红色区域		(010)
#define BARI_MIDDLE		0x01 	// 只有右轮进入红色区域		(001)

/**
	1、普通红外传感器（检测敌人）编码 sensor.detectCode
	2、-(fl)-(l)-(bl)-(b)-(br)-(r)-(fr)-(f)
	@author: Ting
**/
#define NO_ENEMY		0xff		// 检测不到敌人
#define FACE_ENEMY 		0xfe		// 正对敌人
#define BACK_ENEMY  	0xef		// 背对敌人
#define LEFT_ENEMY		0xbf		// 敌人在左侧
#define RIGHT_ENEMY		0xfb		// 敌人在右侧
#define	FRRI_ENEMY		0xfd		// 敌人在右前方	
#define FRLE_ENEMY		0x7f		// 敌人在左前方
#define BARI_ENEMY		0xf7		// 敌人在右后方
#define BALE_ENEMY		0xdf		// 敌人在左后方

/**
	检测边缘红外传感器二进制编码
		 前
	位0       位3（右前边缘检测）

	位1       位2
	@author: Ting
**/
#define BACK_EDGE	0x06		// 背面面向擂台边缘
#define FACE_EDGE	0x09		// 正面面向擂台边缘
#define LEFT_EDGE	0x03		// 左侧面向擂台边缘
#define RIGHT_EDGE	0x0c		// 右侧面向擂台边缘
#define FRRI_EDGE	0x08		// 右前方是擂台边缘
#define FRLE_EDGE	0x01		// 左前方是擂台边缘
#define BARI_EDGE	0x04		// 右后方是擂台边缘
#define BALE_EDGE	0x02		// 左后方是擂台边缘
#define FRLE_RING	0x0E		// 只有左前方在擂台上
#define FRRI_RING	0x07		// 只有右前方在擂台上 	
#define BALE_RING	0x0D		// 只有左后方在擂台上
#define BARI_RING	0x0B		// 只有右后方在擂台上

#endif
