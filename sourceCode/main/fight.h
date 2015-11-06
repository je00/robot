#ifndef _FIGHT_H_
#define _FIGHT_H_

/**
	各轨道信息整合
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
	各敌人方位整合
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
	函数声明
**/
void fighting(void);  
							// 预备，走上擂台，与敌人战斗，走向擂台中心，陷入边缘抽离
							// 调用方法：int main() { init_device(); fight(); }

void edgeDetected(void);	// 从边缘抽离，在中断中调用
void noEnemy(void);			// 当前无敌人，尽量往擂台中心靠，到达中心刹车
	
#endif
