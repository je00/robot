// ppm.c : Defines the entry point for the console application.
//

#define MAX_PPM 8


#include "ppm.h"
#include "mytimer.h"


typedef struct
{
	INT16U us;//保持高电平时间
	INT8U id;
}SPpmState;
typedef struct
{
	SPpmState ppms[MAX_PPM];
	INT8U size;
	INT16U circle_us;//ppm周期 20ms
	INT8U state;
}SPpm;
volatile SPpm ppm;
INT16U t;
void SetPpmIO(INT8U id,BOOLEAN v)
{
	switch(id)
	{
	case 0:
		WRITE_GPIO(PPM0,v);
		break;
	case 1:
		WRITE_GPIO(PPM1,v);
		break;
	case 2:
		WRITE_GPIO(PPM2,v);
		break;
	case 3:
		WRITE_GPIO(PPM3,v);
		break;
	case 4:
		WRITE_GPIO(PPM4,v);
		break;
	case 5:
		WRITE_GPIO(PPM5,v);
		break;
	case 6:
		WRITE_GPIO(PPM6,v);
		break;
	case 7:
		WRITE_GPIO(PPM7,v);
		break;
	}
}

#define SETTIMER1MS() 	cli();TCCR0=4;				TCNT0=256-(1*4*F_CPU/1000/256); TIFR=0x01;	TIMSK|=0x01;sei();
#define SETTIMER1MSC() TCNT0=256-(1*4*F_CPU/1000/256);

SIGNAL(SIG_OVERFLOW0)
{
	INT8U i=0;
	switch(ppm.state)
	{
	case 0:
		for(i=0; i<ppm.size; i++)
			SetPpmIO(ppm.ppms[i].id,ppm.ppms[i].us!=0);
		ppm.state++;
		//delay_us(1000);
	break;
	case 1:
		if(ppm.size>0)
		{
			delay_us(ppm.ppms[0].us);//-(TCNT0>>2));
			SetPpmIO(ppm.ppms[0].id,0);
			for(i=1; i<ppm.size; i++)
			{
				delay_us(ppm.ppms[i].us-ppm.ppms[i-1].us);
				SetPpmIO(ppm.ppms[i].id,0);
			}
			delay_us(1000-ppm.ppms[i-1].us+100);
		}
		ppm.state++;
	break;
	default:
		ppm.state++;
		if(ppm.state>=19)
			ppm.state=0;
	break;
	}
	SETTIMER1MSC();
}
						//设置定时为多少  ,128 	//清中断标志位				//使能定时器0溢出中断


void InitPpm(INT32U circle_us)
{
	INT8U i=0;
	ppm.circle_us=circle_us;
	ppm.size=0;
	for(i=0; i<MAX_PPM; i++)
	{
		ppm.ppms[i].us=0;
		ppm.ppms[i].id=0;
	}
	SETTIMER1MS();
}

void SetPpm(int id,INT16U us)
{
	INT8U i=0,j=0;
	BOOLEAN change=0;
	SPpmState tmp;

	for(i=0; i<ppm.size; i++)
	{
		if(id==ppm.ppms[i].id)
		{
			if(ppm.ppms[i].us!=us)
			{
				ppm.ppms[i].us=us;
				change=1;
			}
			break;
		}
	}
	if(i==ppm.size)
	{
		ppm.ppms[ppm.size].id=id;
		ppm.ppms[ppm.size].us=us;
		change=1;
		ppm.size++;
	}
	if(change==1)
	{
		for(i=0; i<ppm.size; i++)
			for(j=i+1; j<ppm.size; j++)
			{
				if(ppm.ppms[i].us>ppm.ppms[j].us)
				{
					tmp=ppm.ppms[i];
					ppm.ppms[i]=ppm.ppms[j];
					ppm.ppms[j]=tmp;
				}
			}
	}
}
void SetMotor(INT8U id,INT16S sp)
{
	SetPpm(id,530+sp/2);	//robot_hight调整参数
}


