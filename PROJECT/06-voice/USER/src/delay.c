#include "delay.h"

/*
Function name:Delay_us
Description:us延时
param:ustime--延时时长
retval:None
Remarks:
主频(84MHz)-----1S处理84M条指令
						-----1us处理84条指令
						
	1/82MHz≈1个机器周期时间 * nop个数 = 1us
	1us执行时间
*/
void delay_us(u32 ustime)  //1us
{
	while(ustime--)
	{
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();
	}
}



//毫秒延时
void delay_ms(u32 mstime)  //1ms
{
	while(mstime--)
	{
		delay_us(1000);
	}
}









