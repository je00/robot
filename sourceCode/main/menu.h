#ifndef _MENU_H_
#define _MENU_H_


/**
	EEPROM ������־
**/

#define EEP_R 0				// ������
#define EEP_W 1				// д����

#define AD_CHECK_IO 4		// ���������ID��AD��

/**
	�������Ĵ洢��ַ
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
	��̨����
**/
int AD_WU;					// ��ɫ���ֵĻҶ�ֵ
int AD_MAXGAP;				// ̤���ɫ�Ҷ�ͻ�� 

int AD_WHITE;				// ��ɫ����Ҷ�
int AD_BLACK;				// ��ɫ����Ҷ�

int CORNERRATION;			// ����ռ�뾶��

int minGreyTrack0;			// ���0��С�Ҷ�
int minGreyTrack1;			// ���1��С�Ҷ�
int minGreyTrack2;			// ���2��С�Ҷ�

int AD_ADJUST_L;			// �Ҷ���ƫ��
int AD_ADJUST_R;			// �Ҷ���ƫ��

/**
	��������
**/

int TOPSPEED;				// ����ٶ�
int ATTACKGEAR4;			// 4��
int ATTACKGEAR3;			// 3��	
int ATTACKGEAR2;			// 2��
int ATTACKGEAR1;			// 1��
int ATTACKRATION;			// �Ӽ��ٶ�
int TURNSPEED;				// ��ת�ٶ�

unsigned char MODE;			// ����ģʽ

/**
	��ȫ����
**/
int SAFESPEED;				// ��ȫ�ٶ�
int SAFERATION;				// ��ȫ���ٶ�


/**
	 �������ַ 
**/
int NODE_L;					// ����������node			
int NODE_R;					// ����������node


/**
	ʱ�����
**/
unsigned int STATECYCLE; 		// ״̬���ڣ�������ˢ�¼����
unsigned int MEMORYCYCLE;		// �������ڣ���ǰ�޵��ˣ�������һ�ε���λ����Ϣ��ʱ�䣩
unsigned int MEMORYCYCLE_INIT;	// ��ʼ�������ڣ�����ʵ��������ڴ˻��������ӻ���ټ�������

/*
 * ��̨����
 */
int READYSPEEDL;
int READYSPEEDR;
unsigned int MSGOUP;

/*
 *	�����Ӳ���
 */
unsigned int SPEEDPUSH;
unsigned int MEMORYCYCLE_PUSH;

/**
	��������
**/	
void menu(void);						//	��ҳ�����ԭ�����ڴ�ӡ�������նˣ�
void refresh_stage_AD(void);			//  �Ҷȸ�������
void quickSort(int *a, int i, int j); 	//	��������
void eeprom_rOw_par(unsigned char rOw); //	������д����

#endif
