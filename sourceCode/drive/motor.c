/**
  1��ʹ�ô���1ֱ�ӷ���ָ��������壬�ﵽ��ȷ���Ƶ����Ч��;
  2�������PPM����ܲ��ȶ������ҵ����ܴ�Ĳ��٣�����ѵ�����ֻ�������������Сһ���ֵĹ���;
  3��ָ���ʽ����2014/����/BDMC�����ֲ�.
  @author:	Ting
  @date:  		24th June, 2014		
  @history:
  	1��ɾ��motor�ṹ�壬�򻯿��Ʒ���;
	   @corroctor:	Ting
	   @date:		27th July, 2014
	2��setSpeed(..), goOnSpeed(..), turnOnSpeed(..)���������ṩ���ٶȽӿڣ�����ÿ������ָ��ĸ��Ӷ�;
	3��sendOrder(..)��������uart1_put_char(0x0d);��䣬����ָ��ǰ�رն�ʱ��1�жϣ���ʱ�����ҷ�״̬������
	   �ų� ��ָ������ �ĸ���;
	   @corroctor: Ting
	   @date;		16th, September, 2014

**/


#include "INCLUDES.h"
/**
	�����������ַΪnode��������
	@parameter��
			node 	  Ŀ��id		instruction ָ��
			parameter ����
	@return: void
**/
void sendOrder(int node, char* instruction, char* parameter)
{
	uart1_put_char(0x0d);			// �ų����ţ�ʹ�������ѽ��ܵĴ������ݽ���
	uart1_put_int(node);
	uart1_put_str(instruction);
	if(parameter != 0x0d)
		uart1_put_str(parameter);
	uart1_put_char(0x0d);
}

/**
	���ü��ٶȡ����ٶ�
	@parameter: 
			node 	  Ŀ��id
			acceleration ���ٶ�		deceleration ���ٶ�
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
	���������С�ٶ�
	@parameter: 
			node 	  Ŀ��id
			minSpeed ��С�ٶ�		maxSpeed ����ٶ�
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
	����Ŀ���ٶ�
	@parameter: 
			node 	  Ŀ��id
			tarSpeed Ŀ���ٶ�
	@return: void
**/
void setTarSpeed(int node, int tarSpeed) 
{	
	char buf[6];	
	
	sprintf(buf, "%d", tarSpeed);
	sendOrder(node, "V", buf);
}

/**
	���õ�ǰλ��Ϊԭ��
	@parameter: 	node 	  Ŀ��id
	@return: void
**/
void setZeroLocation(int node)
{
	sendOrder(node, "HO", "\r");
}

/**
	����Ŀ��λ��
	@parameter: 
			node 	  Ŀ��id
			tarLocation Ŀ��λ��
			flag		���λ�û��Ǿ���λ�ñ�־��0�����λ�� 	1:����λ��
	@return: void
**/
void setTarLocation(int node, char* tarLocation, int flag)
{
	if(flag == 0){ // ���λ��ģʽ
		sendOrder(node, "M", 0x0d);
		sendOrder(node, "SOR1", 0x0d);
		sendOrder(node, "LR", tarLocation);
		sendOrder(node, "M", 0x0d);
	}
	else{		   // ����λ��ģʽ
		sendOrder(node, "M", 0x0d);
		sendOrder(node, "SOR1", 0x0d);
		sendOrder(node, "LA", tarLocation);
		sendOrder(node, "M", 0x0d);
	}
	
}

/**
	�������ҵ�����ٶ�
	@parameter: 
			speedL/R 	 	�����ֵ��ٶ�
			acceleration	���ٶ�
			deceleration	���ٶ�
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
	��С����speed�ٶ�ǰ��
	@parameter: 
			speed 	 		С���ж����ٶ�
			acceleration	���ٶ�
			deceleration	���ٶ�
	@return: void
**/
void goOnSpeed(int speed) 
{
	setSpeed(speed, speed);
}

/**
 *	��С����speed�ٶ���ת
 *	@parameter:
 *			speed	С����ת���ٶȣ�>0Ϊ˳ʱ�룬<0Ϊ��ʱ��
 *	@return: void
 */			
void turnOnSpeed(int speed)
{	
	CLE_0(TIMSK, TOIE1);
	setTarSpeed(NODE_L, -1*speed);
	setTarSpeed(NODE_R, -1*speed);
	SET_1(TIMSK, TOIE1);	
}




