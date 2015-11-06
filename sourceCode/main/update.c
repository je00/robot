/*
 *	С��״̬������ط�����ÿ��һ��״̬���ڣ�STATECYCLE������һ��״̬����
 *	@corrector: Ting
 *	@date:	 5th July, 2014
 */
#include "INCLUDES.H"

/*
 *	��ȡ���������£����ڶ�ʱ����
 */
void check_sensor(void)
{
	sensor.io_f = READ_GPIO(IO_F);// ������IO������
	sensor.io_fr = READ_GPIO(IO_FR);
	sensor.io_r = READ_GPIO(IO_R);
	sensor.io_br = READ_GPIO(IO_BR);
	sensor.io_b = READ_GPIO(IO_B);
	sensor.io_bl = READ_GPIO(IO_BL);
	sensor.io_l = READ_GPIO(IO_L);
	sensor.io_fl = READ_GPIO(IO_FL);

	sensor.io_frd = READ_GPIO(IO_FRD);
	sensor.io_brd = READ_GPIO(IO_BRD);
	sensor.io_bld = READ_GPIO(IO_BLD);
	sensor.io_fld = READ_GPIO(IO_FLD);

	read_adc(AD_F,&sensor.ad_f);	// ���Ҷ�ADֵ
	read_adc(AD_L,&sensor.ad_l);
	read_adc(AD_R,&sensor.ad_r);
	
	sensor.ad_l += AD_ADJUST_L;	// �Ҷ�У׼
	sensor.ad_r += AD_ADJUST_R;

	sensor.detectCode = (sensor.io_fl<<7 | sensor.io_l<<6 | sensor.io_bl<<5 | sensor.io_b<<4 
	 			| sensor.io_br<<3 | sensor.io_r<<2 | sensor.io_fr<<1 | sensor.io_f);
	sensor.edgeCode = (sensor.io_frd<<3 | sensor.io_brd<<2 | sensor.io_bld<<1 | sensor.io_fld);
	
	// ��ǰ��⵽���� �� ���������ѵ�
	if(sensor.detectCode != NO_ENEMY || count0 > MEMORYCYCLE) {
		if(count0 > MEMORYCYCLE) {
			if(MODE = 'p' && (vehicle.locEnemyLast = LEFT_ENEMY 
						|| vehicle.locEnemyLast == RIGHT_ENEMY)) 
				vehicle.locEnemyLast = FACE_ENEMY;
		}
		vehicle.locEnemyLast = vehicle.locEnemy; // ˢ���ϴμ�⵽���˵�λ��
		if(flag0) {
			flag0 = 0;
			count0 = 0;
		}
	}
	else if(!flag0) {	// ��ǰ��ⲻ������
		flag0 = 1;	// ��ʱ����ʼ��ʱ
		vehicle.locEnemyLast = vehicle.locEnemy;// ������˵���һ��λ�ã�ֱ����������
	}
	vehicle.locEnemy = sensor.detectCode;	
}

/*
 *	����С���������
 */
void updateTrack(void)
{
	sensor.trackCode = 0;	// �����Ϣ��0

	// front�����Ϣ����
	if (sensor.ad_f > minGreyTrack0) 
		sensor.trackCode |= 0<<4;
	else if (sensor.ad_f > minGreyTrack1) 
		sensor.trackCode |= 1<<4;
	else if (sensor.ad_f > minGreyTrack2) 
		sensor.trackCode |= 2<<4;
	else
		sensor.trackCode |= 3<<4;

	// left�����Ϣ����
	if (sensor.ad_l > minGreyTrack0) 
		sensor.trackCode |= 0<<2;
	else if (sensor.ad_l > minGreyTrack1) 
		sensor.trackCode |= 1<<2;
	else if (sensor.ad_l > minGreyTrack2) 
		sensor.trackCode |= 2<<2;
	else
		sensor.trackCode |= 3<<2;

	// right�����Ϣ����
	if (sensor.ad_r > minGreyTrack0) 
		sensor.trackCode |= 0;
	else if (sensor.ad_r > minGreyTrack1) 
		sensor.trackCode |= 1;
	else if (sensor.ad_r > minGreyTrack2) 
		sensor.trackCode |= 2;
	else
		sensor.trackCode |= 3;	

	ifInRed();	// �ж��Ƿ��ں�ɫ����
}

