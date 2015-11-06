/*
 * 对战模式相关策略
 * @Author: Ting
 * @date: 13th July, 2014
 *@history：
 *	1、修改应对策略，并将不同方位遇到敌人的情况各自整理为一个函数
 *	2、改写noEnemy()函数，增加记忆周期的概念，
 *		检测不到敌人则将短暂记忆上次遇到敌人的方位，采取相应策略
 *		@corroctor: Ting
 *		@date: 31th July, 2014
 *	3、优化走向中心函数gotoMiddle()
 *		@corroctor:	Ting
 *		@date: 4th April, 2014
 */

#include "INCLUDES.h"

/*
 * 走进中心武字区域
 */
void goToMiddle()
{ 
	switch(vehicle.flagRed) {
	case IN_MIDDLE: 	// 在武字中		
		goOnSpeed(0);				// 停止
		break;

	case FACE_MIDDLE:	// 面对武字
		goOnSpeed(SAFESPEED);			// 前进
		break;

	case BACK_MIDDLE:	// 背对武字
		goOnSpeed(-1*SAFESPEED);		// 后退
		break;
	
	case BALE_MIDDLE:	// 左后武字
	case LEFT_MIDDLE:	// 左侧武字
		setSpeed(0, 2*SAFESPEED);
		break;
	
	case BARI_MIDDLE:	// 右后武字
	case RIGHT_MIDDLE:	// 右侧武字
		setSpeed(2*SAFESPEED, 0);
		break;

	default: 		// 不在武字中尽量向武字靠近
		switch(vehicle.dir) {
		case BACK_EDGE:		// 面对中心
			switch(vehicle.track) {
			case TRACK2_TRACK1_SiL:	
			case TRACK1_TRACK0_SiL:	
				turnOnSpeed(-1*SAFESPEED);
				break;
			
			case TRACK2_TRACK1_SiR:	
			case TRACK1_TRACK0_SiR:
				turnOnSpeed(SAFESPEED);
				break;

			default:
				goOnSpeed(SAFESPEED);
			}
			break;

		case FACE_EDGE:
			switch(vehicle.track) {
			case TRACK1_TRACK2_SiL:	
			case TRACK0_TRACK1_SiL:	
				turnOnSpeed(-1*SAFESPEED);
				break;
			
			case TRACK1_TRACK2_SiR:	
			case TRACK0_TRACK1_SiR:
				turnOnSpeed(SAFESPEED);
				break;

			default:
				goOnSpeed(-1*SAFESPEED);
			}
			break;

		case RIGHT_EDGE:
			turnOnSpeed(SAFESPEED);
			break;

		case LEFT_EDGE:
			turnOnSpeed(-1*SAFESPEED);
		}
	}
}


/*
 * 没有敌人的情况
 */
void noEnemy() 
{	
	// 分析上次是在什么方位遇到敌人
	switch(vehicle.locEnemyLast) {
	
	case NO_ENEMY:
	// 最近一个记忆周期里没有遇到过敌人，回去擂台中央
		MEMORYCYCLE = MEMORYCYCLE_INIT;
		goToMiddle();
	//	walkInTrack1();
		break;
	
	CASE_FACE_ENEMY
	// 敌人从机器人正前方逃脱了, 可能是棋子在传感器死角，或敌人掉下去了
	// 加长记忆周期，延续上次的攻击
		MEMORYCYCLE = MEMORYCYCLE_INIT; // 记忆周期加长1s
		fight_FACE_ENEMY();
		break; 
	
	CASE_BACK_ENEMY
	// 敌人上次在我后面
		noEnemy_BACK_ENEMY();
		break;

	CASE_FRLE_ENEMY
	// 敌人上次在我左前方
	CASE_LEFT_ENEMY
	// 敌人上次在我左侧
	CASE_BALE_ENEMY
	// 敌人上次在我左后方
		noEnemy_LEFT_ENEMY();
		break;

	CASE_RIGHT_ENEMY
	// 敌人上次在我右侧
	CASE_FRRI_ENEMY
	// 敌人上次在我右前方
	CASE_BARI_ENEMY
	// 敌人上次在我右后方
		noEnemy_RIGHT_ENEMY();
		break;
	
	default:
		if(sensor.io_f == 0)	
			vehicle.locEnemyLast = FACE_ENEMY;
		else if(sensor.io_fr == 0)
			vehicle.locEnemyLast = FRRI_ENEMY;
		else if(sensor.io_fl == 0)
			vehicle.locEnemyLast = FRLE_ENEMY;
		else if(sensor.io_l == 0)
			vehicle.locEnemyLast = LEFT_ENEMY;
		else if(sensor.io_r == 0)
			vehicle.locEnemyLast == RIGHT_ENEMY;
		else if(sensor.io_bl == 0)
			vehicle.locEnemyLast = BALE_ENEMY;
		else if(sensor.io_br == 0)
			vehicle.locEnemyLast = BARI_ENEMY;
		else if(sensor.io_b == 0)
			vehicle.locEnemyLast = BACK_ENEMY;
		break;
	}
}


