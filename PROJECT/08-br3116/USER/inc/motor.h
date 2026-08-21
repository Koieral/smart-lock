#ifndef _MOTOR_H
#define _MOTOR_H


#include "stm32f4xx.h"
#include "delay.h"



#define IB_H GPIO_SetBits(GPIOB, GPIO_Pin_3)      //输出高电平1
#define IB_L GPIO_ResetBits(GPIOB, GPIO_Pin_3)    //输出低电平0
#define IA_H GPIO_SetBits(GPIOB, GPIO_Pin_4)      //输出高电平1
#define IA_L GPIO_ResetBits(GPIOB, GPIO_Pin_4)    //输出低电平0


void Motor_Init(void);
void Open_Door(void);
void Close_Door(void);



#endif
