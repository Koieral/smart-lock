#ifndef _LCD_H   //if not define 预编译处理，防止重定义
#define _LCD_H




#include "stm32f4xx.h"
#include "io_bit.h"
#include "delay.h"
#include "font.h"

#define LEDK PBout(1)          //背光
#define LCD_RESET PBout(10)    //复位
#define LCD_CS PBout(12)       //片选
#define SPI2_SCLK PBout(13)    //时钟
#define LCD_DC PBout(14)       //数据/命令
#define SPI2_MOSI PBout(15)    //数据线


/* 颜色定义开始 */
#define WHITE        0xFFFF
#define BLACK        0x0000	  
#define BLUE         0x001F  
#define BRED         0XF81F
#define GRED 	       0XFFE0
#define GBLUE		     0X07FF
#define RED          0xF800
#define MAGENTA      0xF81F
#define GREEN        0x07E0
#define CYAN         0x7FFF
#define YELLOW       0xFFE0
#define BROWN 			 0XBC40 //棕色
#define BRRED 			 0XFC07 //棕红色
#define GRAY  			 0X8430 //灰色
#define DARKBLUE     0X01CF	//深蓝色
#define LIGHTBLUE    0X7D7C	//浅蓝色  
#define GRAYBLUE     0X5458 //灰蓝色
#define LIGHTGREEN   0X841F //浅绿色
#define LGRAY 			 0XC618 //浅灰色(PANNEL),窗体背景色
#define LGRAYBLUE    0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE       0X2B12 //浅棕蓝色(选择条目的反色)
/* 颜色定义结束 */



/***************LCD初始化配置****************/
void LCD_Pin_Init(void);
void SPI_Send_Data(u8 data);
void LCD_Send_Data(u8 data);
void LCD_Send_Cmd(u8 cmd);
void LCD_Write_Data(u16 data);
void LCD_Set_Address(u16 s_row, u16 e_row, u16 s_col, u16 e_col);
void LCD_Clear(u16 s_row, u16 e_row, u16 s_col, u16 e_col, u16 color);
void LCD_Init(void);
/***************LCD功能函数******************/
void LCD_Point(u16 row,  u16 col, u16 color);
void Lcd_Show_Ch(u16 x, u16 y, u16 font_color, u16 back_color, u8 mode, char* ch);
void Lcd_Show_Szie_Ch(u16 x, u16 y, u16 font_color, u16 back_color, u8 mode, u8 size, u16 ch);
void Lcd_Show_Szie_Hz(u16 x, u16 y, u16 font_color, u16 back_color, u8 mode, u8 size, u8* hz);
void Lcd_Show_Szie_String(u16 x, u16 y, u16 font_color, u16 back_color, u8 mode, u8 size, u8* str);
void Lcd_Show_Pic(u16 x, u16 y, u8* pic);




#endif
