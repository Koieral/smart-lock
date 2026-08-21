#include "motor.h"


/*
	函数功能：motor初始化
	函数参数：无
	函数返回值：无
	备注：PB3   推挽输出   0      1       1
				PB4   推挽输出   1      0       1
												转动    转动    停止 
*/
void Motor_Init(void)
{
	//1.开时钟-- rcc.c文件
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);   //GPIOB时钟使能
	
	//2.配置结构体，IO口控制器输出需要的电平信号 -- gpio.c文件
	GPIO_InitTypeDef GPIO_InitStructure = {0};
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;   					//输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;						//推挽类型
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_3 | GPIO_Pin_4;  //指定配置引脚
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;         //无上下拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;					//低速
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//3.输出需要电平信号
	IB_H;
	IA_H;
}


//开门函数
void Open_Door(void)
{
	IB_H;
	IA_L;
	delay_ms(1000);
	IB_H;
	IA_H;
}


void Close_Door(void)
{
	IB_L;
	IA_H;
	delay_ms(1000);
	IB_H;
	IA_H;
}

































