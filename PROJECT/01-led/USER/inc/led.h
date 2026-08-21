#ifndef _LED_H   //if not define 预编译处理，防止重定义
#define _LED_H




#include "stm32f4xx.h"
#include "delay.h"



/*****函数声明*****/
void Led_Init(void);
void Led_Breath(void);

#endif