/*
 *	没有敌人：上一次背对敌人
 */
void noEnemy_BACK_ENEMY()
{	
	switch(vehicle.dir) {

	case BACK_EDGE:	// 面对中心
		switch(vehicle.track) {
		// 边缘位置，敌人可能是因为掉下去才不见的，往前走一走
		CASE_CORNER
		CASE_TRACK2
			goOnSpeed(ATTACKGEAR2);
			break;

		default:
			turnOnSpeed(3*TURNSPEED);
			break;
		}		
		break;

	case FACE_EDGE:	// 背对中心
		switch(vehicle.track) {
		//  边缘位置，敌人可能暂时走掉了，快速退出边缘
		CASE_CORNER
			goOnSpeed(-1*TOPSPEED);
			break;

		default:
			turnOnSpeed(3*TURNSPEED);
			break;
		}

	case LEFT_EDGE:	// 左侧中心
		turnOnSpeed(-3*TURNSPEED);
		break;

	case RIGHT_EDGE:// 右侧中心
		turnOnSpeed(3*TURNSPEED);
		break;
	}
}

/*
 * 没有敌人：上一次敌人在左侧
 */
void noEnemy_LEFT_ENEMY() {
	switch(vehicle.track) {
	CASE_CORNER	// 在角落
		switch(vehicle.dir) {
		case BACK_EDGE: // 面对中心,离开角落
			goOnSpeed(ATTACKGEAR4);
			break;	 
		case FACE_EDGE:	// 背对中心，离开角落
			goOnSpeed(-1*ATTACKGEAR4);
			break;	
		case LEFT_EDGE: // 右侧中心,敌人可能是掉下去，右转朝向中心
			turnOnSpeed(TURNSPEED);
			break;
		case RIGHT_EDGE:// 左侧中心,旋转面向敌人
			turnOnSpeed(-1*TURNSPEED);
			break;
		}
		break;
	
	// 直接左转找敌人
	default:
		turnOnSpeed(-2*TURNSPEED);
	}
	
}

/* 
 * 没有敌人：上一次敌人在右侧
 */
void noEnemy_RIGHT_ENEMY() {
	switch(vehicle.track) {
	CASE_CORNER	// 在角落
		switch(vehicle.dir) {
		case BACK_EDGE: // 面对中心,离开角落
			goOnSpeed(ATTACKGEAR4);
			break;	 
		case FACE_EDGE:	// 背对中心，离开角落
			goOnSpeed(-1*ATTACKGEAR4);
			break;	
		case LEFT_EDGE: // 右侧中心,旋转面向敌人
			turnOnSpeed(TURNSPEED);
			break;
		case RIGHT_EDGE:// 左侧中心,敌人可能是掉下去，左转朝向中心
			turnOnSpeed(-1*TURNSPEED);
			break;
		}
		break;
	
	// 直接右转找敌人
	default:
		turnOnSpeed(2*TURNSPEED);
	}
	
}

/* 
 * 对战程序，包括根据状态做出动作、走向擂台中心、陷入边缘危机处理
 * 调用方法：int main() { init_device(); fight(); }
 */
