#include "lcd.h"



/*
函数功能：LCD_IO初始化
参数：无
返回值：无
备注：PB1/PB10/PB12/PB13/PB14/PB15--->通用推挽输出
*/
void LCD_Pin_Init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);//打开PB时钟
	GPIO_InitTypeDef GPIO_InitStructure={0};
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//通用输出模式
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1|GPIO_Pin_10|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;//引脚
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	LEDK = 0;
	LCD_RESET = 1;
	LCD_CS = 1;
}



/*
函数功能：模拟SPI数据发送
参数：u8 data
返回值：无
备注：PB1/PB10/PB12/PB13/PB14/PB15--->通用推挽输出
	数据高位先出  
data = 0101 1101  &  1000 0000   = 0000 0000
data = ....
*/
void SPI_Send_Data(u8 data)
{
	//1.时钟线拉高  -- 默认不工作状态
	SPI2_SCLK = 1;
	//2.发送数据  for循环发送8bit，高位在前 如果为1，则代表数据1，否则数据0
	for(u8 i = 0; i < 8; i++)
	{
		//3.拉低时钟线 - 产生下降沿
		SPI2_SCLK = 0;  
		if(data & (0x80 >> i))
		{
			SPI2_MOSI = 1;
		}
		else
		{
			SPI2_MOSI = 0;
		}
		//4.拉高时钟线 - 产生上升沿
		SPI2_SCLK = 1;
	}
}



/*
函数功能：发送数据
参数：u8 data
返回值：无
备注：传输的数据
*/
void LCD_Send_Data(u8 data)
{
	//1.CS=0 拉低片选，开始通信
	LCD_CS = 0;
	//2.DC=1 发送数据
	LCD_DC = 1;
	//3.SPI_Send_Data() 发送数据
	SPI_Send_Data(data);
	//4.CS=1 拉高片选，停止通信
	LCD_CS = 1;
}




/*
函数功能：发送命令
参数：u8 cmd
返回值：无
备注：传输的命令/地址
*/
void LCD_Send_Cmd(u8 cmd)
{
	//1.CS=0 拉低片选，开始通信
	LCD_CS = 0;
	//2.DC=0 发送命令
	LCD_DC = 0;
	//3.SPI_Send_Data() 发送命令
	SPI_Send_Data(cmd);
	//4.CS=1 拉高片选，停止通信
	LCD_CS = 1;
}






/*
函数功能：发送16bit数据
参数：u16 data
返回值：无
备注：发送16bit数据  10101010 11110101
*/
void LCD_Write_Data(u16 data)   //颜色数据存储16位
{
	//1.CS=0 拉低片选，开始通信
	LCD_CS = 0;
	//2.DC=1 发送数据
	LCD_DC = 1;
	//3.SPI_Send_Data(data>>8) 发送数据
	//  SPI_Send_Data(data)    发送数据
	SPI_Send_Data(data>>8);
	SPI_Send_Data(data);
	//4.CS=1 拉高片选，停止通信
	LCD_CS = 1;
}




/*
函数功能：地址坐标函数
参数：u16 s_row, u16 e_row, u16 s_col, u16 e_col
返回值：无
备注：发送坐标地址  
*/
void LCD_Set_Address(u16 s_row, u16 e_row, u16 s_col, u16 e_col)
{
	//1.操作列地址 2A
	LCD_Send_Cmd(0x2A);
	LCD_Write_Data(s_col);
	LCD_Write_Data(e_col-1);
	
	//2.操作行地址 2B
	LCD_Send_Cmd(0x2B);
	LCD_Write_Data(s_row);
	LCD_Write_Data(e_row-1);
	
	//3.操作数据内容写入 2C
	LCD_Send_Cmd(0x2C);
}

