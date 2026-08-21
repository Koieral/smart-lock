#ifndef _LED_H   //if not define 预编译处理，防止重定义
#define _LED_H




#include "stm32f4xx.h"
#include "delay.h"


#define LED_R_OFF GPIO_SetBits(GPIOB, GPIO_Pin_8)   //1
#define LED_R_ON  GPIO_ResetBits(GPIOB, GPIO_Pin_8) //0
#define LED_G_OFF GPIO_SetBits(GPIOB, GPIO_Pin_9)   //1
#define LED_G_ON  GPIO_ResetBits(GPIOB, GPIO_Pin_9) //0


/*****函数声明*****/
void Led_Init(void);
void Led_Breath(void);

#endif