/*
 *	����С������
 */
void updateDir(void)
{
	INT8U flag = 0;	 // ���������־λ

	switch(sensor.edgeCode) {
	case FACE_EDGE:	 // ����������̨��Ե
	case BACK_EDGE:	 // ����������̨��Ե
	case LEFT_EDGE:	 // ����������̨��Ե
	case RIGHT_EDGE: // ����������̨��Ե
		vehicle.dir = sensor.edgeCode;
		break;
	default:
		flag = 1;	// δ���ֱ�Եλ���������
		
	}
	
	if(flag) {		// ��ͨ����ûҶ��жϳ���
		if( (sensor.ad_f > sensor.ad_l) &&( sensor.ad_f > sensor.ad_r) ) {
			vehicle.dir = BACK_EDGE;
		} 

		else if( (sensor.ad_f < sensor.ad_l) &&( sensor.ad_f < sensor.ad_r) ) {
			vehicle.dir = FACE_EDGE;
		}

		else if( (sensor.ad_r > sensor.ad_f) &&( sensor.ad_f > sensor.ad_l) ) {
			vehicle.dir = LEFT_EDGE;
		}

		else if( (sensor.ad_l > sensor.ad_f) &&( sensor.ad_f > sensor.ad_r) ) {
			vehicle.dir = RIGHT_EDGE;
		}
	}
}

/*
 *	�ж�С���Ƿ���������������
 */
void ifInRed(void)
{	
	if((sensor.ad_f + sensor.ad_l + sensor.ad_r) >= 3*minGreyTrack1) {
		if(sensor.ad_f > AD_WU)	
			SET_1(vehicle.flagRed, 2);	
		else if((sensor.ad_l - sensor.ad_f) > AD_MAXGAP
		 	  ||(sensor.ad_r - sensor.ad_f) > AD_MAXGAP)
			SET_1(vehicle.flagRed, 2);
		else if( (sensor.ad_f > minGreyTrack1) && (vehicle.flagRed & 0x04 != 0) )
			;
		else
			CLE_0(vehicle.flagRed, 2);
												
		if(sensor.ad_l > AD_WU)	
			SET_1(vehicle.flagRed, 1);
		else if((sensor.ad_f - sensor.ad_l) > AD_MAXGAP
		      ||(sensor.ad_r - sensor.ad_l) > AD_MAXGAP)
			SET_1(vehicle.flagRed, 1);
		else if( (sensor.ad_l > minGreyTrack1) && (vehicle.flagRed & 0x02 != 0) )
			;
		else 
			CLE_0(vehicle.flagRed, 1);

		if(sensor.ad_r > AD_WU)	
			SET_1(vehicle.flagRed, 0);
		else if((sensor.ad_f - sensor.ad_r) > AD_MAXGAP
		      ||(sensor.ad_l - sensor.ad_r) > AD_MAXGAP)
			SET_1(vehicle.flagRed, 0);
		else if( (sensor.ad_r > minGreyTrack1) && (vehicle.flagRed & 0x01 != 0) )
			;			
		else
			CLE_0(vehicle.flagRed, 0);
	}
	else
		vehicle.flagRed = 0;

	if(sensor.ad_l > AD_WU || sensor.ad_f > AD_WU || sensor.ad_r > AD_WU) {
		vehicle.track = IN_TRACK0;
		vehicle.dir = FACE_EDGE;
	}
	else 
		vehicle.track = sensor.trackCode;

}


