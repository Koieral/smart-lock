#include "main.h"




int main(void)
{
	
	Led_Init();
	Key_Init();
	Motor_Init();
	Usart_Init(115200);
	
	printf("初始化完成...\r\n");
	

	
	
	while(1)
	{
		
		Tim2_Delay_ms(1000);
		printf("111\r\n");
		
	}
}




