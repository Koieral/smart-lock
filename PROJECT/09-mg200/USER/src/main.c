#include "main.h"




char ch[] = {0x00,0x00,0x00,0x10,0x10,0x18,0x28,0x28,0x24,0x3C,0x44,0x42,0x42,0xE7,0x00,0x00};/*"A",0*/

int main(void)
{
	
	Led_Init();
	Key_Init();
	Motor_Init();
	Usart_Init(115200);
	Voice_Init();
	LCD_Init();
	CY8CMBR3116_Init();
	Mg200_Init();
	
	printf("初始化完成...\r\n");
	
//	Lcd_Show_Ch(100, 100, RED, YELLOW, 1, ch);
//	Lcd_Show_Ch(80, 100, RED, YELLOW, 0, ch);
//	Lcd_Show_Szie_Ch(100, 100, RED, YELLOW, 1, 16, 'c');
//	Lcd_Show_Szie_Ch(80, 100, RED, YELLOW, 0, 32, '~');
//	Lcd_Show_Szie_Hz(80, 100, RED, YELLOW, 0, 16, (u8*)"你");
//	Lcd_Show_Szie_Hz(80, 140, RED, YELLOW, 0, 32, (u8*)"你");
//	Lcd_Show_Szie_String(80, 140, RED, YELLOW, 0, 32, (u8*)"asd你好fgh");
//	Tim2_Delay_ms(200);
//	Voice_Send_Cmd(0X18);
//	Tim2_Delay_ms(3000);
//	Voice_Send_Cmd(0XEF);       //音量最大
	
//	for(u8 i = 0; i < 100; i++)
//	{
//		LCD_Point(100,  100+i, RED);
//	}
//	
	
	//Lcd_Show_Pic(100, 100, (u8*)gImage_pig);
	
	while(1)
	{
		//BR3116_Open_Door();
		//Enroll();
		
		//Match1N();
		
		Mg200_Open_Door();
	}
}




