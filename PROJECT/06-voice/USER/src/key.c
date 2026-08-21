#include "key.h"


/*
	函数功能：key引脚初始化
	函数参数：无
	函数返回值：无
	备注：
	KEY1   PA0
	KEY2   PC13
	KEY1按下，引脚接收1；松开接收0
	KEY2按下，引脚接收0；松开接收1
*/
void Key_Init(void)
{
	//跳转快捷键 ：选中内容然后ctrl+f
	//1.给GPIO控制器提供时钟脉冲信号  -- rcc.c文件
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOC, ENABLE);
	//2.配置GPIO控制器函数--让GPIO能正常工作  -- gpio.c文件
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IN;     //输入模式
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_0;       //工作引脚
	GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL; //无上下拉电阻
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_13;      //工作引脚
	GPIO_Init(GPIOC, &GPIO_InitStruct);
}


/*
	函数功能：按键扫描检测
	函数参数：无
	函数返回值：u8 键值
	备注：
		当按键按下，返回一个键值（给按键绑定一个序号）
*/
u8 key_scanf(void)  // 1  2  3  4  5
{
	u8 key_value = 0;
	static u8 key_flag = 1;  //1未按下  0按下
	if((KEY1 == 1 || KEY2 == 0) && key_flag == 1)   //1.判断按键按下
	{
		//2.做消抖处理
		delay_ms(15);
		
		//3.进一步判断按下
		if(KEY1==1)
		{
			key_value = 1;
			key_flag = 0;
		}
		if(KEY2 == 0)
		{
			key_value = 2;
			key_flag = 0;
		}
		
	}
	else if(KEY1 == 0 && KEY2 == 1)   //松开
	{
		key_flag = 1;
	}
	return key_value;
}




















