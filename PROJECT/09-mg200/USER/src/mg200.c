#include "mg200.h"

/*
MG200管脚初始化函数
MG200_DETECT   	---   PC0    	---   输入模式
MG200_PWR   		---   PC1   	---   推挽输出
*/
void Mg200_PortInit(void)
{
	
	//1、打开时钟    GPIOC   ---   AHB1打开时钟的库函数   时钟：rcc
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	
	//2、GPIO初始化
	GPIO_InitTypeDef GPIO_InitStruct;					      //定义结构体变量
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_OUT;     //输出模式
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;     //推挽输出
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_1 ;       
	GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;  //无上下拉
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;  //速度为50Mhz
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;       //输入模式
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_0; 
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	//要给MG200供电
	MG200_PWR_ON;
	
}



/*
函数功能：USART6初始化
返回值：void
形参：u32 bps    设置波特率
说明：
USART6_TX   ---  PC6   ---   复用
USART6_RX   ---  PC7   ---   复用
*/

void Usart6_Init(u32 bps)
{
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//打开GPIOC时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6,ENABLE);//打开USART6时钟
	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_USART6);//将PC6复用到USART6
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_USART6);//将PC7复用到USART6
	
	GPIO_InitTypeDef GPIO_InitStruct={0};
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;//复用模式
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;//配置第6、7号管脚
	GPIO_Init(GPIOC,&GPIO_InitStruct);
	
	USART_InitTypeDef USART_InitStruct={0};
	USART_InitStruct.USART_BaudRate = bps;//设置波特率
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件流传输控制
	//RTS和CTS：各占用一个IO
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//发送器和接收器使能
	USART_InitStruct.USART_Parity = USART_Parity_No;//无奇偶校验
	USART_InitStruct.USART_StopBits = USART_StopBits_1;//停止位为1bit
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;//数据位为8bit
	USART_Init(USART6,&USART_InitStruct);
	
	USART_ITConfig(USART6,USART_IT_RXNE,ENABLE);//使能接收中断
	USART_ITConfig(USART6,USART_IT_IDLE,ENABLE);//使能空闲中断   表示接收数据完成
	
	//配置NVIC  ①使用搜索NVIC配置函数   ②使用库函数 -- misc
	NVIC_InitTypeDef NVIC_InitStruct={0};
	NVIC_InitStruct.NVIC_IRQChannel = USART6_IRQn;//配置中断源（中断源名称） --  搜索IRQn
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;//中断源使能
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 9;//配置抢占优先级
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;//配置响应优先级
	NVIC_Init(&NVIC_InitStruct);
	
	USART_Cmd(USART6,ENABLE);//使能USART6
	
}

/*
USART6中断服务函数
注意：中断服务函数都是无返回值无形参
*/
U6_STRUCT u6={0};
void USART6_IRQHandler(void)
{
	
	//判断接收中断标志位
	if(USART_GetITStatus(USART6,USART_IT_RXNE))
	{
		USART_ClearITPendingBit(USART6,USART_IT_RXNE);//清除接收中断标志位
		//user handler
		u6.buff[u6.len++] = USART_ReceiveData(USART6);
		
	}
	//判断空闲中断标志位  ---  提示接收数据完成
	if(USART_GetITStatus(USART6,USART_IT_IDLE))
	{
		
		USART6->SR;
		USART6->DR;//清除空闲中断标志位
		
		u6.buff[u6.len] = '\0';//结尾补充结束符
		u6.len = 0;//数据长度清零，准备下次数据接收
		u6.flag = 1;//接收MG200返回结果完成
		
		
	}
	
}




//USART_FLAG_RXNE
/*
函数功能：USART6发送1byte函数
返回值：void
形参：u8 data    1byte数据
说明：

*/
void usart6_send_byte(u8 data)
{

	//等待发送标志位置一
	while(!USART_GetFlagStatus(USART6,USART_FLAG_TXE));
	
	//发送1byte数据
	USART_SendData(USART6,data);
	
}



/*
函数功能：USART61发送字符串
返回值：void
形参：u8 *data    需要发送字符串数据首地址
说明：
"123456\0"
*/
void usart6_send_str(u8 *data)
{
	
	while(*data != '\0')
	{
		usart6_send_byte(*data);
		data++;//地址偏移	
	}
	usart6_send_byte('\0');
	
}


/*
MG200模块初始化函数
*/
void Mg200_Init(void)
{
	//1、MG200管脚初始化
	Mg200_PortInit();
	//注意：MG200供电后两种效果  ①亮彩灯    ②不会亮灯
		
	//2、USART6初始化
	Usart6_Init(115200);
}




/*
发送数据包函数
形参：
			u8 cmd     发送指令码
			u8 param   发送参数
返回值：void
*/

void Mg200_SendPacket(u8 cmd,u8 param)
{
	u8 checksum = 0;//计算校验和
	usart6_send_byte(0x6c); 
	usart6_send_byte(0x63);
	usart6_send_byte(0x62);
	usart6_send_byte(cmd);
	usart6_send_byte(param);
	usart6_send_byte(0x00);
	checksum = (0x63 + 0x62 + cmd + param + 0x00) & 0xff;
	usart6_send_byte(checksum);
	
	u6.flag = 0;//跳过MG200返回的没用数据
}




