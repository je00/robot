/**
	�������ó���PC��ͨ�������жϽ��պͷ��ʹ������ݣ�ʵ�ֶ�С������������
	@author: Ting
	@date:	 	24th July, 2014
	@history:
		1���ڲ˵��н��������С�Ҷȼ�����ϴ���eeprom��������ԭʼ�������
			@corrector��Ting
			@date: 4th April, 2014
**/
#include "INCLUDES.h"

char select;
char buf[6];
int i;

void menu() 
{
	myuart_init();
	_delay_ms(1000);

	uart1_put_str("\n\n\r����ģʽ���������ڶ�ȡ��Ϣ...");

	//��EEPROM�ж�ȡ����
	eeprom_rOw_par(EEP_R);

	uart1_put_str("\n\r��ȡ�ɹ���");
	
	while(1) {

		buf[0] = 'n'; buf[1] = 'n'; buf[2] = 'n'; buf[3] = 'n'; buf[4] = 'n';

		do {
			uart1_put_str("\n\n\r��Ҫ�����������?");
			uart1_put_str("\n\r1.��ӡ��ǰ��Ϣ");
			uart1_put_str("\t2.�����������");
			uart1_put_str("\t3.���лҶȲ���");
			uart1_put_str("\t4.���ý���Ȩֵ");
			uart1_put_str("\n\r5.����״̬����");
			uart1_put_str("\t6.���ü�������");
			uart1_put_str("\t7.������̨����");
			uart1_put_str("\t8.���õ������");
			uart1_put_str("\n\rl.�ض�");
			uart1_put_str("\tw.����");
			uart1_put_str("\n\r-> ");
			select = uart1_get_char();
			uart1_put_char(select);
		} while(	select != '1' && select != '2' && select != '3' && select != '4' && select != '5'
			 && 	select != '6' && select != '7' && select != '8' && select != 'l' && select != 'w' 
				);

		switch(select) {
		
		case '1':	// ��ӡ��ǰ��Ϣ
			printMessage();
		break;

		case '2':	// ���������Ӳ���
			setPush();
		break;

		case '3':	// �ҶȲ���
			refresh_stage_AD();
		break;	

		case '4':	// ���ý���Ȩֵ
			setCornerRation();
		break;

		case '5':	// ����״̬����
			setStateCycle();
		break;	

		case '6':	// ���ü�������
			setMemoryCycle();
		break;

		case '7':	// ������̨����
			setReady();
		break;

		case '8':	// ���õ������
			setMotor();
		break;

		case 'w':	// ����
			uart1_put_str("\n\n\r���ڱ���...");
			eeprom_rOw_par(EEP_W);
			uart1_put_str("\n\r����ɹ�!");
		break;

		case 'l':	// ���¶�ȡ
			uart1_put_str("\n\n\r�������¶�ȡ��Ϣ...");
			eeprom_rOw_par(EEP_R);
			uart1_put_str("\n\r��ȡ�ɹ���");
		break;
		}
	}
}	

