#ifndef _CODE_H_
#define _CODE_H_

/**
	1��������루�Ҷȴ�������vehicle.track��
	2��00(��Ч) --(front) --(left) --(right)
	3��track0: 00	track1: 01	track2: 10	`corner: 11
	@author: Ting
**/
#define	IN_TRACK0 0x00	// ���ڹ��0 (00 00 00 00��
#define IN_TRACK1 0x15 	// ���ڹ��1 (00 01 01 01)
#define IN_TRACK2 0x2A	// ���ڹ��2 (00 10 10 10)
#define IN_CORNER 0x3f	// ���ڽ���	 (00 11 11 11)

// ��һ�����������һ�������ֱ�ӽ��루ǰ���ѽ��룬����δ���룩
#define TRACK0_TRACK1_STRI 0x10	// �ӹ��0������1 (00 01 00 00)
#define TRACK1_TRACK2_STRI 0x25	// �ӹ��1������2 (00 10 01 01)
#define TRACK2_CORNER_STRI 0x3A	// �ӹ��2�������  (00 11 10 10)

#define CORNER_TRACK2_STRI 0x2F	// �ӽ��������2  (00 10 11 11)
#define TRACK2_TRACK1_STRI 0x1A	// �ӹ��2������1 (00 01 10 10)
#define TRACK1_TRACK0_STRI 0x05	// �ӹ��1������0 (00 00 01 01)

// ��һ�����������һ��������Ҳ��Ƚ��루���ֽ��룬����ͣ��ԭ�����
#define TRACK0_TRACK1_SiR 0x11	// �ӹ��0������1 (00 01 00 01)
#define TRACK1_TRACK2_SiR 0x26	// �ӹ��1������2 (00 10 01 10)
#define TRACK2_CORNER_SiR 0x3B	// �ӹ��2�������  (00 11 10 11)

#define CORNER_TRACK2_SiR 0x2E	// �ӽ��������2  (00 10 11 10)
#define TRACK2_TRACK1_SiR 0x19	// �ӹ��2������1 (00 01 10 01)
#define TRACK1_TRACK0_SiR 0x04	// �ӹ��1������0 (00 00 01 00)

// ��һ�����������һ�����������Ƚ��루���ֽ��룬����ͣ��ԭ�����
#define TRACK0_TRACK1_SiL 0x14	// �ӹ��0������1 (00 01 01 00)
#define TRACK1_TRACK2_SiL 0x29	// �ӹ��1������2 (00 10 10 01)
#define TRACK2_CORNER_SiL 0x3E	// �ӹ��2�������  (00 11 11 10)

#define CORNER_TRACK2_SiL 0x2B	// �ӽ��������2  (00 10 10 11)
#define TRACK2_TRACK1_SiL 0x16	// �ӹ��2������1 (00 01 01 10)
#define TRACK1_TRACK0_SiL 0x01	// �ӹ��1������0 (00 00 00 01)


/**
	1����ɫ�����־λ��trackCode��10��9��8λ��������8λ�����ж�
	2��00 00 0(��Ч) -(front) -(left) -(right)
	3��0�������ں�ɫ���� 	1�����ں�ɫ����
	@author: Ting
**/
#define IN_MIDDLE 		0x07	// ���崦�ں�ɫ����			(111)			
#define FACE_MIDDLE		0x04	// ǰ�ֽ����ɫ����			(100)
#define BACK_MIDDLE		0x03	// �������ֽ����ɫ����		(011)	
#define LEFT_MIDDLE		0x06	// ǰ�������ֽ����ɫ����	(110)
#define RIGHT_MIDDLE	0x05	// ǰ�ֺ����ֽ����ɫ����	(101)
#define BALE_MIDDLE 	0x02	// ֻ�����ֽ����ɫ����		(010)
#define BARI_MIDDLE		0x01 	// ֻ�����ֽ����ɫ����		(001)

/**
	1����ͨ���⴫�����������ˣ����� sensor.detectCode
	2��-(fl)-(l)-(bl)-(b)-(br)-(r)-(fr)-(f)
	@author: Ting
**/
#define NO_ENEMY		0xff		// ��ⲻ������
#define FACE_ENEMY 		0xfe		// ���Ե���
#define BACK_ENEMY  	0xef		// ���Ե���
#define LEFT_ENEMY		0xbf		// ���������
#define RIGHT_ENEMY		0xfb		// �������Ҳ�
#define	FRRI_ENEMY		0xfd		// ��������ǰ��	
#define FRLE_ENEMY		0x7f		// ��������ǰ��
#define BARI_ENEMY		0xf7		// �������Һ�
#define BALE_ENEMY		0xdf		// ���������

/**
	����Ե���⴫���������Ʊ���
		 ǰ
	λ0       λ3����ǰ��Ե��⣩

	λ1       λ2
	@author: Ting
**/
#define BACK_EDGE	0x06		// ����������̨��Ե
#define FACE_EDGE	0x09		// ����������̨��Ե
#define LEFT_EDGE	0x03		// ���������̨��Ե
#define RIGHT_EDGE	0x0c		// �Ҳ�������̨��Ե
#define FRRI_EDGE	0x08		// ��ǰ������̨��Ե
#define FRLE_EDGE	0x01		// ��ǰ������̨��Ե
#define BARI_EDGE	0x04		// �Һ�����̨��Ե
#define BALE_EDGE	0x02		// �������̨��Ե
#define FRLE_RING	0x0E		// ֻ����ǰ������̨��
#define FRRI_RING	0x07		// ֻ����ǰ������̨�� 	
#define BALE_RING	0x0D		// ֻ���������̨��
#define BARI_RING	0x0B		// ֻ���Һ�����̨��

#endif