/*
函数功能：清屏函数
参数：u16 s_row, u16 e_row, u16 s_col, u16 e_col, u16 color
返回值：无
备注：发送16bit颜色数据  
*/
void LCD_Clear(u16 s_row, u16 e_row, u16 s_col, u16 e_col, u16 color)
{
	//1.确定显示范围区域
	LCD_Set_Address( s_row,  e_row,  s_col,  e_col); //240*240
	
	//2.在区域写入数据
	for(u32 i = 0; i < 240*240; i++)
	{
		LCD_Write_Data(color);
	}
}



/*
函数功能：lcd初始化
参数：无
返回值：无
备注：芯片初始化
*/
void LCD_Init(void)
{
	//初始化引脚
	LCD_Pin_Init();
	
	/* 复位ST7789VM驱动器 */
	LCD_RESET = 1;
	delay_ms(100);
	LCD_RESET = 1;
	delay_ms(100);

	/* start initial sequence */ 
	LCD_Send_Cmd(0x36);
	LCD_Send_Data(0x00);

	LCD_Send_Cmd(0x3A); 
	LCD_Send_Data(0x05);

	LCD_Send_Cmd(0xB2);
	LCD_Send_Data(0x0C);
	LCD_Send_Data(0x0C);
	LCD_Send_Data(0x00);
	LCD_Send_Data(0x33);
	LCD_Send_Data(0x33); 

	LCD_Send_Cmd(0xB7); 
	LCD_Send_Data(0x35);  

	LCD_Send_Cmd(0xBB);
	LCD_Send_Data(0x19);

	LCD_Send_Cmd(0xC0);
	LCD_Send_Data(0x2C);

	LCD_Send_Cmd(0xC2);
	LCD_Send_Data(0x01);

	LCD_Send_Cmd(0xC3);
	LCD_Send_Data(0x12);   

	LCD_Send_Cmd(0xC4);
	LCD_Send_Data(0x20);  

	LCD_Send_Cmd(0xC6); 
	LCD_Send_Data(0x0F);    

	LCD_Send_Cmd(0xD0); 
	LCD_Send_Data(0xA4);
	LCD_Send_Data(0xA1);

	LCD_Send_Cmd(0xE0);
	LCD_Send_Data(0xD0);
	LCD_Send_Data(0x04);
	LCD_Send_Data(0x0D);
	LCD_Send_Data(0x11);
	LCD_Send_Data(0x13);
	LCD_Send_Data(0x2B);
	LCD_Send_Data(0x3F);
	LCD_Send_Data(0x54);
	LCD_Send_Data(0x4C);
	LCD_Send_Data(0x18);
	LCD_Send_Data(0x0D);
	LCD_Send_Data(0x0B);
	LCD_Send_Data(0x1F);
	LCD_Send_Data(0x23);

	LCD_Send_Cmd(0xE1);
	LCD_Send_Data(0xD0);
	LCD_Send_Data(0x04);
	LCD_Send_Data(0x0C);
	LCD_Send_Data(0x11);
	LCD_Send_Data(0x13);
	LCD_Send_Data(0x2C);
	LCD_Send_Data(0x3F);
	LCD_Send_Data(0x44);
	LCD_Send_Data(0x51);
	LCD_Send_Data(0x2F);
	LCD_Send_Data(0x1F);
	LCD_Send_Data(0x1F);
	LCD_Send_Data(0x20);
	LCD_Send_Data(0x23);

	LCD_Send_Cmd(0x21); 
	LCD_Send_Cmd(0x11); 
	LCD_Send_Cmd(0x29); 
	
	/* 清空屏幕显示 */
	LCD_Clear(0, 239, 0, 239, WHITE);

	/* 开启背光 */
	LEDK = 1;
}



/*********************功能函数****************************/

/*
函数功能：打点函数
参数：u16 row,  u16 col, u16 color
返回值：无
备注：起始坐标和终止坐标一致
*/
void LCD_Point(u16 row,  u16 col, u16 color)
{
	//1.确定显示区域 -- 挖坑
	LCD_Set_Address(row, row, col, col);
	//2.写入数据 -- 填坑
	LCD_Write_Data(color);
}


//画出一个矩形

