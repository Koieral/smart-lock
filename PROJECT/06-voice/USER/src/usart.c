#include "usart.h"


/*
	函数功能：usart引脚初始化
	函数参数：u32 baud
	函数返回值：无
	备注：PA9  USART_TX  
				PA10 USART_RX  
*/
void Usart_Init(u32 baud)
{
	//1.配置GPIO时钟脉冲信号
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	//2.配置GPIO控制器
	GPIO_InitTypeDef GPIO_InitStructure = {0};
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;   					 //复用模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;						 //推挽类型
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10 | GPIO_Pin_9;  //指定配置引脚
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;          //无上下拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;				 //高速
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//3.将GPIO引脚映射为串口的通信通道--发送/接收
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
	
	//4.配置USART的时钟脉冲信号 rcc.c文件
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	//5.配置USART控制器
	USART_InitTypeDef USART_InitStructure = {0};
	USART_InitStructure.USART_BaudRate 	          = baud;    												//115200
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //无硬件流模式
	USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;  //全双工模式
	USART_InitStructure.USART_Parity              = USART_Parity_No;      			    //无奇偶校验
	USART_InitStructure.USART_StopBits            = USART_StopBits_1;     			    //1bit停止位
	USART_InitStructure.USART_WordLength          = USART_WordLength_8b;  	    	  //8bit字长
	USART_Init(USART1, &USART_InitStructure);

	//6.开启USART
	USART_Cmd(USART1, ENABLE);
}



//封装发送字节函数
void Usart1_Send_Data(u8 data)  
{
	while( USART_GetFlagStatus(USART1, USART_FLAG_TXE) == 0);  //等待上一次数据发送完成
	USART_SendData(USART1, data);
}


//封装接收字节函数
u8 Usart1_Rec_Data(void)  
{
	
	while( USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == 0);  //等待上一次数据发送完成
	return USART_ReceiveData(USART1);
}



//封装发送字符串函数
void Usart1_Send_String(u8* data)
{
	while(*data != '\0')
	{
		Usart1_Send_Data(*data); //s
		data++;
	}
}	
//s   d   f   g\0
//封装接收字符串函数
Usart1 usart1;
void Usart1_Rec_String(void)
{
	while(1)
	{
		usart1.data[usart1.index] = Usart1_Rec_Data(); // s
		if(usart1.data[usart1.index] == '\n')
		{
			usart1.data[usart1.index + 1] = '\0';
			usart1.index = 0;
			printf("数据内容：%s\r\n",usart1.data);
			
			if(strcmp((const char*)usart1.data, "led_on\r\n") == 0)   //结果等于0说明字符串一样
				LED_G_ON;
			
			return;
		}
		usart1.index++;
	}//数组最后收的字符=\0
}  
	






//重定向函数，将数据重定向到串口，通过串口发送数据出去
int fputc(int c, FILE *stream)
{
	Usart1_Send_Data(c);
	return c;
}



//接收功能
