void fight() 
{

	// 开启检测边缘中断，使用上升沿触发
	cli();
	EICRB |= (1<<ISC71) |(1<<ISC70) |(1<<ISC61) |(1<<ISC60) 
				|(1<<ISC51) |(1<<ISC50) |(1<<ISC41) |(1<<ISC40) ;
	EIMSK |=(1<<INT7) |(1<<INT6) |(1<<INT5) |(1<<INT4); 
	sei(); 

	while(1) {
		txData();		
		printData();
		uart1_put_char(0x0d);
		switch(vehicle.locEnemy) {
		case NO_ENEMY:	// 未发现敌人
			noEnemy();
			break;

		CASE_FACE_ENEMY	// 面对敌人
			fight_FACE_ENEMY();
			break;

		CASE_BACK_ENEMY	// 背对敌人
			fight_BACK_ENEMY();
			break;

		CASE_LEFT_ENEMY // 左侧敌人
			fight_LEFT_ENEMY();
			break;
	
		CASE_RIGHT_ENEMY // 右侧敌人
			fight_RIGHT_ENEMY();
			break;

		CASE_FRRI_ENEMY	 // 右前敌人
			fight_FRRI_ENEMY();
			break;	

		CASE_FRLE_ENEMY	// 左前敌人
			fight_FRLE_ENEMY();
			break;	

		CASE_BALE_ENEMY // 左后敌人
			fight_BALE_ENEMY();	
		break;

		CASE_BARI_ENEMY // 右后敌人
			fight_BARI_ENEMY();
			break;

		default: // 汇总当多个方位检查到敌人的情况
			if(sensor.io_f == 0)	
				vehicle.locEnemy = FACE_ENEMY;
			else if(sensor.io_fr == 0)
				vehicle.locEnemy = FRRI_ENEMY;
			else if(sensor.io_fl == 0)
				vehicle.locEnemy = FRLE_ENEMY;
			else if(sensor.io_l == 0)
				vehicle.locEnemy = LEFT_ENEMY;
			else if(sensor.io_r == 0)
				vehicle.locEnemy == RIGHT_ENEMY;
			else if(sensor.io_bl == 0)
				vehicle.locEnemy = BALE_ENEMY;
			else if(sensor.io_br == 0)
				vehicle.locEnemy = BARI_ENEMY;
			else if(sensor.io_b == 0)
				vehicle.locEnemy = BACK_ENEMY;
			break;
		}
	}
}


/*
 *	对战：面对敌人
 */
void fight_FACE_ENEMY()
{
	switch(vehicle.dir) {
	case BACK_EDGE:	// 面对中心
	// 敌人在中心方向，反正是往中心冲，冲！
		goOnSpeed(ATTACKGEAR4);		// 四档攻击
	break;

	case FACE_EDGE:	// 背对中心
		switch(vehicle.track) {
		// 在轨道0，好安全，冲啊!
		CASE_TRACK0
			goOnSpeed(ATTACKGEAR3);
			break;
		// 开始进入第一轨道，太快可能会刹不住车，换二档吧
		CASE_TRACK1
			goOnSpeed(ATTACKGEAR2);
			break;
		// 开始进入第二轨道，有点危险，只用一档攻击
		CASE_TRACK2
			goOnSpeed(ATTACKGEAR1); // 一档攻击
			break;
		// 已触碰到角落了，很危险，让敌人自己掉下去吧，走为上计
		CASE_CORNER
			goOnSpeed(-1*TOPSPEED);	// 快速后退
			break;
		}
		break;
			
	case LEFT_EDGE: // 右侧中心
		switch(vehicle.track) {
		// 在0、1轨道比较安全，使用三档
		CASE_TRACK0
		CASE_TRACK1
			goOnSpeed(ATTACKGEAR3);
			break;
		// 第二轨道可能刹不住车
		CASE_TRACK2
			goOnSpeed(ATTACKGEAR2);
			break;
		// 碰到角落了，为防止掉下去，往左转面对边缘，有机会再出击
		CASE_CORNER
			turnOnSpeed(ATTACKGEAR3);
		// 矛盾的情况，不可能发生
		default:
			break;
		}
		break;

	case RIGHT_EDGE: // 左侧中心
		switch(vehicle.track) {
		// 在第0、1轨道活动范围较广，开启三档
		CASE_TRACK0
		CASE_TRACK1
			goOnSpeed(ATTACKGEAR3);
			break;
		// 第2轨道有点危险，使用二档
		CASE_TRACK2
			goOnSpeed(ATTACKGEAR2);
			break;
		// 碰到角落了，为防止掉下去，往右转面对边缘，有机会再出击
		CASE_CORNER
			turnOnSpeed(-1*TURNSPEED);
			break;
		// 矛盾的情况，不可能发生
		default:
			break;
		}
		break;
	}
}

/*
 *	对战：敌人在背后
 */
