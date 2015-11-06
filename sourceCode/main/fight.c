/*
 * ��սģʽ��ز���
 * @Author: Ting
 * @date: 13th July, 2014
 *@history��
 *	1���޸�Ӧ�Բ��ԣ�������ͬ��λ�������˵������������Ϊһ������
 *	2����дnoEnemy()���������Ӽ������ڵĸ��
 *		��ⲻ�������򽫶��ݼ����ϴ��������˵ķ�λ����ȡ��Ӧ����
 *		@corroctor: Ting
 *		@date: 31th July, 2014
 *	3���Ż��������ĺ���gotoMiddle()
 *		@corroctor:	Ting
 *		@date: 4th April, 2014
 */

#include "INCLUDES.h"

/*
 * �߽�������������
 */
void goToMiddle()
{ 
	switch(vehicle.flagRed) {
	case IN_MIDDLE: 	// ��������		
		goOnSpeed(0);				// ֹͣ
		break;

	case FACE_MIDDLE:	// �������
		goOnSpeed(SAFESPEED);			// ǰ��
		break;

	case BACK_MIDDLE:	// ��������
		goOnSpeed(-1*SAFESPEED);		// ����
		break;
	
	case BALE_MIDDLE:	// �������
	case LEFT_MIDDLE:	// �������
		setSpeed(0, 2*SAFESPEED);
		break;
	
	case BARI_MIDDLE:	// �Һ�����
	case RIGHT_MIDDLE:	// �Ҳ�����
		setSpeed(2*SAFESPEED, 0);
		break;

	default: 		// ���������о��������ֿ���
		switch(vehicle.dir) {
		case BACK_EDGE:		// �������
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
 * û�е��˵����
 */
void noEnemy() 
{	
	// �����ϴ�����ʲô��λ��������
	switch(vehicle.locEnemyLast) {
	
	case NO_ENEMY:
	// ���һ������������û�����������ˣ���ȥ��̨����
		MEMORYCYCLE = MEMORYCYCLE_INIT;
		goToMiddle();
	//	walkInTrack1();
		break;
	
	CASE_FACE_ENEMY
	// ���˴ӻ�������ǰ��������, �����������ڴ��������ǣ�����˵���ȥ��
	// �ӳ��������ڣ������ϴεĹ���
		MEMORYCYCLE = MEMORYCYCLE_INIT; // �������ڼӳ�1s
		fight_FACE_ENEMY();
		break; 
	
	CASE_BACK_ENEMY
	// �����ϴ����Һ���
		noEnemy_BACK_ENEMY();
		break;

	CASE_FRLE_ENEMY
	// �����ϴ�������ǰ��
	CASE_LEFT_ENEMY
	// �����ϴ��������
	CASE_BALE_ENEMY
	// �����ϴ��������
		noEnemy_LEFT_ENEMY();
		break;

	CASE_RIGHT_ENEMY
	// �����ϴ������Ҳ�
	CASE_FRRI_ENEMY
	// �����ϴ�������ǰ��
	CASE_BARI_ENEMY
	// �����ϴ������Һ�
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
 *	û�е��ˣ���һ�α��Ե���
 */
void noEnemy_BACK_ENEMY()
{	
	switch(vehicle.dir) {

	case BACK_EDGE:	// �������
		switch(vehicle.track) {
		// ��Եλ�ã����˿�������Ϊ����ȥ�Ų����ģ���ǰ��һ��
		CASE_CORNER
		CASE_TRACK2
			goOnSpeed(ATTACKGEAR2);
			break;

		default:
			turnOnSpeed(3*TURNSPEED);
			break;
		}		
		break;

	case FACE_EDGE:	// ��������
		switch(vehicle.track) {
		//  ��Եλ�ã����˿�����ʱ�ߵ��ˣ������˳���Ե
		CASE_CORNER
			goOnSpeed(-1*TOPSPEED);
			break;

		default:
			turnOnSpeed(3*TURNSPEED);
			break;
		}

	case LEFT_EDGE:	// �������
		turnOnSpeed(-3*TURNSPEED);
		break;

	case RIGHT_EDGE:// �Ҳ�����
		turnOnSpeed(3*TURNSPEED);
		break;
	}
}

/*
 * û�е��ˣ���һ�ε��������
 */
void noEnemy_LEFT_ENEMY() {
	switch(vehicle.track) {
	CASE_CORNER	// �ڽ���
		switch(vehicle.dir) {
		case BACK_EDGE: // �������,�뿪����
			goOnSpeed(ATTACKGEAR4);
			break;	 
		case FACE_EDGE:	// �������ģ��뿪����
			goOnSpeed(-1*ATTACKGEAR4);
			break;	
		case LEFT_EDGE: // �Ҳ�����,���˿����ǵ���ȥ����ת��������
			turnOnSpeed(TURNSPEED);
			break;
		case RIGHT_EDGE:// �������,��ת�������
			turnOnSpeed(-1*TURNSPEED);
			break;
		}
		break;
	
	// ֱ����ת�ҵ���
	default:
		turnOnSpeed(-2*TURNSPEED);
	}
	
}

/* 
 * û�е��ˣ���һ�ε������Ҳ�
 */
void noEnemy_RIGHT_ENEMY() {
	switch(vehicle.track) {
	CASE_CORNER	// �ڽ���
		switch(vehicle.dir) {
		case BACK_EDGE: // �������,�뿪����
			goOnSpeed(ATTACKGEAR4);
			break;	 
		case FACE_EDGE:	// �������ģ��뿪����
			goOnSpeed(-1*ATTACKGEAR4);
			break;	
		case LEFT_EDGE: // �Ҳ�����,��ת�������
			turnOnSpeed(TURNSPEED);
			break;
		case RIGHT_EDGE:// �������,���˿����ǵ���ȥ����ת��������
			turnOnSpeed(-1*TURNSPEED);
			break;
		}
		break;
	
	// ֱ����ת�ҵ���
	default:
		turnOnSpeed(2*TURNSPEED);
	}
	
}

/* 
 * ��ս���򣬰�������״̬����������������̨���ġ������ԵΣ������
 * ���÷�����int main() { init_device(); fight(); }
 */
void fight() 
{

	// ��������Ե�жϣ�ʹ�������ش���
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
		case NO_ENEMY:	// δ���ֵ���
			noEnemy();
			break;

		CASE_FACE_ENEMY	// ��Ե���
			fight_FACE_ENEMY();
			break;

		CASE_BACK_ENEMY	// ���Ե���
			fight_BACK_ENEMY();
			break;

		CASE_LEFT_ENEMY // ������
			fight_LEFT_ENEMY();
			break;
	
		CASE_RIGHT_ENEMY // �Ҳ����
			fight_RIGHT_ENEMY();
			break;

		CASE_FRRI_ENEMY	 // ��ǰ����
			fight_FRRI_ENEMY();
			break;	

		CASE_FRLE_ENEMY	// ��ǰ����
			fight_FRLE_ENEMY();
			break;	

		CASE_BALE_ENEMY // ������
			fight_BALE_ENEMY();	
		break;

		CASE_BARI_ENEMY // �Һ����
			fight_BARI_ENEMY();
			break;

		default: // ���ܵ������λ��鵽���˵����
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
 *	��ս����Ե���
 */
void fight_FACE_ENEMY()
{
	switch(vehicle.dir) {
	case BACK_EDGE:	// �������
	// ���������ķ��򣬷����������ĳ壬�壡
		goOnSpeed(ATTACKGEAR4);		// �ĵ�����
	break;

	case FACE_EDGE:	// ��������
		switch(vehicle.track) {
		// �ڹ��0���ð�ȫ���尡!
		CASE_TRACK0
			goOnSpeed(ATTACKGEAR3);
			break;
		// ��ʼ�����һ�����̫����ܻ�ɲ��ס������������
		CASE_TRACK1
			goOnSpeed(ATTACKGEAR2);
			break;
		// ��ʼ����ڶ�������е�Σ�գ�ֻ��һ������
		CASE_TRACK2
			goOnSpeed(ATTACKGEAR1); // һ������
			break;
		// �Ѵ����������ˣ���Σ�գ��õ����Լ�����ȥ�ɣ���Ϊ�ϼ�
		CASE_CORNER
			goOnSpeed(-1*TOPSPEED);	// ���ٺ���
			break;
		}
		break;
			
	case LEFT_EDGE: // �Ҳ�����
		switch(vehicle.track) {
		// ��0��1����Ƚϰ�ȫ��ʹ������
		CASE_TRACK0
		CASE_TRACK1
			goOnSpeed(ATTACKGEAR3);
			break;
		// �ڶ��������ɲ��ס��
		CASE_TRACK2
			goOnSpeed(ATTACKGEAR2);
			break;
		// ���������ˣ�Ϊ��ֹ����ȥ������ת��Ա�Ե���л����ٳ���
		CASE_CORNER
			turnOnSpeed(ATTACKGEAR3);
		// ì�ܵ�����������ܷ���
		default:
			break;
		}
		break;

	case RIGHT_EDGE: // �������
		switch(vehicle.track) {
		// �ڵ�0��1������Χ�Ϲ㣬��������
		CASE_TRACK0
		CASE_TRACK1
			goOnSpeed(ATTACKGEAR3);
			break;
		// ��2����е�Σ�գ�ʹ�ö���
		CASE_TRACK2
			goOnSpeed(ATTACKGEAR2);
			break;
		// ���������ˣ�Ϊ��ֹ����ȥ������ת��Ա�Ե���л����ٳ���
		CASE_CORNER
			turnOnSpeed(-1*TURNSPEED);
			break;
		// ì�ܵ�����������ܷ���
		default:
			break;
		}
		break;
	}
}

/*
 *	��ս�������ڱ���
 */
void fight_BACK_ENEMY()
{
	switch(vehicle.dir) {
	case BACK_EDGE:	// �������
		// ���ܱ�ת��
		setSpeed(ATTACKGEAR2, ATTACKGEAR4); 				// ����ǰ�� + ��ת��
		break;

	case FACE_EDGE:	// ��������
		switch(vehicle.track) {
	
		// �ڹ��0�л��Χ�Ϲ㣬����
		case IN_TRACK0:
			setSpeed(ATTACKGEAR2, ATTACKGEAR4);			// ����ǰ�� + ��ת��
			break;

		// �ڹ��1��ֱ��ת��
		CASE_TRACK1
			turnOnSpeed(TURNSPEED);						// ������ת
			break;
					
		// �Ӳ��ˣ��ֿ�!
		default:
			goOnSpeed(-1*TOPSPEED);  
			break;
		}
	break;
				
	case LEFT_EDGE:	// �Ҳ�����
		switch(vehicle.track) {
			
		// ���ڱ�Ե�ش����ܿ��ܳ���ȥ��ֱ��ת��
		CASE_TRACK2
		CASE_CORNER
			turnOnSpeed(TURNSPEED);						// ������ת
			break;

		default: // �������
			setSpeed(ATTACKGEAR4, ATTACKGEAR2);				// ��ǰ�ƽ� + �Ҽ�ת��
			break;
		}
	break;

	case RIGHT_EDGE: // �������
		switch(vehicle.track) {

		// ���ڱ�Ե�ش����ܿ��ܳ���ȥ��ֱ��ת��
		CASE_TRACK2
		CASE_CORNER
			turnOnSpeed(-1*TURNSPEED);			
			break;

		default: // �������
			setSpeed(ATTACKGEAR2, ATTACKGEAR4);			// ��ǰ�ƽ� + ��ת��
			break;
		}
	break;
	}
}

/*
 *	��ս�����������
 *	˼�룺������������
 */
void fight_LEFT_ENEMY()
{
	switch(vehicle.dir) {
	case BACK_EDGE:	// �������
	// ��ǰ�壬�������ˣ�ͬʱŤת����
		setSpeed(ATTACKGEAR2, ATTACKGEAR4);	
		break;

	case FACE_EDGE:	// ��������
	// ����壬��������
		setSpeed(-1*ATTACKGEAR4, -1*ATTACKGEAR2);
		break;

	case LEFT_EDGE:	// �Ҳ�����
		switch(vehicle.track) {
		// ��0��1��������˴��ڱ�Ե�����ҷ�������������������
		CASE_TRACK0
		CASE_TRACK1
			setSpeed(-1*ATTACKGEAR4, -1*ATTACKGEAR2);		// ���ٺ��� + ��ת��
			break;

		// �ڿ�����Եλ�ã����˿����Ѿ�����ȥ�ˣ�����ײ�Ŀ����Բ�����ת��������
		CASE_TRACK2
		CASE_CORNER
			turnOnSpeed(-1*TURNSPEED);
			break;
		}
		break;
			
	case RIGHT_EDGE: // ������ġ������ˣ��ҷ�������
		switch(vehicle.track) {
		// �������ˣ�ͬʱ���￿
		CASE_TRACK0
		CASE_TRACK1
		CASE_TRACK2
			setSpeed(ATTACKGEAR2, ATTACKGEAR4);			// ����ǰ�� + ��ת��
			break;

		// �ڽ������ǰ����ܳ���ȥ�ˣ���ת����
		default:
			turnOnSpeed(-1*TURNSPEED);
			break;
		}
		break;
	}
}

/*
 *	��ս���������Ҳ�
 */
void fight_RIGHT_ENEMY()
{
	switch(vehicle.dir) {
	case BACK_EDGE:	// �������
	// ��ǰ�壬��������
		setSpeed(ATTACKGEAR4, ATTACKGEAR2);			// ����ǰ�� + ��ת��
		break;

	case FACE_EDGE:	// ��������
	// ����壬��������
		setSpeed(-1*ATTACKGEAR2, -1*ATTACKGEAR4);		// ���ٺ��� + ��ת��
		break;

	case RIGHT_EDGE: // �������
		switch(vehicle.track) {

		// ��0��1��������˴��ڱ�Ե�����ҷ�������������������
		CASE_TRACK0
		CASE_TRACK1
			setSpeed(-1*ATTACKGEAR2, -1*ATTACKGEAR4);	// ���ٺ��� + ��ת��
			break;

		// �ڿ�����Եλ�ã����˿����Ѿ�����ȥ�ˣ�����ײ�Ŀ����Բ�����תת��������
		default:
			turnOnSpeed(TURNSPEED);
			break;
		}
		break;

	case LEFT_EDGE:	// �Ҳ�����
		switch(vehicle.track) {			
			// �������ˣ�ͬʱ���￿
		CASE_TRACK0
		CASE_TRACK1
			setSpeed(ATTACKGEAR4, ATTACKGEAR2);		// ����ǰ�� + �Ҽ�ת��
			break;

		// �ڽ������ǰ����ܳ���ȥ�ˣ���ת����
		default:
			turnOnSpeed(TURNSPEED);
			break;
		}
	}
}

/*
 *	��ս����������ǰ��
 */
void fight_FRRI_ENEMY()
{
	switch(vehicle.dir) {
	case BACK_EDGE:	// �������
		setSpeed(ATTACKGEAR4, ATTACKGEAR2);			// ����ǰ�� + �Ҽ�ת��
		break;

	case FACE_EDGE:	// ��������
		switch(vehicle.track) {
		case IN_TRACK0:
			setSpeed(ATTACKGEAR4, ATTACKGEAR2);		// ����ǰ�� + �Ҽ�ת��
			break;

		default:
			turnOnSpeed(TURNSPEED);
			break;
		}
		break;

	case LEFT_EDGE:	// �Ҳ�����
	case RIGHT_EDGE: // �������
		switch(vehicle.track) {
		case IN_TRACK0:
		case IN_TRACK1:
		case TRACK0_TRACK1_SiR:
		case TRACK1_TRACK0_SiL:
			setSpeed(ATTACKGEAR4, ATTACKGEAR2);		// ����ǰ�� + �Ҽ�ת��
			break;
				
		default:
			turnOnSpeed(TURNSPEED);
		break;
		}
	break;
	}
}


/*
 *	��ս����������ǰ��
 */
void fight_FRLE_ENEMY()
{
/*
	switch(vehicle.dir) {
	case RIGHT_EDGE:	// ������ģ��ҷ�����
		switch(vehicle.track) {
		CASE_CORNER
		// �ڽ���λ�ã���ת����
			turnOnSpeed(TURNSPEED);
			break;
		// ����λ����ת��׼����
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
		case BACK_EDGE:		// �������
			setSpeed(ATTACKGEAR2, ATTACKGEAR4);			// ����ǰ�� + ��ת��
		break;

		case FACE_EDGE:		// ��������
			switch(vehicle.track) {
			case IN_TRACK0:
				setSpeed(ATTACKGEAR2, ATTACKGEAR4);		// ����ǰ�� + ��ת��
			break;

			default:
				turnOnSpeed(-1*TURNSPEED);
			break;
			}
		break;

		case LEFT_EDGE:		// �Ҳ�����
		case RIGHT_EDGE:	// �������
			switch(vehicle.track) {
			case IN_TRACK0:
			case IN_TRACK1:
			case TRACK0_TRACK1_SiR:
			case TRACK1_TRACK0_SiL:
				setSpeed(ATTACKGEAR2, ATTACKGEAR4);		// ����ǰ�� + ��ת��
			break;
				
			default:
				turnOnSpeed(-1*TURNSPEED);
			break;
			}
		break;
		}
}

/*
 *	��ս�����������
 */
void fight_BALE_ENEMY()
{
	switch(vehicle.dir) {

	case BACK_EDGE:		// �������
	// ���ܱ�ת��
		setSpeed(ATTACKGEAR2, ATTACKGEAR4); 			// ����ǰ�� + ��ת��
		break;

	case FACE_EDGE:		// ��������
		switch(vehicle.track) {
	
		// �ڹ��0�л��Χ�Ϲ㣬����
		case IN_TRACK0:
			setSpeed(ATTACKGEAR2, ATTACKGEAR4);		// ����ǰ�� + ��ת��
			break;

		// �ڹ��1��ֱ��ת��
		CASE_TRACK1
			turnOnSpeed(-1*TURNSPEED);					// ������ת
			break;			
		// �Ӳ��ˣ��ֿ�!
		default:
			goOnSpeed( -1*TOPSPEED);  
			break;
		}
		break;
	}
}

/*
 *	��ս���������Һ�
 */
void fight_BARI_ENEMY()
{
	switch(vehicle.dir) {
		
	case BACK_EDGE:		// �������
	// ���ܱ�ת��
		setSpeed(ATTACKGEAR4, ATTACKGEAR2);			// ����ǰ�� + �Ҽ�ת��
		break;

	case FACE_EDGE:		// ��������
		switch(vehicle.track) {
	
		// �ڹ��0�л��Χ�Ϲ㣬����
		case IN_TRACK0:
			setSpeed(ATTACKGEAR4, ATTACKGEAR2);		// ����ǰ�� + �Ҽ�ת��
			break;

		// �ڹ��1��ֱ��ת��
		CASE_TRACK1
			turnOnSpeed(TURNSPEED);					// ������ת
			break;		
		// �Ӳ��ˣ��ֿ�!
		default:
			setSpeed(-1*ATTACKGEAR2, -1*ATTACKGEAR4);  // ���ٺ��� + �Ҽ�ת��
			break;
		}
		break;
	}
}

/**
	��Ե����ж� 
	@IO��  1
	@��λ���Һ�
**/
SIGNAL(INT4_vect){
	cli();

//	uart1_put_str("�Һ��ж�\n");
	edgeDetected();

	sei();

}

/**
	��Ե����ж�2
	@IO  ��  0
	@��λ����ǰ
**/
SIGNAL (INT5_vect)
{
	cli();

//	uart1_put_str("��ǰ�ж�\n");
	edgeDetected();

	sei();
}

/**
	��Ե����ж�3
	@IO : 3
	@��λ �����
**/
SIGNAL (INT6_vect)
{
	cli();

//	uart1_put_str("����ж�\n");
	edgeDetected();

	sei();
}

/**
	��Ե����ж�4
	@IO : 2
	@��λ����ǰ
**/
SIGNAL (INT7_vect)
{
	cli();

//	uart1_put_str("��ǰ�ж�\n");
	edgeDetected();

	sei();
}
/**
	��⵽��Եʱ����Σ������
**/
void edgeDetected() {

	int flagInEdge = 1;		// ��ǰ���ڱ�Ե�ش�
	packDanger();
	while(flagInEdge) {	
		txData();
		// ˢ�±�Ե������
		sensor.io_frd	=READ_GPIO(IO_FRD);
	 	sensor.io_brd	=READ_GPIO(IO_BRD);
	 	sensor.io_bld	=READ_GPIO(IO_BLD);
     	sensor.io_fld	=READ_GPIO(IO_FLD);
		sensor.edgeCode = (sensor.io_frd<<3 | sensor.io_brd<<2 | sensor.io_bld<<1 | sensor.io_fld);

		switch(sensor.edgeCode) {
		case BACK_EDGE:		// ���������Ե 
			goOnSpeed(TOPSPEED);
			break;

		case FACE_EDGE:		// ��ǰ�������Ե
			goOnSpeed(-1*TOPSPEED);
			break;

		case LEFT_EDGE:		// ��������Ե
			setSpeed(TOPSPEED, 0);
			break;

		case RIGHT_EDGE:	// �Ҳ������Ե
			setSpeed(0, TOPSPEED);
			break;

		case FRRI_EDGE:		// ��ǰ�������Ե
		case BALE_RING:		// ֻ���������̨��
			setSpeed(0, -1*TOPSPEED);
			break;

		case FRLE_EDGE:		// ��ǰ�������Ե
		case BARI_RING:		// ֻ���Һ�����̨��
			setSpeed(-1*TOPSPEED, 0);
			break;

		case BARI_EDGE:		// �Һ������Ե
		case FRLE_RING:		// ֻ����ǰ������̨��
			setSpeed(0, TOPSPEED);
			break;
	
		case BALE_EDGE:		// ��������Ե
		case FRRI_RING:		// ֻ����ǰ������̨��
			setSpeed(TOPSPEED, 0);
			break;

		default:
			flagInEdge = 0;	// �ѳɹ������Ե
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

