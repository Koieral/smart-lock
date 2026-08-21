#ifndef _TIM_H   //if not define 预编译处理，防止重定义
#define _TIM_H


#include "stm32f4xx.h"


/*****函数声明*****/
void Tim2_Delay_us(u32 arr);
void Tim2_Delay_ms(u32 arr);

#endif
