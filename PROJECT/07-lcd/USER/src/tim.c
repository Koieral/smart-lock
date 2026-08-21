#include "tim.h"


//功能函数在tim.c文件

void Tim2_Delay_us(u32 arr)  //1us
{
	//1.时钟脉冲
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	//2.定时器控制器配置
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = {0};
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode   = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period        = arr-1;
	TIM_TimeBaseInitStructure.TIM_Prescaler     = 81-1;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	//3清除更新标志位（防止上次残留的标志导致立刻跳出循环）
	TIM_ClearFlag(TIM2, TIM_FLAG_Update); 
	//4开启定时器
	TIM_Cmd(TIM2, ENABLE);
	//5阻塞等待：一直读状态标志位，直到定时器溢出
	while(TIM_GetFlagStatus(TIM2, TIM_FLAG_Update) == RESET);
}



void Tim2_Delay_ms(u32 arr)  //1us
{
	//1.时钟脉冲
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	//2.定时器控制器配置
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = {0};
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode   = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period        = arr*10-1;
	TIM_TimeBaseInitStructure.TIM_Prescaler     = 8400-1;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	//3清除更新标志位（防止上次残留的标志导致立刻跳出循环）
	TIM_ClearFlag(TIM2, TIM_FLAG_Update); 
	//4开启定时器
	TIM_Cmd(TIM2, ENABLE);
	//5阻塞等待：一直读状态标志位，直到定时器溢出
	while(TIM_GetFlagStatus(TIM2, TIM_FLAG_Update) == RESET);
}


