/**
	��ӡ��ǰ��Ϣ
**/
void printMessage() 
{
	uart1_put_str("\n\n\r-------------------------------------------------------------------");

	uart1_put_str("\n\r״̬���ڣ�");
	uart1_put_int(STATECYCLE); uart1_put_str("ms");

	uart1_put_str("\t�������ڣ�");
	uart1_put_int(MEMORYCYCLE_INIT); uart1_put_str("ms");

	uart1_put_str("\n\r��̨������");
	uart1_put_str("\n\r\t  �ٶȣ�");
	uart1_put_str("\t��");	uart1_put_int(READYSPEEDL);	
	uart1_put_str("\t�ң�");	uart1_put_int(READYSPEEDR);
	uart1_put_str("\t����ʱ�ӣ�");	
	uart1_put_int(MSGOUP); uart1_put_str("ms");
	
	uart1_put_str("\n\r���������");
	uart1_put_str("\n\r\t  �ٶȣ�"); uart1_put_int(SPEEDPUSH);	
	uart1_put_str("\t  ״̬���ڣ�");uart1_put_int(MEMORYCYCLE_PUSH); uart1_put_str("ms");
		
	uart1_put_str("\n\r�Ҷ���Ϣ��");
	uart1_put_str("\n\r\t  �Ҷ�ƫ�ã�");
	uart1_put_str("\t��");	uart1_put_int(AD_ADJUST_L);	
	uart1_put_str("\t�ң�");	uart1_put_int(AD_ADJUST_R);
	uart1_put_str("\n\r\t  ���Ҷ�ֵ��");
	uart1_put_str("\t�䣺");	uart1_put_int(AD_WU);	
	uart1_put_str("\t�ף�");	uart1_put_int(AD_WHITE);
	uart1_put_str("\t�ڣ�");	uart1_put_int(AD_BLACK);
	uart1_put_str("\n\r\t  ����Ȩֵ��\t");
	uart1_put_int(CORNERRATION);

	uart1_put_str("\n\r�����Ϣ:");
	uart1_put_str("\n\r\t  ���ID��");
	uart1_put_str("\t��"); uart1_put_int(NODE_L);
	uart1_put_str("\t�ң�"); uart1_put_int(NODE_R);
	uart1_put_str("\n\r\t  ����ٶȣ�\t"); 	uart1_put_int(TOPSPEED);
	uart1_put_str("\n\r\t  ת���ٶȣ�\t");	uart1_put_int(TURNSPEED);
	uart1_put_str("\n\r\t  ��ȫ�ٶȣ�\t"); 	uart1_put_int(SAFESPEED);
	uart1_put_str("\n\r\t  ��ȫ���٣�\t"); 	uart1_put_int(SAFERATION);
	uart1_put_str("\n\r\t  �����ٶȣ�"); 
	uart1_put_str("\tһ����"); 				uart1_put_int(ATTACKGEAR1);	
	uart1_put_str("\t������"); 				uart1_put_int(ATTACKGEAR2);
	uart1_put_str("\n\r\t\t\t������");		uart1_put_int(ATTACKGEAR3);
	uart1_put_str("\t�ĵ���"); 				uart1_put_int(ATTACKGEAR4);
	uart1_put_str("\n\r\t  �������٣�\t");	uart1_put_int(ATTACKRATION);

	uart1_put_str("\n\r-------------------------------------------------------------------");
}

/**
	���������Ӳ���
**/
void setPush()
{
	while(1) {
		do {
			uart1_put_str("\n\n\r���������");
			uart1_put_str("\n\r1.�����ٶ�");
			uart1_put_str("\n\r2.���ü�������");
			uart1_put_str("\n\r0.����");
			uart1_put_str("\n\r-> ");
			select = uart1_get_char();
			uart1_put_char(select);
		} while( select != '1' && select != '2' && select != '3' && select != '0');
		if(select == '0') break;
		switch(select) {
		case '1':  // �����������ٶ�
			do{
				uart1_put_str("\n\n\r�����������ٶ�(0000~9999)��");
				for(i=0; i<4; i++) {
					buf[i] = uart1_get_char();	
					uart1_put_char(buf[i]);
				}
				buf[4] = '\0';
				SPEEDPUSH = atoi(buf);
			} while(SPEEDPUSH < 0 || SPEEDPUSH > 9999);
			uart1_put_str("\n\r���óɹ���");
			break;

		case '2': // ���������Ӽ�������
			do {
				uart1_put_str("\n\r�����Ӽ�������(0000~9999): ");
				for(i=0; i<4; i++) {
					buf[i] = uart1_get_char();	
					uart1_put_char(buf[i]);
				}
				buf[4] = '\0';
				MEMORYCYCLE_PUSH = atoi(buf);
			} while( MEMORYCYCLE_PUSH > 9999 ||MEMORYCYCLE_PUSH < 0 );
			uart1_put_str("\n\r���óɹ���");

		break;

		default:
		break;
		}
	}
}