/*
	函数功能：显示字符函数
	参数：u16 x, u16 y,   显示位置
				u16 font_color, 字符颜色
				u16 back_color, 背景颜色
				u8 mode,        背景控制 1-显示  0-不显示
				char* ch        显示字符
	返回值：无
	备注：8*16字宽字高
{0x00,0x00,0x00,0x10,0x10,0x18,0x28,0x28,0x24,0x3C,0x44,0x42,0x42,0xE7,0x00,0x00}
*/
void Lcd_Show_Ch(u16 x, u16 y, u16 font_color, u16 back_color, u8 mode, char* ch)
{
	char temp = 0;   //数据缓存
	
	//1.先获取数组数据，缓存起来
	for(u8 i = 0; i < 16; i++)
	{
		temp = ch[i];
		
		//2.将缓存数据按照8列处理
		for(u8 j = 0; j < 8; j++)
		{
			if(temp & (0x80 >> j))  //1
			{
				LCD_Point( x + i,  y + j, font_color);
			}
			else
			{
				if(mode == 1)
					LCD_Point( x + i,  y + j, back_color);
			}
		}
	}
}



/*
	函数功能：显示可选字符函数
	参数：u16 x, u16 y,   显示位置
				u16 font_color, 字符颜色
				u16 back_color, 背景颜色
				u8 mode,        背景控制 1-显示  0-不显示
				u8 size,        字符大小
				u16 ch        显示字符
	返回值：无
	备注：8*16字宽字高
{0x00,0x00,0x00,0x10,0x10,0x18,0x28,0x28,0x24,0x3C,0x44,0x42,0x42,0xE7,0x00,0x00}
*/
void Lcd_Show_Szie_Ch(u16 x, u16 y, u16 font_color, u16 back_color, u8 mode, u8 size, u16 ch)
{
	u32 temp = 0;
	
	//1.根据需求，通过码值表计算出对应字符的偏移值
	int n = 0;
	n = ch - ' ';  //35 - 32 = 3
	
	//2.根据偏移值，循环检测获取到对应字符数据
	if(size == 16)
	{
		for(u8 i = 0; i < size; i++)
		{
			//3.在对应字符数据中，每获取到一个字符就缓存起来
			temp = ASC16[n * 16 + i];
			//4.将缓存的数据按照对应列数处理
			for(u8 j = 0; j < size/2; j++)
			{
				if(temp & (0x80 >> j))  //1
				{
					LCD_Point( x + i,  y + j, font_color);
				}
				else
				{
					if(mode == 1)
						LCD_Point( x + i,  y + j, back_color);
				}
			}
		}
	}
	if(size == 32)
	{
		for(u8 i = 0; i < size; i++)
		{
			temp = ASC32[n * 64 + i*2 + 0] << 8 | ASC32[n * 64 + i*2 + 1];
			
			for(u8 j = 0; j < size/2; j++)
			{
				if(temp & (0x8000 >> j))  //1
				{
					LCD_Point( x + i,  y + j, font_color);
				}
				else
				{
					if(mode == 1)
						LCD_Point( x + i,  y + j, back_color);
				}
			}
		}
	}
	
	
}