void fight_BACK_ENEMY()
{
	switch(vehicle.dir) {
	case BACK_EDGE:	// 面对中心
		// 边跑边转弯
		setSpeed(ATTACKGEAR2, ATTACKGEAR4); 				// 差速前进 + 急转弯
		break;

	case FACE_EDGE:	// 背对中心
		switch(vehicle.track) {
	
		// 在轨道0中活动范围较广，逃跑
		case IN_TRACK0:
			setSpeed(ATTACKGEAR2, ATTACKGEAR4);			// 差速前进 + 急转弯
			break;

		// 在轨道1中直接转弯
		CASE_TRACK1
			turnOnSpeed(TURNSPEED);						// 向右旋转
			break;
					
		// 逃不了，抵抗!
		default:
			goOnSpeed(-1*TOPSPEED);  
			break;
		}
	break;
				
	case LEFT_EDGE:	// 右侧中心
		switch(vehicle.track) {
			
		// 处于边缘地带，很可能冲下去，直接转弯
		CASE_TRACK2
		CASE_CORNER
			turnOnSpeed(TURNSPEED);						// 向右旋转
			break;

		default: // 其他情况
			setSpeed(ATTACKGEAR4, ATTACKGEAR2);				// 向前推进 + 右急转弯
			break;
		}
	break;

	case RIGHT_EDGE: // 左侧中心
		switch(vehicle.track) {

		// 处于边缘地带，很可能冲下去，直接转弯
		CASE_TRACK2
		CASE_CORNER
			turnOnSpeed(-1*TURNSPEED);			
			break;

		default: // 其他情况
			setSpeed(ATTACKGEAR2, ATTACKGEAR4);			// 向前推进 + 左急转弯
			break;
		}
	break;
	}
}

/*
 *	对战：敌人在左侧
 *	思想：尽量闪开敌人
 */
void fight_LEFT_ENEMY()
{
	switch(vehicle.dir) {
	case BACK_EDGE:	// 面对中心
	// 往前冲，闪开敌人，同时扭转方向
		setSpeed(ATTACKGEAR2, ATTACKGEAR4);	
		break;

	case FACE_EDGE:	// 背对中心
	// 往后冲，闪开敌人
		setSpeed(-1*ATTACKGEAR4, -1*ATTACKGEAR2);
		break;

	case LEFT_EDGE:	// 右侧中心
		switch(vehicle.track) {
		// 第0、1轨道，敌人处于边缘方向，我方较有利，调整攻击面
		CASE_TRACK0
		CASE_TRACK1
			setSpeed(-1*ATTACKGEAR4, -1*ATTACKGEAR2);		// 差速后退 + 急转弯
			break;

		// 在靠近边缘位置，敌人可能已经掉下去了，被冲撞的可能性不大，左转继续攻击
		CASE_TRACK2
		CASE_CORNER
			turnOnSpeed(-1*TURNSPEED);
			break;
		}
		break;
			
	case RIGHT_EDGE: // 左侧中心、左侧敌人（我方不利）
		switch(vehicle.track) {
		// 闪开敌人，同时往里靠
		CASE_TRACK0
		CASE_TRACK1
		CASE_TRACK2
			setSpeed(ATTACKGEAR2, ATTACKGEAR4);			// 差速前进 + 左急转弯
			break;

		// 在角落里，往前冲可能冲下去了，左转攻击
		default:
			turnOnSpeed(-1*TURNSPEED);
			break;
		}
		break;
	}
}

/*
 *	对战：敌人在右侧
 */
void fight_RIGHT_ENEMY()
{
	switch(vehicle.dir) {
	case BACK_EDGE:	// 面对中心
	// 往前冲，闪开敌人
		setSpeed(ATTACKGEAR4, ATTACKGEAR2);			// 差速前进 + 急转弯
		break;

	case FACE_EDGE:	// 背对中心
	// 往后冲，闪开敌人
		setSpeed(-1*ATTACKGEAR2, -1*ATTACKGEAR4);		// 差速后退 + 急转弯
		break;

	case RIGHT_EDGE: // 左侧中心
		switch(vehicle.track) {

		// 第0、1轨道，敌人处于边缘方向，我方较有利，调整攻击面
		CASE_TRACK0
		CASE_TRACK1
			setSpeed(-1*ATTACKGEAR2, -1*ATTACKGEAR4);	// 差速后退 + 急转弯
			break;

		// 在靠近边缘位置，敌人可能已经掉下去了，被冲撞的可能性不大，右转转继续攻击
		default:
			turnOnSpeed(TURNSPEED);
			break;
		}
		break;

	case LEFT_EDGE:	// 右侧中心
		switch(vehicle.track) {			
			// 闪开敌人，同时往里靠
		CASE_TRACK0
		CASE_TRACK1
			setSpeed(ATTACKGEAR4, ATTACKGEAR2);		// 差速前进 + 右急转弯
			break;

		// 在角落里，往前冲可能冲下去了，右转攻击
		default:
			turnOnSpeed(TURNSPEED);
			break;
		}
	}
}