/**
	����״̬����
**/
void setStateCycle()
{
	do {
		uart1_put_str("\n\n\r����״̬����(000~999ms)��");
		for(i=0; i<3; i++) {
			buf[i] = uart1_get_char();	
			uart1_put_char(buf[i]);
		}
		buf[3] = '\0';
		STATECYCLE = atoi(buf);
	} while( STATECYCLE < 0 || STATECYCLE > 999);	
	uart1_put_str("\n\r���óɹ���");
}

/**
	���ü�������
**/
void setMemoryCycle()
{
	do {
		uart1_put_str("\n\n\r���ü�������(0000~9999ms)��");
		for(i=0; i<4; i++) {
			buf[i] = uart1_get_char();	
			uart1_put_char(buf[i]);
		}
		buf[4] = '\0';
		MEMORYCYCLE_INIT = atoi(buf);
	} while( MEMORYCYCLE_INIT < 0 || MEMORYCYCLE_INIT > 9999);	
	uart1_put_str("\n\r���óɹ���");
}

/**
	���ý���Ȩֵ
**/
void setCornerRation()
{
	do {
		uart1_put_str("\n\n\r���ý���Ȩֵ(0~9)��");
		buf[0] = uart1_get_char();	
		uart1_put_char(buf[0]);
		buf[1] = '\0';
		CORNERRATION = atoi(buf);
	} while( CORNERRATION < 0 || CORNERRATION > 9);	
	uart1_put_str("\n\r���óɹ���");
}

/**
	������̨����
**/
void setReady()
{
	while(1) {
		do {
			uart1_put_str("\n\n\r��̨������");
			uart1_put_str("\n\r1.�����ٶ�");
			uart1_put_str("\n\r2.������̨ʱ��");
			uart1_put_str("\n\r0.����");
			uart1_put_str("\n\r-> ");
			select = uart1_get_char();
			uart1_put_char(select);
		} while( select != '1' && select != '2' && select != '3' && select != '0');
		if(select == '0') break;
		switch(select) {
		case '1':  // �������ٶ�
			uart1_put_str("\n\n\r������̨�ٶȣ�");
			do {
				uart1_put_str("\n\r�ٶ���(-9999~09999): ");
				for(i=0; i<5; i++) {
					buf[i] = uart1_get_char();	
					uart1_put_char(buf[i]);
				}
				buf[5] = '\0';
				READYSPEEDL = atoi(buf);
			} while(READYSPEEDL < -9999 || READYSPEEDL > 9999);

			do {
				uart1_put_str("\n\r�ٶ���(-9999~09999): ");
				for(i=0; i<5; i++) {
					buf[i] = uart1_get_char();	
					uart1_put_char(buf[i]);
				}
				buf[5] = '\0';
				READYSPEEDR = atoi(buf);
			} while(READYSPEEDR < -9999 || READYSPEEDR > 9999);
			uart1_put_str("\n\r���óɹ���");
			break;

		case '2': // ������̨ʱ��
			do {
				uart1_put_str("\n\r��̨ʱ��(0000~9999): ");
				for(i=0; i<4; i++) {
					buf[i] = uart1_get_char();	
					uart1_put_char(buf[i]);
				}
				buf[4] = '\0';
				MSGOUP = atoi(buf);
			} while( MSGOUP > 9999 ||MSGOUP < 0 );
			uart1_put_str("\n\r���óɹ���");

		break;

		default:
		break;
		}
	}
}

