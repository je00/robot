#ifndef	_INIT_H
#define	_INIT_H

#define SET_1(a,b) a |= (1<<b)
#define CLE_0(a,b) a &=~ (1<<b)


/**
	 小车结构体 
**/
struct VEHICLE
{	
	unsigned char dir;				// 朝向
	unsigned char track;			// 轨道
	unsigned char flagRed;			// 红色区域标志位
	unsigned char locEnemy; 		// 敌人的位置
	unsigned char locEnemyLast;		// 上一次敌人的位置
	unsigned char locFriend;		// 友方的位置
} vehicle; 


/**
	函数声明
**/
void init_device(void);		// 初始化AVR资源
void globalVarInit(void);	// 全局变量初始化(大部分从eeprom中读取)
void ready(void);			// 准备完毕，遮挡右侧红外走上擂台
void scoopLaydown(void);	// 放下铲子

#endif