/*
 *	对战：敌人在右前方
 */
void fight_FRRI_ENEMY()
{
	switch(vehicle.dir) {
	case BACK_EDGE:	// 面对中心
		setSpeed(ATTACKGEAR4, ATTACKGEAR2);			// 差速前进 + 右急转弯
		break;

	case FACE_EDGE:	// 背对中心
		switch(vehicle.track) {
		case IN_TRACK0:
			setSpeed(ATTACKGEAR4, ATTACKGEAR2);		// 差速前进 + 右急转弯
			break;

		default:
			turnOnSpeed(TURNSPEED);
			break;
		}
		break;

	case LEFT_EDGE:	// 右侧中心
	case RIGHT_EDGE: // 左侧中心
		switch(vehicle.track) {
		case IN_TRACK0:
		case IN_TRACK1:
		case TRACK0_TRACK1_SiR:
		case TRACK1_TRACK0_SiL:
			setSpeed(ATTACKGEAR4, ATTACKGEAR2);		// 差速前进 + 右急转弯
			break;
				
		default:
			turnOnSpeed(TURNSPEED);
		break;
		}
	break;
	}
}


/*
 *	对战：敌人在左前方
 */
void fight_FRLE_ENEMY()
{
/*
	switch(vehicle.dir) {
	case RIGHT_EDGE:	// 左侧中心，我方不利
		switch(vehicle.track) {
		CASE_CORNER
		// 在角落位置，右转逃离
			turnOnSpeed(TURNSPEED);
			break;
		// 其他位置左转对准敌人
		default:
			turnOnSpeed(-1*TURNSPEED);
			break;
		}
		break;

	default:
		turnOnSpeed(-1*TURNSPEED);
		break;
	}
*/
	switch(vehicle.dir) {
		case BACK_EDGE:		// 面对中心
			setSpeed(ATTACKGEAR2, ATTACKGEAR4);			// 差速前进 + 左急转弯
		break;

		case FACE_EDGE:		// 背对中心
			switch(vehicle.track) {
			case IN_TRACK0:
				setSpeed(ATTACKGEAR2, ATTACKGEAR4);		// 差速前进 + 左急转弯
			break;

			default:
				turnOnSpeed(-1*TURNSPEED);
			break;
			}
		break;

		case LEFT_EDGE:		// 右侧中心
		case RIGHT_EDGE:	// 左侧中心
			switch(vehicle.track) {
			case IN_TRACK0:
			case IN_TRACK1:
			case TRACK0_TRACK1_SiR:
			case TRACK1_TRACK0_SiL:
				setSpeed(ATTACKGEAR2, ATTACKGEAR4);		// 差速前进 + 左急转弯
			break;
				
			default:
				turnOnSpeed(-1*TURNSPEED);
			break;
			}
		break;
		}
}

/*
 *	对战：敌人在左后方
 */
void fight_BALE_ENEMY()
{
	switch(vehicle.dir) {

	case BACK_EDGE:		// 面对中心
	// 边跑边转弯
		setSpeed(ATTACKGEAR2, ATTACKGEAR4); 			// 差速前进 + 左急转弯
		break;

	case FACE_EDGE:		// 背对中心
		switch(vehicle.track) {
	
		// 在轨道0中活动范围较广，逃跑
		case IN_TRACK0:
			setSpeed(ATTACKGEAR2, ATTACKGEAR4);		// 差速前进 + 左急转弯
			break;

		// 在轨道1中直接转弯
		CASE_TRACK1
			turnOnSpeed(-1*TURNSPEED);					// 向左旋转
			break;			
		// 逃不了，抵抗!
		default:
			goOnSpeed( -1*TOPSPEED);  
			break;
		}
		break;
	}
}

/*
 *	对战：敌人在右后方
 */
