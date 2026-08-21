#ifndef _USART_H   //if not define 预编译处理，防止重定义
#define _USART_H




#include "stm32f4xx.h"
#include "stdio.h"
#include "string.h"
#include "led.h"

typedef struct
{
	u8 data[255];  //存储接收的数据
	u8 index;      //数组长度
	//u8 flag;       //判断数据接收完成
}Usart1;



/*****函数声明*****/
void Usart_Init(u32 baud);
void Usart1_Send_Data(u8 data);
u8 Usart1_Rec_Data(void) ;
void Usart1_Send_String(u8* data);
void Usart1_Rec_String(void);


#endif
