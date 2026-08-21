#include "voice.h"


/*
	函数功能：voice引脚初始化
	函数参数：无
	函数返回值：无
	备注：
	VOICE_BUSY    PC4   输入
	VOICE_DATA    PC5   输出
*/
void Voice_Init(void)
{

	//跳转快捷键 ：选中内容然后ctrl+f
	//1.给GPIO控制器提供时钟脉冲信号  -- rcc.c文件
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	//2.配置GPIO控制器函数--让GPIO能正常工作  -- gpio.c文件
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_OUT;    //输出模式
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;    //推挽输出类型
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_5;       //工作引脚
	GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL; //无上下拉电阻
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_25MHz; //中速
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IN;     //输出模式
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_4;       //工作引脚
	GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL; //无上下拉电阻
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	//3.默认不工作
	VOICE_DATA_H;
	Tim2_Delay_ms(100);
}

//Start 3-9 ms
void Voice_Start(void)
{
	VOICE_DATA_L;
	Tim2_Delay_ms(5);
}

/*
	码 0 的高电平时间 T0H  300 - 1000 us
	码 0 的低电平时间 T0L  900 - 3000 us
*/
void Voice_Data_0(void)
{
	VOICE_DATA_H;
	Tim2_Delay_us(500);
	VOICE_DATA_L;
	Tim2_Delay_us(1500);
}


/*
	码 1 的高电平时间 T1H 900 - 3000 us
	码 1 的低电平时间 T1L 300 - 1000 us
*/
void Voice_Data_1(void)
{
	VOICE_DATA_H;
	Tim2_Delay_us(1500);
	VOICE_DATA_L;
	Tim2_Delay_us(500);
}

/*
	发送8位数据，先发低位(0x01)，再发高位(0x80)
	高位在前：
	data = 1010 0100
	1010 0100 & 1000 0000 = 1000 0000  1   data <<= 1
	0100 1000 & 1000 0000 = 0000 0000  0   data <<= 1
	1001 0000 & 1000 0000 = 1000 0000  1  ......

	i = 0; 1010 0100 & 1000 0000 = 1000 0000   1
	i = 1; 1010 0100 & 0100 0000 = 0000 0000   0
	i = 2; 1010 0100 & 0010 0000 = 0010 0000   1
	...
	低位在前：
	1010 0100 & 0000 0001 = 0000 0000    0  data >> 1
	0101 0010 & 0000 0001 = 0000 0000    0  data >> 1
	0010 1001 & 0000 0001 = 0000 0001    1  ....
*/
void Voice_Send_Data(u8 data)
{
	Voice_Start();
	
	for(u8 i = 0; i < 8; i++)
	{
		if(data & (0x01 << i))
		{
			//1
			Voice_Data_1();
		}
		else
		{
			//0
			Voice_Data_0();
		}
	}
}

//发送特定指令
void Voice_Send_Cmd(u8 cmd)
{
	Voice_Send_Data(cmd);
	VOICE_DATA_H;
	while(VOICE_BUSY)
	{
		//时间计数器，计算间隔时间
		static u32 i = 0;
		i++;
		if(i > 30000)
		{
			break;
		}
		Tim2_Delay_us(120);
	}
}














