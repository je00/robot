#include "watch_dog.h"


void init_watch_dog(void)//��ʼ�����Ź�,�û����ܱ�֤���Ź���4��ʱ�������ڲ������
{
   FEED_DOG();
   //MCUCSR &=~0x08
   //WDTCR=0x1f;
   //WDTCR=0x0f;//�����Ź�,1.8���������ι��AVR����λ
  
   asm volatile ("push r16        \n\t   \
                  ldi  r16,0x1f   \n\t   \
                  out  0x21,r16   \n\t   \
                  ldi  r16,0x0f   \n\t   \
                  out  0x21,r16   \n\t   \
                  pop  r16        \n\t"  );
				  
   FEED_DOG();
}
