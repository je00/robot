/**
  1、使用串口1直接发送指令给驱动板，达到精确控制电机的效果;
  2、往届的PPM程序很不稳定，左右电机会很大的差速，误差难调，且只发挥了驱动板很小一部分的功能;
  3、指令格式参照2014/资料/BDMC数据手册.
  @author:	Ting
  @date:  		24th June, 2014		
  @history:
  	1、删除motor结构体，简化控制方法;
	   @corroctor:	Ting
	   @date:		27th July, 2014
	2、setSpeed(..), goOnSpeed(..), turnOnSpeed(..)函数不再提供加速度接口，降低每条控制指令的复杂度;
	3、sendOrder(..)函数加入uart1_put_char(0x0d);语句，发送指令前关闭定时器1中断（定时发送我方状态包），
	   排除 非指令串口输出 的干扰;
	   @corroctor: Ting
	   @date;		16th, September, 2014

**/


#include "INCLUDES.h"
/**
	发送命令给地址为node的驱动板
	@parameter：
			node 	  目标id		instruction 指令
			parameter 参数
	@return: void
**/
void sendOrder(int node, char* instruction, char* parameter)
{
	uart1_put_char(0x0d);			// 排除干扰，使驱动板已接受的错误数据结束
	uart1_put_int(node);
	uart1_put_str(instruction);
	if(parameter != 0x0d)
		uart1_put_str(parameter);
	uart1_put_char(0x0d);
}

/**
	设置加速度、减速度
	@parameter: 
			node 	  目标id
			acceleration 加速度		deceleration 减速度
	@return: void
**/
void setSpeedRation(int node, int acceleration, int deceleration) 
{	
	char buf[64];
	
	sprintf(buf, "%d", acceleration);
	sendOrder(node, "AC", buf);

	sprintf(buf, "%d", deceleration);
	sendOrder(node, "DEC", buf);
}

/**
	设置最大、最小速度
	@parameter: 
			node 	  目标id
			minSpeed 最小速度		maxSpeed 最大速度
	@return: void
**/
void setNatureSpeed(int node, int minSpeed, int maxSpeed) 
{
	char buf[6];

	sprintf(buf, "%d", minSpeed);
	sendOrder(node, "MV", buf);

	sprintf(buf, "%d", maxSpeed);
	sendOrder(node, "SP", buf);

	sendOrder(node, "eepsav", 0x0d);

}

/**
	设置目标速度
	@parameter: 
			node 	  目标id
			tarSpeed 目标速度
	@return: void
**/
void setTarSpeed(int node, int tarSpeed) 
{	
	char buf[6];	
	
	sprintf(buf, "%d", tarSpeed);
	sendOrder(node, "V", buf);
}

/**
	设置当前位置为原点
	@parameter: 	node 	  目标id
	@return: void
**/
void setZeroLocation(int node)
{
	sendOrder(node, "HO", "\r");
}

/**
	设置目标位置
	@parameter: 
			node 	  目标id
			tarLocation 目标位置
			flag		相对位置或是绝对位置标志，0：相对位置 	1:绝对位置
	@return: void
**/
void setTarLocation(int node, char* tarLocation, int flag)
{
	if(flag == 0){ // 相对位置模式
		sendOrder(node, "M", 0x0d);
		sendOrder(node, "SOR1", 0x0d);
		sendOrder(node, "LR", tarLocation);
		sendOrder(node, "M", 0x0d);
	}
	else{		   // 绝对位置模式
		sendOrder(node, "M", 0x0d);
		sendOrder(node, "SOR1", 0x0d);
		sendOrder(node, "LA", tarLocation);
		sendOrder(node, "M", 0x0d);
	}
	
}

/**
	设置左右电机的速度
	@parameter: 
			speedL/R 	 	左右轮的速度
			acceleration	加速度
			deceleration	减速度
	@return: void
**/
void setSpeed(int speedL, int speedR)
{
	CLE_0(TIMSK, TOIE1);
	setTarSpeed(NODE_L, -1*speedL);	
	setTarSpeed(NODE_R, speedR);
	SET_1(TIMSK, TOIE1);
}

/**
	让小车以speed速度前行
	@parameter: 
			speed 	 		小车行动的速度
			acceleration	加速度
			deceleration	减速度
	@return: void
**/
void goOnSpeed(int speed) 
{
	setSpeed(speed, speed);
}

/**
 *	让小车以speed速度旋转
 *	@parameter:
 *			speed	小车旋转的速度，>0为顺时针，<0为逆时针
 *	@return: void
 */			
void turnOnSpeed(int speed)
{	
	CLE_0(TIMSK, TOIE1);
	setTarSpeed(NODE_L, -1*speed);
	setTarSpeed(NODE_R, -1*speed);
	SET_1(TIMSK, TOIE1);	
}




