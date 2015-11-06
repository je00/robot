#ifndef _MOTORCTRL_UART_H
#define _MOTORCTRL_UART_H

void sendOrder(int node, char* instruction, char* parameter);				// 使用uart1发送指令
void setSpeedRation(int node, int acceleration, int deceleration);			// 设置加、减速度
void setNatureSpeed(int node, int minSpeed, int maxSpeed);					// 设置最大速度、最小速度
void setTarSpeed(int node, int tarSpeed);									// 设置目标速度
void setZeroLocation(int node);												// 设置当前为原点位置
void setTarLocation(int node, char* tarLocation, int flag);					// 设置目标位置
void setSpeed(int speedL, int speedR);										// 设置小车左右轮的速度
void goOnSpeed(int speed);													// 让小车以speed速度前进
void turnOnSpeed(int speed);												// 让小车以speed速度旋转

#endif
