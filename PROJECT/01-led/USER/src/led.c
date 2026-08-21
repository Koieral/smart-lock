#include "led.h"

/*
	函数功能：led引脚初始化
	函数参数：无
	函数返回值：无
	备注：
	LED_R   PB8
	LED_G   PB9
	引脚输出低电平0V（0），led亮；输出高电平3.3V（1），led灭
*/
void Led_Init(void)
{

	//跳转快捷键 ：选中内容然后ctrl+f
	//1.给GPIO控制器提供时钟脉冲信号  -- rcc.c文件
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	//2.配置GPIO控制器函数--让GPIO能正常工作  -- gpio.c文件
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_OUT;    //输出模式
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;    //推挽输出类型
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_8 | GPIO_Pin_9;       //工作引脚
	GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL; //无上下拉电阻
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;  //低速
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	//3.调用函数输出对应的信号
	GPIO_SetBits(GPIOB, GPIO_Pin_8);   //1
	//GPIO_ResetBits(GPIOB, GPIO_Pin_8); //0
	GPIO_SetBits(GPIOB, GPIO_Pin_9);   //1
	//GPIO_ResetBits(GPIOB, GPIO_Pin_9); //0
}


//LED_R实现呼吸灯
void Led_Breath(void)
{
	//暗->亮
	for(u32 i = 0; i < 1000; i++)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_8);   //1000  999  998  997 ...
		delay_us(1000-i);
		GPIO_ResetBits(GPIOB, GPIO_Pin_8); //0     1    2    3   ...
		delay_us(i);
	}
	//亮->暗
	for(u32 i = 0; i < 1000; i++)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_8);   //1000  999  998  997 ...
		delay_us(i);
		GPIO_ResetBits(GPIOB, GPIO_Pin_8); //0     1    2    3   ...
		delay_us(1000-i);
	}
}




