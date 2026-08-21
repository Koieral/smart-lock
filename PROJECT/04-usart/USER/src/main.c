#include "main.h"




int main(void)
{
	u8 value = 0;
	
	
	Led_Init();
	Key_Init();
	Motor_Init();
	Usart_Init(115200);
	
	printf("初始化完成...\r\n");
	
//	Usart1_Send_Data('a');
//	printf("\r\n");
//	
//	value = Usart1_Rec_Data(); 
//	printf("value=%c \r\n", value);
//	
//	Usart1_Send_String("asdf");
	
	
	
	while(1)
	{
		Usart1_Rec_String();
//		//闪烁
//		GPIO_SetBits(GPIOB, GPIO_Pin_8);   //1
//		delay_ms(500);
//		GPIO_ResetBits(GPIOB, GPIO_Pin_8); //0
//		delay_ms(500);
		
		//当接收到指令"led_on",led亮；接收到"led_off"，led灭
		//strcmp字符对比函数
		
	}
}




