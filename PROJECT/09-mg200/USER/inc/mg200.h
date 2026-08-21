#ifndef _MG200_H
#define _MG200_H

#include "stm32f4xx.h"
#include "stdio.h"
#include "delay.h"
#include "voice.h"
#include "motor.h"

#define MG200_PWR_OFF  (GPIO_ResetBits(GPIOC,GPIO_Pin_1))
#define MG200_PWR_ON   (GPIO_SetBits(GPIOC,GPIO_Pin_1))

#define MG200_DETECT   (GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0))


typedef struct{

	u8 buff[128];    //保存接受数据
	u16 len;				 //记录数据长度
	u8 flag;         //接收数据完成标志位    0：还没有接收到数据   1：接收到数据

}U6_STRUCT;

extern U6_STRUCT u6;

void Usart6_Init(u32 bps);
void usart6_send_byte(u8 data);
void usart6_send_str(u8 *data);
void Mg200_Init(void);

u8 CaptureAndExtract(u8 num);//提取指纹特征量
u8 Enroll(void);
u8 Match1N(void);
void Mg200_Open_Door(void);

#endif
