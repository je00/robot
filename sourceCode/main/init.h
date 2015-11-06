#ifndef	_INIT_H
#define	_INIT_H

#define SET_1(a,b) a |= (1<<b)
#define CLE_0(a,b) a &=~ (1<<b)


/**
	 С���ṹ�� 
**/
struct VEHICLE
{	
	unsigned char dir;				// ����
	unsigned char track;			// ���
	unsigned char flagRed;			// ��ɫ�����־λ
	unsigned char locEnemy; 		// ���˵�λ��
	unsigned char locEnemyLast;		// ��һ�ε��˵�λ��
	unsigned char locFriend;		// �ѷ���λ��
} vehicle; 


/**
	��������
**/
void init_device(void);		// ��ʼ��AVR��Դ
void globalVarInit(void);	// ȫ�ֱ�����ʼ��(�󲿷ִ�eeprom�ж�ȡ)
void ready(void);			// ׼����ϣ��ڵ��Ҳ����������̨
void scoopLaydown(void);	// ���²���

#endif
