#include "main.h"




int main(void)
{
	
	Led_Init();
	Key_Init();
	Motor_Init();
	Usart_Init(115200);
	Voice_Init();
	
	
	printf("初始化完成...\r\n");
	

	Tim2_Delay_ms(200);
	Voice_Send_Cmd(0X18);
	Tim2_Delay_ms(3000);
	Voice_Send_Cmd(0XEF);       //音量最大
	
	
	while(1)
	{
		
		Tim2_Delay_ms(1000);
		printf("111\r\n");
		
	}
}