/**
	���õ��
**/
void setMotor()
{
	while(1) {
		do {
			uart1_put_str("\n\n\r���ѡ�");
			uart1_put_str("\n\r1.���õ��ID");
			uart1_put_str("\n\r2.��������ٶ�");
			uart1_put_str("\n\r3.����ת���ٶ�");
			uart1_put_str("\n\r4.���ð�ȫ����");
			uart1_put_str("\n\r5.���ù�������");
			uart1_put_str("\n\r0.����");
			uart1_put_str("\n\r-> ");
			select = uart1_get_char();
			uart1_put_char(select);
		} while( select != '1' && select != '2' && select != '3' && select != '4' 
				&& select != '5' && select != '0');
		if( select == '0') break;
		switch(select) {
		case '1':	// ���õ��ID
			uart1_put_str("\n\n\r���õ��ID��");
			do {
				uart1_put_str("\n\r�����(00~99): ");
				for(i=0; i<2; i++) {
					buf[i] = uart1_get_char();	
					uart1_put_char(buf[i]);
				}
				buf[2] = '\0';
				NODE_L = atoi(buf);
			} while( NODE_L < 0 || NODE_L > 99);

			do {
				uart1_put_str("\n\r�����(00~99): ");
				for(i=0; i<2; i++) {
					buf[i] = uart1_get_char();	
					uart1_put_char(buf[i]);
				}
				buf[2] = '\0';
				NODE_R = atoi(buf);
			} while(NODE_R < 0 || NODE_R > 99);
			uart1_put_str("\n\r���óɹ���");
		break;

		case '2':	// ��������ٶ�
			uart1_put_str("\n\n\r��������ٶ�(00000 ~ 20000)��");
			do {
				for(i=0; i<5; i++) {
					buf[i] = uart1_get_char();
					uart1_put_char(buf[i]);
				}
				buf[5] = '\0';
				TOPSPEED = atoi(buf);
			} while(TOPSPEED < 0 || TOPSPEED > 20000);
			uart1_put_str("\n\r���óɹ���");
		break;	
		
		case '3':	// ����ת���ٶ�
			uart1_put_str("\n\n\r����ת���ٶ�(00000 ~ 20000)��");
			do {
				for(i=0; i<5; i++) {
					buf[i] = uart1_get_char();
					uart1_put_char(buf[i]);
				}
				buf[5] = '\0';
				TURNSPEED = atoi(buf);
			} while(TURNSPEED < 0 || TURNSPEED > 20000);
			uart1_put_str("\n\r���óɹ���");
		break;

		case '4':	// ���ð�ȫ����
			uart1_put_str("\n\n\r���ð�ȫ������");
			uart1_put_str("\n\r��ȫ�ٶ�(00000~20000)��");
			do {
				for(i=0; i<5; i++) {
					buf[i] = uart1_get_char();
					uart1_put_char(buf[i]);
				}
				buf[5] = '\0';
				SAFESPEED = atoi(buf);
			} while(SAFESPEED < 0 || SAFESPEED > 20000);

			uart1_put_str("\n\r��ȫ�ӡ����ٶ�(00000~10000)��");
			do {
				for(i=0; i<5; i++) {
					buf[i] = uart1_get_char();
					uart1_put_char(buf[i]);
				}
				buf[5] = '\0';
				SAFERATION = atoi(buf);
			} while(SAFERATION < 0 || SAFERATION > 10000);

			uart1_put_str("\n\r���óɹ���");

		break;

		case '5':	// ���ù�������
			uart1_put_str("\n\n\r���ù���������");

			uart1_put_str("\n\rһ���ٶ�(00000~20000)��");
			do {
				for(i=0; i<5; i++) {
					buf[i] = uart1_get_char();
					uart1_put_char(buf[i]);
				}
				buf[5] = '\0';
				ATTACKGEAR1 = atoi(buf);
			} while(ATTACKGEAR1 < 0 || ATTACKGEAR1 > 20000);
				
			uart1_put_str("\n\r�����ٶ�(00000~20000)��");
			do {
				for(i=0; i<5; i++) {
					buf[i] = uart1_get_char();
					uart1_put_char(buf[i]);
				}
				buf[5] = '\0';
				ATTACKGEAR2 = atoi(buf);
			} while(ATTACKGEAR2 < 0 || ATTACKGEAR2 > 20000);

			uart1_put_str("\n\r�����ٶ�(00000~20000)��");
			do {
				for(i=0; i<5; i++) {
					buf[i] = uart1_get_char();
					uart1_put_char(buf[i]);
				}
				buf[5] = '\0';
				ATTACKGEAR3 = atoi(buf);
			} while(ATTACKGEAR3 < 0 || ATTACKGEAR3 > 20000);

			uart1_put_str("\n\r�ĵ��ٶ�(00000~20000)��");
			do {
				for(i=0; i<5; i++) {
					buf[i] = uart1_get_char();
					uart1_put_char(buf[i]);
				}
				buf[5] = '\0';
				ATTACKGEAR4 = atoi(buf);
			} while(ATTACKGEAR4 < 0 || ATTACKGEAR4 > 20000);

			uart1_put_str("\n\r�����ӡ����ٶ�(00000~50000)��");
			do {
				for(i=0; i<5; i++) {
					buf[i] = uart1_get_char();
					uart1_put_char(buf[i]);
				}
				buf[5] = '\0';
				ATTACKRATION = atoi(buf);
			} while(ATTACKRATION < 0 || ATTACKRATION > 50000);

			uart1_put_str("\n\r���óɹ���");
		break;

		}
	}
}
/**
	ͨ����������ȡ������ͬ��̨�İ�ɫ�������ɫ���ֵĻҶ�ֵ
**/
void refresh_stage_AD()
{ 
	int i =0, j=0, k=0;

	int white[3][4];
	int black[3][4];
	int ad_port[3] = {AD_F, AD_L, AD_R};
	char* ad_loc[3] = {"\tF:", "\tL:", "\tR:"};
	int white_f[4];
	int white_l[4];
	int white_r[4];

	int black_f[4];
	int black_l[4];
	int black_r[4];

	int ad_white[3];
	int ad_black[3];
	int ad_red[3];
	int ad_wu[3];

	int t = 50;
	
	// ���������ʱ����������Ч���ȴ������ɿ�
	while( read_adc2(AD_CHECK_IO)  < 512) 	
		_delay_ms(1000);	

	uart1_put_str("�Ҷ�ȡ����������...\n\r");
	
	uart1_put_str("\n\n\r��ɫ����");
	for(j = 0; j < 4; j++) {
		uart1_put_str("\n\r��");
		uart1_put_int(j);
		uart1_put_str(":");
		for(i = 0; i < 3; i++) {
			uart1_put_str(ad_loc[i]);
			while(1) {
				if( read_adc2(AD_CHECK_IO) < 512 ) { _delay_ms(t); // ����
				if( read_adc2(AD_CHECK_IO) < 512 ) {
					white[i][j] = 0;
					k = 0;
					while(k < 10) {
						white[i][j] += read_adc2(ad_port[i]);
						_delay_ms(t);
						k ++;
					}
					white[i][j] /= 10;

					uart1_put_int(white[i][j]);

					while( read_adc2(AD_CHECK_IO) < 512);
					break;
				}}
			}
		}
	}

	uart1_put_str("\n\n\r��������");

	uart1_put_str("\n\r��");
	uart1_put_str(":");
	for(i = 0; i < 3; i++) {
		uart1_put_str(ad_loc[i]);
		while(1) {
			if( read_adc2(AD_CHECK_IO) < 512 ) { _delay_ms(t); // ����
			if( read_adc2(AD_CHECK_IO) < 512 ) {
				ad_wu[i] = 0;
				k = 0;
				while(k < 10) {
					ad_wu[i] += read_adc2(ad_port[i]);
					_delay_ms(t);
					k ++;
				}
				ad_wu[i] /= 10;

				uart1_put_int(ad_wu[i]);

				while( read_adc2(AD_CHECK_IO) < 512);
				break;
			}}
		}
	}
	
	uart1_put_str("\n\n\r��ɫ����");
	for(j = 0; j < 4; j++) {
		uart1_put_str("\n\r��");
		uart1_put_int(j);
		uart1_put_str(":");
		for(i = 0; i < 3; i++) {
			uart1_put_str(ad_loc[i]);
			while(1) {
				if( read_adc2(AD_CHECK_IO) < 512 ) { _delay_ms(t); // ����
				if( read_adc2(AD_CHECK_IO) < 512 ) {
					black[i][j] = 0;
					k = 0;
					while(k < 10) {
						black[i][j] += read_adc2(ad_port[i]);
						_delay_ms(t);
						k ++;
					}
					black[i][j] /= 10;

					uart1_put_int(black[i][j]);

					while( read_adc2(AD_CHECK_IO) < 512);
					break;
				}}
			}
		}
	}


	
	// ���������Ҷȴ������ں�ɫ����ɫ����ֱ�������ȡ��ֵ���洢������һά������
	// ÿ����ȡ��ֵ�����п�������
	uart1_put_str("\n\rȡ�����������ڽ��п�������...");

	for(i = 0; i < 3; i++) {
		quickSort(white[i], 0, 3);
		quickSort(black[i], 0, 3);
	}
	uart1_put_str("\n\r�������!");

	uart1_put_str("\n\r���ڼ�����Ч����ֵ...");
	
	// ȥ�����ֵ����Сֵ����������ֵ���ֵ
	for(i = 0; i < 3; i++) {
		ad_white[i] = (white[i][1] + white[i][2]) / 2;
		ad_black[i] = (black[i][1] + black[i][2]) /2;
	}
	
	uart1_put_str("\n\r������ϣ�");
	
	uart1_put_str("\n\n\r���ڼ���Ҷ�ƫ��ֵ...");

	AD_ADJUST_L = ( (ad_white[0] - ad_white[1]) + (ad_black[0] - ad_black[1]) 
						+ (ad_wu[0] - ad_wu[1]) ) / 3;
	AD_ADJUST_R = ( (ad_white[0] - ad_white[2]) + (ad_black[0] - ad_black[2]) 
						+ (ad_wu[0] - ad_wu[2]) ) / 3;

	uart1_put_str("\n\r�������!");
	
	AD_WU = (ad_wu[0] + ad_white[0]) /2;
	
	uart1_put_str("\n\n\rдEEPROM��...");
	
	AD_WHITE = ad_white[0];
	AD_BLACK = ad_black[0];

	eeprom_write_word(AD_WHITE_ADD, AD_WHITE);
	eeprom_write_word(AD_BLACK_ADD, AD_BLACK);
	eeprom_write_word(AD_WU_ADD, AD_WU);
	eeprom_write_word(AD_ADJUST_L_ADD, AD_ADJUST_L);
	eeprom_write_word(AD_ADJUST_R_ADD, AD_ADJUST_R);
	
	uart1_put_str("\n\rд��ɹ���");


	uart1_put_str("\n\n\r����������\n\r");
}