/*
接收数据包函数
形参：
			u8 cmd     接收到指令码
			u8 *result 接收的结果
			u8 *param  接收的参数
返回值：u8   0:接收数据包正常      非0：接收数据包失败
*/

u8 Mg200_RecPacket(u8 cmd,u8 *result,u8 *param)
{
	u8 checksum = 0;
	//等待接收数据包接收完成   u6.flag = 1
	while(!u6.flag);
	//判断接收数据包的没一字节数据是否正确
	if(u6.buff[0] != 0x6c)
		return 1;
	if(u6.buff[1] != 0x62)
		return 2;
	if(u6.buff[2] != 0x63)
		return 3;
	if(u6.buff[3] != cmd)
		return 4;	
	
	*result = u6.buff[4];//获取MG200返回结果的数据
	*param = u6.buff[5];//获取MG200返回的参数
	
	if(u6.buff[6] != 0x00)
		return 5;	
	
	checksum = (u6.buff[1] + u6.buff[2] + u6.buff[3] + u6.buff[4] + u6.buff[5] + u6.buff[6])&0xff;
	
	if(checksum != u6.buff[7])
		return 6;
	
	return 0;//接收数据包成功
}



/*
提取指纹图像及特征量函数
形参：u8 num    代表第几次提取指纹特征量
				0:第1次提取指纹特征量
				1:第2次提取指纹特征量
				2:第3次提取指纹特征量
				3:第4次提取指纹特征量
				4:第5次提取指纹特征量
返回值：u8   0:提取特征量正常      非0：提取特征量失败
*/

u8 CaptureAndExtract(u8 num)
{
	u8 result,param;
	printf("请按下手指\r\n");
	//等待手指有没有按下
	while(!MG200_DETECT);
	
	//发送数据包
	Mg200_SendPacket(0x51,num);
	//接收数据包
	if(Mg200_RecPacket(0x51,&result,&param)==0)
	{
		//代表接收数据包成功
		switch(result)
		{
			case 0x00:printf("抓取指纹图像及特征量提取成功\r\n");break;
			default:printf("抓取指纹图像及特征量提取失败\r\n");break;
		}
	}
	else
	{
		printf("接收数据包失败\r\n");
		return 1;
	}
	
	return result;
	
}




/*
注册用户
形参：无
返回值：u8   0:注册成功      非0：注册失败
*/
u8 Enroll(void)
{
	u8 ret = 0;
	u8 result,param;
	
	//1.提取指纹数据--3次
	printf("按下手指，提取第一次指纹\r\n");
	do{
		ret = CaptureAndExtract(0);
	}while(ret);
	
	printf("按下手指，提取第二次指纹\r\n");
	do{
		ret = CaptureAndExtract(1);
	}while(ret);
	
	printf("按下手指，提取第三次指纹\r\n");
	do{
		ret = CaptureAndExtract(2);
	}while(ret);
	
	
	//2.发送注册指令
	Mg200_SendPacket(0x7F,0x00);
	//3.接收注册指令
	if(Mg200_RecPacket(0x7F,&result,&param) == 0)
	{
		//4.将接收到的指令解析，判断结果
		switch(result)
		{
			case 0x00:printf("注册成功\r\n");break;
			case 0x93:printf("ID已经存在\r\n");break;
			default:printf("注册失败\r\n");break;
		}
	}
	else
	{
		printf("接收数据包出错，请重新接收\r\n");
		return 1;  //报错
	}
	return result;  //注册成功
	
}


/*
对比用户
形参：无
返回值：u8   0:对比成功      非0：对比失败
*/
u8 Match1N(void)
{
	u8 ret = 0;
	u8 result,param;
	
	//1.先提取指纹数据
	if(MG200_DETECT)  //开启指纹工作
	{
		printf("对比指纹前，先按下手指提取指纹\r\n");
		do{
			ret = CaptureAndExtract(0);
		}while(ret);
		
		//2.发送对比指令
		Mg200_SendPacket(0x71,0x00);
		//3.接收指令数据
		if(Mg200_RecPacket(0x71,&result,&param) == 0)
		{
			//4.将接收到的指令解析，判断结果
			switch(result)
			{
				case 0x00:printf("对比成功\r\n");break;
				default:printf("对比失败\r\n");break;
			}
		}
		else
		{
			printf("接收数据包出错，请重新接收\r\n");
			return 1;  //报错
		}
		return result;
	}
	
	//4.将指令进行对比
	//5.对结果进行解析
	return 2;
}



//指纹开门
void Mg200_Open_Door(void)
{
	//1.先注册
	//2.对比
	//3.判断对比结果
	
	if(Match1N() == 0)
	{
		//4.成功则开门
		printf("指纹开门成功\r\n");
		//语音提示
		Voice_Send_Cmd(DOOROPEN_SUCCESS);
		//电机操作
		Open_Door();
		//led提示
	}
	else if(Match1N() != 0 && MG200_DETECT) //5.失败则提示
	{
		Voice_Send_Cmd(DOOROPEN_FAIL);
		delay_ms(200);
		printf("指纹开门失败\r\n");
	}
	
}






















