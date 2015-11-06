#ifndef _MOTORCTRL_UART_H
#define _MOTORCTRL_UART_H

void sendOrder(int node, char* instruction, char* parameter);				// ʹ��uart1����ָ��
void setSpeedRation(int node, int acceleration, int deceleration);			// ���üӡ����ٶ�
void setNatureSpeed(int node, int minSpeed, int maxSpeed);					// ��������ٶȡ���С�ٶ�
void setTarSpeed(int node, int tarSpeed);									// ����Ŀ���ٶ�
void setZeroLocation(int node);												// ���õ�ǰΪԭ��λ��
void setTarLocation(int node, char* tarLocation, int flag);					// ����Ŀ��λ��
void setSpeed(int speedL, int speedR);										// ����С�������ֵ��ٶ�
void goOnSpeed(int speed);													// ��С����speed�ٶ�ǰ��
void turnOnSpeed(int speed);												// ��С����speed�ٶ���ת

#endif
