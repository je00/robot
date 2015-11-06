#ifndef _UPDATE_H
#define _UPDATE_H



/**
	1、存储传感器的状态
	2、包括红外与灰度，以及各种通过传感器状态计算得出的状态码	
**/
struct SENSOR	//传感器返回值变量结构体
{
	INT8U io_f;			// 前，红外IO传感器状态值变量
	INT8U io_fl;		// 前左
	INT8U io_fr;
	INT8U io_b;
	INT8U io_bl;
	INT8U io_br;
	INT8U io_r;
	INT8U io_l;
	INT8U io_fld;		// 前左斜向下
	INT8U io_frd;
	INT8U io_bld;
	INT8U io_brd;

	INT16U ad_f;		// 前，灰度AD传感器状态值变量
	INT16U ad_l;	
	INT16U ad_r;
	
	// 状态编码
	INT8U detectCode;	// 检测敌人的红外传感器编码
	INT8U trackCode;	// 根据灰度值进行轨道编码
	INT8U edgeCode;		// 边缘红外传感器编码

}sensor;

/**
	接线
**/
#define IO_F		GPIO4		//前，红外IO传感器id
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

#define AD_F		0			//前，灰度AD传感器id
#define AD_L		2
#define AD_R		1





#endif

