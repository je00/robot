#ifndef _FIGHT_H_
#define _FIGHT_H_

/**
	�������Ϣ����
**/
#define CASE_TRACK0 	case IN_TRACK0:
#define CASE_TRACK1		case IN_TRACK1:\
						case TRACK0_TRACK1_STRI:\
						case TRACK0_TRACK1_SiL:\
						case TRACK0_TRACK1_SiR:\
						case TRACK1_TRACK0_STRI:\
						case TRACK1_TRACK0_SiL:\
						case TRACK1_TRACK0_SiR:
#define CASE_TRACK2 	case IN_TRACK2:\
				    		case TRACK1_TRACK2_STRI:\
					    	case TRACK1_TRACK2_SiL:\
					    	case TRACK1_TRACK2_SiR:\
					    	case TRACK2_TRACK1_STRI:\
					    	case TRACK2_TRACK1_SiL:\
					    	case TRACK2_TRACK1_SiR:
#define CASE_CORNER 	case IN_CORNER:\
					   	case TRACK2_CORNER_STRI:\
					   	case TRACK2_CORNER_SiL:\
					    	case TRACK2_CORNER_SiR:\
					    	case CORNER_TRACK2_STRI:\
					    	case CORNER_TRACK2_SiL:\
					    	case CORNER_TRACK2_SiR:

/**
	�����˷�λ����
**/
#define CASE_FACE_ENEMY	case FACE_ENEMY:\
							case FACE_ENEMY &FRRI_ENEMY &FRLE_ENEMY:

#define CASE_BACK_ENEMY	case BACK_ENEMY:\
							case BACK_ENEMY &BARI_ENEMY &BALE_ENEMY:

#define	CASE_LEFT_ENEMY	case LEFT_ENEMY:\
							case LEFT_ENEMY &FRLE_ENEMY:\
							case LEFT_ENEMY &BALE_ENEMY:\
							case LEFT_ENEMY &FRLE_ENEMY &BALE_ENEMY:

#define CASE_RIGHT_ENEMY	case RIGHT_ENEMY:\
							case RIGHT_ENEMY &FRRI_ENEMY:\
							case RIGHT_ENEMY &BARI_ENEMY:\
							case RIGHT_ENEMY &FRRI_ENEMY &BARI_ENEMY:

#define CASE_FRRI_ENEMY	case FRRI_ENEMY:\
							case FRRI_ENEMY &FACE_ENEMY:
									
#define CASE_FRLE_ENEMY	case FRLE_ENEMY:\
							case FRLE_ENEMY &FACE_ENEMY:

#define CASE_BARI_ENEMY	case BARI_ENEMY:\
							case BARI_ENEMY &BACK_ENEMY:

#define CASE_BALE_ENEMY	case BALE_ENEMY:\
							case BALE_ENEMY &BACK_ENEMY:
/**
	��������
**/
void fighting(void);  
							// Ԥ����������̨�������ս����������̨���ģ������Ե����
							// ���÷�����int main() { init_device(); fight(); }

void edgeDetected(void);	// �ӱ�Ե���룬���ж��е���
void noEnemy(void);			// ��ǰ�޵��ˣ���������̨���Ŀ�����������ɲ��
	
#endif
