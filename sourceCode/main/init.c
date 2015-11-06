/*
 * �����˳�ʼ����Ԥ������ط���
 * @Author: Ting
 * @Date: 24th July, 2014
 */

#include "INCLUDES.h"

/*
 * ��ʼ��AVR��Դ����EEPROM�ж�ȡ�����˲�����Ȼ��Ԥ���ȴ��ǳ�����
 */
void init_device(void)
{
	cli();

	/* 1.��ʼ�����ڡ���ʱ�� */
	myuart_init();	
	mytimer_init();

	/* 2.��EEPROM�л�ȡ���� */
	globalVarInit();
	
	/* 3.�����ٶȲ��� */

	// ���ù������ٶ�
	setSpeedRation(NODE_L, ATTACKRATION, ATTACKRATION);
	setSpeedRation(NODE_R, ATTACKRATION, ATTACKRATION);
	// ���������С�ٶ�
	setNatureSpeed(NODE_L, 0, TOPSPEED); 
	setNatureSpeed(NODE_R, 0, TOPSPEED);
	
	/* 4.Ԥ�� */
	ready();
	// �����ж�
	sei();
}

/*
 * ��EEPOM�л�ȡ�����˲���������ȫ�ֱ���
 */
void globalVarInit(void)
{
	uart1_put_str("���ڶ�ȡeeprom...\n");
	eeprom_rOw_par(EEP_R);	

	// ���������ʼ��
	sensor.trackCode = 0; 
	MEMORYCYCLE = MEMORYCYCLE_INIT;
	minGreyTrack2 = AD_BLACK + (AD_WHITE - AD_BLACK) /CORNERRATION;
	AD_MAXGAP = (AD_WHITE - minGreyTrack2) /3;
	minGreyTrack1 = minGreyTrack2 + AD_MAXGAP; 
	minGreyTrack0 = minGreyTrack1 + AD_MAXGAP; 

	// ���Ҷ�ͻ�䣬�����ҶȲ�������Ҷ�ͻ�䣬��Ϊ�����ɫ
	AD_MAXGAP += 10;

	myFriend.id = 0x34;
	myFriend.detectCode = 0xff;
	// ������ʱ��2��������¼�������ݰ��ļ��ʱ��
	flag2 = 1;

}

/*
 * �ڽ��ݴ���׼����ֱ���ڵ��Ҳ���⿪��
 */
void ready()
{
	unsigned char i = 0;
	unsigned char j = 0;
	while(1)	
	{
		i = 0;
		sensor.io_r	=READ_GPIO(IO_R);
		while(sensor.io_r == 0) {
			uart1_put_str("\n\rMODE: FIGHT\n\r");
	        	sensor.io_r = READ_GPIO(IO_R);
			sensor.io_l = READ_GPIO(IO_L);
			if(i++ > 10) // ��10��ȷ������������
				goto OK;
			_delay_ms(10);
		}
	}
OK:
	//  ������������Ҫ������ϸ���ԣ���֤�������ܳ嵽��̨����
	setSpeed(READYSPEEDL, READYSPEEDR);
	_delay_ms(MSGOUP);

	// ����̨����ͣס
	goOnSpeed(0);
}
