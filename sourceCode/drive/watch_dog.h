#ifndef __WATCH_DOG_H__
#define __WATCH_DOG_H__

#include "includes.h"

//ι��
#define FEED_DOG() asm("wdr")

//��ʼ�����Ź���1.9���������ι������λ
void init_watch_dog(void);


#endif
