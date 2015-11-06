#ifndef _UPDATE_H
#define _UPDATE_H



/**
	1���洢��������״̬
	2������������Ҷȣ��Լ�����ͨ��������״̬����ó���״̬��	
**/
struct SENSOR	//����������ֵ�����ṹ��
{
	INT8U io_f;			// ǰ������IO������״ֵ̬����
	INT8U io_fl;		// ǰ��
	INT8U io_fr;
	INT8U io_b;
	INT8U io_bl;
	INT8U io_br;
	INT8U io_r;
	INT8U io_l;
	INT8U io_fld;		// ǰ��б����
	INT8U io_frd;
	INT8U io_bld;
	INT8U io_brd;

	INT16U ad_f;		// ǰ���Ҷ�AD������״ֵ̬����
	INT16U ad_l;	
	INT16U ad_r;
	
	// ״̬����
	INT8U detectCode;	// �����˵ĺ��⴫��������
	INT8U trackCode;	// ���ݻҶ�ֵ���й������
	INT8U edgeCode;		// ��Ե���⴫��������

}sensor;

/**
	����
**/
#define IO_F		GPIO4		//ǰ������IO������id
#define IO_FL		GPIO11
#define IO_FR		GPIO5
#define IO_B		GPIO8
#define IO_BL		GPIO9
#define IO_BR		GPIO7	
#define IO_L		GPIO10	
#define IO_R		GPIO6
#define IO_FLD		GPIO3
#define IO_FRD		GPIO0
#define IO_BLD		GPIO2
#define IO_BRD		GPIO1

#define AD_F		0			//ǰ���Ҷ�AD������id
#define AD_L		2
#define AD_R		1





#endif

