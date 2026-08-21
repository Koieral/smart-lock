#include "main.h"




int main(void)
{
	u8 key = 0;
	
	Led_Init();
	Key_Init();
	
	
	while(1)
	{
	
		key = key_scanf(); //1 2
		if(key == 1)
			LED_G_OFF;
		if(key==2)
			LED_G_ON;
			
		//иак╦
//		GPIO_SetBits(GPIOB, GPIO_Pin_8);   //1
//		delay_ms(500);
//		GPIO_ResetBits(GPIOB, GPIO_Pin_8); //0
//		delay_ms(500);
		
		//Led_Breath();
	}
}




