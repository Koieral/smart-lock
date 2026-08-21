#ifndef _KEY_H   //if not define 预编译处理，防止重定义
#define _KEY_H




#include "stm32f4xx.h"
#include "delay.h"


#define KEY1 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)  //1  0
#define KEY2 GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13)


/*****函数声明*****/
void Key_Init(void);
u8 key_scanf(void);



#endif