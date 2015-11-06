#include "watch_dog.h"


void init_watch_dog(void)//初始化看门狗,用汇编才能保证看门狗在4个时钟周期内操作完成
{
   FEED_DOG();
   //MCUCSR &=~0x08
   //WDTCR=0x1f;
   //WDTCR=0x0f;//开看门狗,1.8秒内如果不喂狗AVR将复位
  
   asm volatile ("push r16        \n\t   \
                  ldi  r16,0x1f   \n\t   \
                  out  0x21,r16   \n\t   \
                  ldi  r16,0x0f   \n\t   \
                  out  0x21,r16   \n\t   \
                  pop  r16        \n\t"  );
				  
   FEED_DOG();
}