/**
	��eeprom�ж�ȡ����
	@parameter: 
		ifbak �Ƿ��Ǳ��ݻ�ԭ������ifbak == EEP_BAKʱ���ӱ��ݵ�ַ��ȡ�򱣴棬�������ͨ��ַ��ȡ��
		rOw	  ��д��־
**/
void eeprom_rOw_par(unsigned char rOw)
{
	switch(rOw) {
	case EEP_R:
		AD_WU = eeprom_read_word(AD_WU_ADD);
		AD_WHITE = eeprom_read_word(AD_WHITE_ADD);
		AD_BLACK = eeprom_read_word(AD_BLACK_ADD);
		AD_ADJUST_L = eeprom_read_word(AD_ADJUST_L_ADD);
		AD_ADJUST_R = eeprom_read_word(AD_ADJUST_R_ADD);
		CORNERRATION = eeprom_read_word(CORNERRATION_ADD);
		MODE = eeprom_read_word(MODE_ADD);
		NODE_L = eeprom_read_word(NODE_L_ADD);
		NODE_R = eeprom_read_word(NODE_R_ADD);
		ATTACKGEAR4 = eeprom_read_word(ATTACKGEAR4_ADD);
		ATTACKGEAR3 = eeprom_read_word(ATTACKGEAR3_ADD);
		ATTACKGEAR2 = eeprom_read_word(ATTACKGEAR2_ADD);
		ATTACKGEAR1 = eeprom_read_word(ATTACKGEAR1_ADD);
		ATTACKRATION = eeprom_read_word(ATTACKRATION_ADD);
		SAFESPEED = eeprom_read_word(SAFESPEED_ADD);
		SAFERATION = eeprom_read_word(SAFERATION_ADD);
		TOPSPEED = eeprom_read_word(TOPSPEED_ADD);
		STATECYCLE = eeprom_read_word(STATECYCLE_ADD);
		MEMORYCYCLE_INIT = eeprom_read_word(MEMORYCYCLE_INIT_ADD);
		TURNSPEED = eeprom_read_word(TURNSPEED_ADD);
		MSGOUP = eeprom_read_word(MSGOUP_ADD);
		READYSPEEDL = eeprom_read_word(READYSPEEDL_ADD);
		READYSPEEDR = eeprom_read_word(READYSPEEDR_ADD);
		SPEEDPUSH = eeprom_read_word(SPEEDPUSH_ADD);
		MEMORYCYCLE_PUSH = eeprom_read_word(MEMORYCYCLE_PUSH_ADD);
		break;

	case EEP_W:
		eeprom_write_word(AD_WU_ADD, AD_WU);
		eeprom_write_word(AD_WHITE_ADD, AD_WHITE);
		eeprom_write_word(AD_BLACK_ADD, AD_BLACK);
		eeprom_write_word(AD_ADJUST_L_ADD, AD_ADJUST_L );
		eeprom_write_word(AD_ADJUST_R_ADD, AD_ADJUST_R );
		eeprom_write_word(CORNERRATION_ADD, CORNERRATION );
		eeprom_write_word(MODE_ADD, MODE);	
		eeprom_write_word(NODE_L_ADD, NODE_L);
		eeprom_write_word(NODE_R_ADD, NODE_R);
		eeprom_write_word(ATTACKGEAR4_ADD, ATTACKGEAR4);
		eeprom_write_word(ATTACKGEAR3_ADD, ATTACKGEAR3);
		eeprom_write_word(ATTACKGEAR2_ADD, ATTACKGEAR2);
		eeprom_write_word(ATTACKGEAR1_ADD, ATTACKGEAR1);
		eeprom_write_word(ATTACKRATION_ADD, ATTACKRATION);
		eeprom_write_word(SAFESPEED_ADD, SAFESPEED);
		eeprom_write_word(SAFERATION_ADD, SAFERATION);
		eeprom_write_word(TOPSPEED_ADD, TOPSPEED);
		eeprom_write_word(STATECYCLE_ADD, STATECYCLE);
		eeprom_write_word(MEMORYCYCLE_INIT_ADD, MEMORYCYCLE_INIT);
		eeprom_write_word(TURNSPEED_ADD, TURNSPEED);
		eeprom_write_word(MSGOUP_ADD, MSGOUP);
		eeprom_write_word(READYSPEEDL_ADD, READYSPEEDL);
		eeprom_write_word(READYSPEEDR_ADD, READYSPEEDR);
		eeprom_write_word(SPEEDPUSH_ADD, SPEEDPUSH);
		eeprom_write_word(MEMORYCYCLE_PUSH_ADD, MEMORYCYCLE_PUSH);
		break;
	}	
}

/**
	��������
**/
void quickSort(int *a, int i, int j) 
{
	int m, n, temp;
	int k;
	m = i;
	n = j;
	k = a[(i+j)/2];
	do {
		while( a[m]<k && m<j ) m++;
		while( a[n]>k && n>i ) n--;
		if( m <= n ) {
			temp = a[m];
			a[m] = a[n];
			a[n] = temp;
			m++;
			n--;
		}
	} while(m <= n);
	if(m < j) quickSort(a, m, j);
	if(n > j) quickSort(a, i, n);
}
