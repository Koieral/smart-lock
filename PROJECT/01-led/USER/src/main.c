#include "main.h"




int main(void)
{
	
	Led_Init();
	//lcd
	//key
	
	
	while(1)
	{
		//иак╦
//		GPIO_SetBits(GPIOB, GPIO_Pin_8);   //1
//		delay_ms(500);
//		GPIO_ResetBits(GPIOB, GPIO_Pin_8); //0
//		delay_ms(500);
		
		Led_Breath();
	}
}




