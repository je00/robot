#ifndef __WATCH_DOG_H__
#define __WATCH_DOG_H__

#include "includes.h"

//喂狗
#define FEED_DOG() asm("wdr")

//初始化看门狗。1.9秒内如果不喂狗将复位
void init_watch_dog(void);


#endif
