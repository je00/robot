

#include "INCLUDES.h"

int main()
{	
	// �ް������� AD_CHECK_IO �� ���°����������������
	if( read_adc2(AD_CHECK_IO) < 512 ) { _delay_ms(200);	// ����
	if( read_adc2(AD_CHECK_IO) < 512 ) { 
		init_device();
		fight();
	}}

	// �������� AD_CHECK_IO �� ��������, ����������ó���ʹ�ó����նˣ�
	else	
		menu();
}