void fight_BARI_ENEMY()
{
	switch(vehicle.dir) {
		
	case BACK_EDGE:		// 面对中心
	// 边跑边转弯
		setSpeed(ATTACKGEAR4, ATTACKGEAR2);			// 差速前进 + 右急转弯
		break;

	case FACE_EDGE:		// 背对中心
		switch(vehicle.track) {
	
		// 在轨道0中活动范围较广，逃跑
		case IN_TRACK0:
			setSpeed(ATTACKGEAR4, ATTACKGEAR2);		// 差速前进 + 右急转弯
			break;

		// 在轨道1中直接转弯
		CASE_TRACK1
			turnOnSpeed(TURNSPEED);					// 向右旋转
			break;		
		// 逃不了，抵抗!
		default:
			setSpeed(-1*ATTACKGEAR2, -1*ATTACKGEAR4);  // 差速后退 + 右急转弯
			break;
		}
		break;
	}
}

/**
	边缘检测中断 
	@IO：  1
	@方位：右后
**/
SIGNAL(INT4_vect){
	cli();

//	uart1_put_str("右后中断\n");
	edgeDetected();

	sei();

}

/**
	边缘检测中断2
	@IO  ：  0
	@方位：右前
**/
SIGNAL (INT5_vect)
{
	cli();

//	uart1_put_str("右前中断\n");
	edgeDetected();

	sei();
}

/**
	边缘检测中断3
	@IO : 3
	@方位 ：左后
**/
SIGNAL (INT6_vect)
{
	cli();

//	uart1_put_str("左后中断\n");
	edgeDetected();

	sei();
}

/**
	边缘检测中断4
	@IO : 2
	@方位：左前
**/
SIGNAL (INT7_vect)
{
	cli();

//	uart1_put_str("左前中断\n");
	edgeDetected();

	sei();
}
/**
	检测到边缘时进行危机处理
**/
void edgeDetected() {

	int flagInEdge = 1;		// 当前处于边缘地带
	packDanger();
	while(flagInEdge) {	
		txData();
		// 刷新边缘检测编码
		sensor.io_frd	=READ_GPIO(IO_FRD);
	 	sensor.io_brd	=READ_GPIO(IO_BRD);
	 	sensor.io_bld	=READ_GPIO(IO_BLD);
     	sensor.io_fld	=READ_GPIO(IO_FLD);
		sensor.edgeCode = (sensor.io_frd<<3 | sensor.io_brd<<2 | sensor.io_bld<<1 | sensor.io_fld);

		switch(sensor.edgeCode) {
		case BACK_EDGE:		// 正后方陷入边缘 
			goOnSpeed(TOPSPEED);
			break;

		case FACE_EDGE:		// 正前方陷入边缘
			goOnSpeed(-1*TOPSPEED);
			break;

		case LEFT_EDGE:		// 左侧陷入边缘
			setSpeed(TOPSPEED, 0);
			break;

		case RIGHT_EDGE:	// 右侧陷入边缘
			setSpeed(0, TOPSPEED);
			break;

		case FRRI_EDGE:		// 右前方陷入边缘
		case BALE_RING:		// 只有左后方在擂台上
			setSpeed(0, -1*TOPSPEED);
			break;

		case FRLE_EDGE:		// 左前方陷入边缘
		case BARI_RING:		// 只有右后方在擂台上
			setSpeed(-1*TOPSPEED, 0);
			break;

		case BARI_EDGE:		// 右后方陷入边缘
		case FRLE_RING:		// 只有左前方在擂台上
			setSpeed(0, TOPSPEED);
			break;
	
		case BALE_EDGE:		// 左后方陷入边缘
		case FRRI_RING:		// 只有右前方在擂台上
			setSpeed(TOPSPEED, 0);
			break;

		default:
			flagInEdge = 0;	// 已成功脱离边缘
			break;
		}
	}
}

void walkInTrack1()
{
	switch(vehicle.dir) {
	case FACE_EDGE:
		switch(vehicle.track) {
		CASE_CORNER
		CASE_TRACK2
			goOnSpeed(-1*SAFESPEED);
			break;
		default:
			turnOnSpeed(SAFESPEED);
			break;
		}
		break;
	case LEFT_EDGE:
		switch(vehicle.track) {
		CASE_CORNER
		CASE_TRACK2	
			turnOnSpeed(SAFESPEED);
			break;
		default:
			goOnSpeed(SAFESPEED);
			break;
		}
		break;
	case RIGHT_EDGE:
		switch(vehicle.track) {
		CASE_CORNER
		CASE_TRACK2
			turnOnSpeed(-1*SAFESPEED);
			break;
		default:
			setSpeed(0, SAFESPEED);
			break;
		}
	case BACK_EDGE:
		goOnSpeed(SAFESPEED);
		break;	
	}	
}