/*
	函数功能：显示可选汉字函数
	参数：u16 x, u16 y,   显示位置
				u16 font_color, 字符颜色
				u16 back_color, 背景颜色
				u8 mode,        背景控制 1-显示  0-不显示
				u8 size,        字符大小
				u8* hz        显示字符
	返回值：无
	备注：8*16字宽字高
{0x00,0x00,0x00,0x10,0x10,0x18,0x28,0x28,0x24,0x3C,0x44,0x42,0x42,0xE7,0x00,0x00}
*/
void Lcd_Show_Szie_Hz(u16 x, u16 y, u16 font_color, u16 back_color, u8 mode, u8 size, u8* hz)
{
	int n = 0;
	u32 temp = 0;
	//1.根据数组对比获取到字符偏移值
	while(1)
	{
		if(*hz == table[2*n+0] && *(hz+1) == table[2*n+1])
		{
			break;
		}
		n++;
	}
	//2.根据偏移值循环遍历获取对应字符数据
	if(size == 16)
	{
		for(u8 i = 0; i < size; i++)
		{
			//3.在对应字符数据中，每获取到一个字符就缓存起来
			temp = HZ16[n * 32 + i * 2 + 0] << 8 | HZ16[n * 32 + i * 2 + 1];
			//4.将缓存的数据按照对应列数处理
			for(u8 j = 0; j < size; j++)
			{
				if(temp & (0x8000 >> j))  //1
				{
					LCD_Point( x + i,  y + j, font_color);
				}
				else
				{
					if(mode == 1)
						LCD_Point( x + i,  y + j, back_color);
				}
			}
		}
	}
	if(size == 32)
	{
		for(u8 i = 0; i < size; i++)
		{
			//3.在对应字符数据中，每获取到一个字符就缓存起来
			temp = HZ32[n * 128 + i * 4 + 0] << 24 | 
						 HZ32[n * 128 + i * 4 + 1] << 16 |
						 HZ32[n * 128 + i * 4 + 2] << 8  |
						 HZ32[n * 128 + i * 4 + 3];
			
			//4.将缓存的数据按照对应列数处理
			for(u8 j = 0; j < size; j++)
			{
				if(temp & (0x80000000 >> j))  //1
				{
					LCD_Point( x + i,  y + j, font_color);
				}
				else
				{
					if(mode == 1)
						LCD_Point( x + i,  y + j, back_color);
				}
			}
		}
	}
}

/*
	函数功能：显示可选英文汉字混合字符串函数
	参数：u16 x, u16 y,   显示位置
				u16 font_color, 字符颜色
				u16 back_color, 背景颜色
				u8 mode,        背景控制 1-显示  0-不显示
				u8 size,        字符大小
				u8* str         显示字符串
	返回值：无
	备注：8*16字宽字高
		"asdf纳米\0"
*/
void Lcd_Show_Szie_String(u16 x, u16 y, u16 font_color, u16 back_color, u8 mode, u8 size, u8* str)
{
	while(1)
	{
		if(*str >= 32 && *str < 127)   //字符
		{
			Lcd_Show_Szie_Ch( x,  y,  font_color,  back_color,  mode,  size, *str); //a
			str++;  //指针地址偏移，指向下一个字符
			
			y += size/2;
			if(y > 240 - size/2)
			{
				y = 0;
				x += size;
			}
			if(*str == '\0')
			{
				break;
			}	
		}
		else   //汉字
		{
			Lcd_Show_Szie_Hz( x,  y,  font_color,  back_color,  mode,  size, str); //a
			str +=2;  //指针地址偏移，指向下一个字符
			
			y += size;
			if(y > 240 - size)
			{
				y = 0;
				x += size;
			}
			if(*str == '\0')
			{
				break;
			}	
		}
	}
}





/*
	函数功能：显示图片
	参数：u16 x, u16 y,   显示位置
				u8* pic         显示图片数据
	返回值：无
	备注：BMP格式图片
	pic[2]=0X00 << 8 | pic[3]=0X32
	pic[4]=0X00 << 8 | pic[5]=0X32

*/
void Lcd_Show_Pic(u16 x, u16 y, u8* pic)
{
	//1.根据图片获取到宽高
	u16 w = pic[2] << 8 | pic[3];
	u16 h = pic[4] << 8 | pic[5];
	
	//2.在lcd中设置显示范围 -- 挖坑
	LCD_Set_Address(x, x+h, y, y+w);
	
	//3.在显示范围显示数据 -- 填坑
	for(u16 i = 0; i < w*h; i++)
	{
		//16位  8  8
		LCD_Write_Data(pic[8 + i*2 + 0] << 8 | pic[8 + i*2 + 1]);
	}
}




/*
	界面1：随便显示一些文字
*/
/*
	界面2：显示一张图片
*/
//初始化界面默认黑屏；
//按键2按下第一次，显示界面1；
//按下第二次，显示界面2；
//按下第三次，显示黑屏

































