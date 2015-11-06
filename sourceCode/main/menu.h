#ifndef _MENU_H_
#define _MENU_H_


/**
	EEPROM 操作标志
**/

#define EEP_R 0				// 读操作
#define EEP_W 1				// 写操作

#define AD_CHECK_IO 4		// 按键插入口ID（AD）

/**
	各参数的存储地址
**/
#define AD_WU_ADD			0x24
#define AD_MAXGAP_ADD		0x26
#define minGreyTrack0_ADD	0x28
#define minGreyTrack1_ADD	0x2a
#define minGreyTrack2_ADD	0x2c
#define AD_ADJUST_L_ADD 	0x2e
#define AD_ADJUST_R_ADD 	0x30
#define READYSPEEDL_ADD		0x32
#define READYSPEEDR_ADD		0x34
#define MODE_ADD			0x3c
#define NODE_L_ADD			0x3e
#define NODE_R_ADD			0x40
#define ATTACKGEAR4_ADD		0x42
#define ATTACKGEAR3_ADD		0x44
#define ATTACKGEAR2_ADD		0x46
#define ATTACKGEAR1_ADD		0x48
#define ATTACKRATION_ADD	0x4a
#define SAFESPEED_ADD		0x4c
#define SAFERATION_ADD		0x4e
#define SPEEDPUSH_ADD		0x50	
#define MEMORYCYCLE_PUSH_ADD 0x52
#define TOPSPEED_ADD		0x5a
#define STATECYCLE_ADD		0x5c
#define MEMORYCYCLE_INIT_ADD 0x5e
#define TURNSPEED_ADD		0x60
#define AD_WHITE_ADD		0x62
#define AD_BLACK_ADD		0x64
#define CORNERRATION_ADD	0x66
#define MSGOUP_ADD			0x68


/**
	擂台环境
**/
int AD_WU;					// 白色武字的灰度值
int AD_MAXGAP;				// 踏入红色灰度突变 

int AD_WHITE;				// 白色区域灰度
int AD_BLACK;				// 黑色区域灰度

int CORNERRATION;			// 角落占半径比

int minGreyTrack0;			// 轨道0最小灰度
int minGreyTrack1;			// 轨道1最小灰度
int minGreyTrack2;			// 轨道2最小灰度

int AD_ADJUST_L;			// 灰度左偏置
int AD_ADJUST_R;			// 灰度右偏置

/**
	攻击参数
**/

int TOPSPEED;				// 最大速度
int ATTACKGEAR4;			// 4档
int ATTACKGEAR3;			// 3档	
int ATTACKGEAR2;			// 2档
int ATTACKGEAR1;			// 1档
int ATTACKRATION;			// 加减速度
int TURNSPEED;				// 旋转速度

unsigned char MODE;			// 工作模式

/**
	安全参数
**/
int SAFESPEED;				// 安全速度
int SAFERATION;				// 安全加速度


/**
	 驱动板地址 
**/
int NODE_L;					// 左轮驱动板node			
int NODE_R;					// 右轮驱动板node


/**
	时间参数
**/
unsigned int STATECYCLE; 		// 状态周期（传感器刷新间隔）
unsigned int MEMORYCYCLE;		// 记忆周期（当前无敌人，保留上一次敌人位置信息的时间）
unsigned int MEMORYCYCLE_INIT;	// 初始记忆周期，根据实际情况，在此基础上增加或减少记忆周期

/*
 * 上台参数
 */
int READYSPEEDL;
int READYSPEEDR;
unsigned int MSGOUP;

/*
 *	推棋子参数
 */
unsigned int SPEEDPUSH;
unsigned int MEMORYCYCLE_PUSH;

/**
	函数声明
**/	
void menu(void);						//	主页面程序（原理：串口打印、超级终端）
void refresh_stage_AD(void);			//  灰度辅助采样
void quickSort(int *a, int i, int j); 	//	快速排序
void eeprom_rOw_par(unsigned char rOw); //	参数读写程序

#endif
