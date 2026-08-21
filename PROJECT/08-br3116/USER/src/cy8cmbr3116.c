#include "CY8CMBR3116.h"
#include <stdio.h>

const unsigned char CY8CMBR3116_LQXI_configuration[128] = {
	 0xFFu, 0x0Fu, 0xFBu, 0x0Fu, 0x00u, 0x00u, 0x00u, 0x00u,
    0xFFu, 0xFFu, 0xFEu, 0x00u, 0xA5u, 0xA5u, 0xA5u, 0xA5u,
    0xA5u, 0xA5u, 0xA5u, 0xA5u, 0xA5u, 0xA5u, 0xA5u, 0xA5u,
    0x7Fu, 0x7Fu, 0x7Fu, 0x7Fu, 0x08u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x80u,
    0x05u, 0x00u, 0x00u, 0x02u, 0x00u, 0x02u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x1Eu, 0x1Eu, 0x00u,
    0x00u, 0x1Eu, 0x1Eu, 0x00u, 0x00u, 0x00u, 0x01u, 0x01u,
    0x00u, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu,
    0xFFu, 0x00u, 0x00u, 0x00u, 0x20u, 0x03u, 0x01u, 0x63u,
    0x00u, 0x37u, 0x03u, 0x00u, 0x00u, 0x0Au, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0xD3u, 0x27u
};


const unsigned char CY8CMBR3116_RegPara[128] = {

    0xFFu, 0x0Fu, 0xFBu, 0x0Fu, 0x00u, 0x00u, 0x00u, 0x00u,
    0xAAu, 0xAAu, 0xA9u, 0x00u, 0x80u, 0x80u, 0x80u, 0x80u,
    0x80u, 0x80u, 0x80u, 0x80u, 0x80u, 0x80u, 0x80u, 0x80u,
    0x7Fu, 0x7Fu, 0x7Fu, 0x7Fu, 0x08u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x80u,
    0x05u, 0x00u, 0x00u, 0x02u, 0x00u, 0x02u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x1Eu, 0x1Eu, 0x00u,
    0x00u, 0x1Eu, 0x1Eu, 0x00u, 0x00u, 0x00u, 0x01u, 0x01u,
    0x00u, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0xFFu,
    0xFFu, 0x00u, 0x00u, 0x00u, 0x20u, 0x03u, 0x01u, 0x63u,
    0x00u, 0x37u, 0x03u, 0x00u, 0x00u, 0x0Au, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0xA1u, 0xD5u
};			//finger threshold 128  	有防护		有FSS（CS2无）	有IIR FILTER	有MEDIAN FILTER		enable shield		enable guard sensor		

/********************************************IIC************************************/

/**
 * 函数名    :CY8CMBR3116_iic_io_init
 * 函数功能  :IIC所用IO口初始化配置
 * 函数参数  :无
 * 函数返回值:无
 * 函数描述  : PB6----SCL----通用开漏输出
 *             PB7----SDA----通用开漏输出
			   PA1----RST----通用推挽输出
 */				
void CY8CMBR3116_iic_io_init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	//端口时钟使能
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	
	//配置工作状态
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_OUT;          	//通用输出
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;         	//开漏
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_6 | GPIO_Pin_7 ;//6、7
	GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;       	//无上下拉
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;       	//速度
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;         	//推挽输出
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_1 ;  						//1
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//空闲状态
	GPIO_SetBits(GPIOB, GPIO_Pin_6);//SCL
	GPIO_SetBits(GPIOB, GPIO_Pin_7);//SDA
	
}


/**
 * 函数名    :iic_start
 * 函数功能  :IIC起始信号函数
 * 函数参数  :无
 * 函数返回值:无
 * 函数描述  :时钟线为高电平，数据线出现下降沿
 */
void CY8CMBR3116_iic_start(void)
{
	//时钟线拉低，才可以动数据线
	CY8CMBR3116_IIC_SCL_L; 
	Tim2_Delay_us(500);
	//数据线拉高，目的是为出现下降沿做准备
	CY8CMBR3116_IIC_SDA_OUT_H;   
	
	//时钟线拉高  产生起始信号的条件
	CY8CMBR3116_IIC_SCL_H;
	Tim2_Delay_us(500);
	//数据线拉低  可以产生起始信号
	CY8CMBR3116_IIC_SDA_OUT_L;
	Tim2_Delay_us(500);
	
	//安全
	//CY8CMBR3116_IIC_SCL_L;
}


/**
 * 函数名    :iic_stop
 * 函数功能  :IIC停止信号函数
 * 函数参数  :无
 * 函数返回值:无
 * 函数描述  :时钟线为高电平，数据线出现上升沿
 */
void CY8CMBR3116_iic_stop(void)
{
	
	//准备工作
	CY8CMBR3116_IIC_SCL_L;
	Tim2_Delay_us(500);
	CY8CMBR3116_IIC_SDA_OUT_L;
	
	//产生停止信号
	CY8CMBR3116_IIC_SCL_H;
	Tim2_Delay_us(500);
	CY8CMBR3116_IIC_SDA_OUT_H;
	Tim2_Delay_us(500);
}


/**
 * 函数名    :iic_send_ack
 * 函数功能  :发送应答/不应答信号
 * 函数参数  :0--发送应答信号,1--发送不应答信号
 * 函数返回值:无
 * 函数描述  :应答： 时钟线为高电平，数据线已经保持好低电平了         
 *			  不应答 时钟线为高电平，数据线已经保持好高电平了			空闲状态	
 */
void CY8CMBR3116_iic_send_ack(uint8_t ack)
{
	CY8CMBR3116_IIC_SCL_L;	  		//时钟线拉低，才可以动数据线
	Tim2_Delay_us(500);
	if(ack == 0)	   			//发送应答
	{
		CY8CMBR3116_IIC_SDA_OUT_L;   //让数据线先保持低电平
	}
	else if(ack == 1)
	{
		CY8CMBR3116_IIC_SDA_OUT_H;   //让数据线先保持高电平
	}
	Tim2_Delay_us(500);
	CY8CMBR3116_IIC_SCL_H;	  	    //产生了应答信号	
	Tim2_Delay_us(500);

	//安全
	//IIC_SCL_L;	
}


/**
 * 函数名    :iic_get_ack
 * 函数功能  :检测应答/不应答信号
 * 函数参数  :无
 * 函数返回值:返回0--表示应答信号,返回1--表示不应答信号
 * 函数描述  :			
 */
uint8_t CY8CMBR3116_iic_get_ack(void)
{	
	uint8_t ack = 0;
	
	//数据线要为输入
	//CY8CMBR3116_IIC_SCL_L;
	//数据线切换输入状态（从机来控制）
	CY8CMBR3116_IIC_SDA_OUT_H;    				//空闲状态
	
	//检测应答/不应答信号
	CY8CMBR3116_IIC_SCL_L;   //主机帮助从机拉低时钟线，从机才可以动数据线，来表现应答/不应答信号
	Tim2_Delay_us(500);  
	CY8CMBR3116_IIC_SCL_H;   //主机才可以读数据线
	Tim2_Delay_us(500);
	if(CY8CMBR3116_IIC_SDA_INT == 0)
	{
		//低电平——应答信号
		ack = 0;
	}
	else
	{
		//高电平----不应答信号
		ack = 1;
	}
	
	//安全
	//CY8CMBR3116_IIC_SCL_L;
	return ack;
}


/**
 * 函数名    :iic_send_byte
 * 函数功能  :IIC发送一个字节函数
 * 函数参数  :uint8_t data
 * 函数返回值:无
 * 函数描述  :SCL拉低准备数据，SCL发送数据
 */
void CY8CMBR3116_iic_send_byte(uint8_t data)
{
	uint8_t i;
	for(i = 0;i < 8;i++)
	{
		//时钟线拉低才可以改变数据线
		CY8CMBR3116_IIC_SCL_L;
		Tim2_Delay_us(500);  
		//根据参数的对应位是0还是1决定数据线的高低
		if(data & 0x80)					//高位相与
		{
			CY8CMBR3116_IIC_SDA_OUT_H;
		}
		else
		{
			CY8CMBR3116_IIC_SDA_OUT_L;
		}
		Tim2_Delay_us(500);  
		//时钟下拉高，帮助从机，这样从机才可以读这一位数据
		CY8CMBR3116_IIC_SCL_H;
		Tim2_Delay_us(500);  
		//下一位数据，次高位变成最高位
		data = data << 1;
	}
	//安全
	//CY8CMBR3116_IIC_SCL_L;
	
}


/**
 * 函数名    :iic_read_byte
 * 函数功能  :主机通过IIC接收一个字节函数
 * 函数参数  :无
 * 函数返回值:uint8_t
 * 函数描述  :
 */
uint8_t CY8CMBR3116_iic_read_byte(void)
{
	
	uint8_t data;    
	uint8_t i;
	
	//将IO口切换为输入
	//CY8CMBR3116_IIC_SCL_L;
	CY8CMBR3116_IIC_SDA_OUT_H;			//空闲
	
	//读数据
	for(i = 0;i < 8;i++)
	{
		CY8CMBR3116_IIC_SCL_L;             //主机帮助从机拉低时钟线
		Tim2_Delay_us(500);   
		CY8CMBR3116_IIC_SCL_H;             //主机可以读数据
		Tim2_Delay_us(500);
		data = data << 1;
		if(CY8CMBR3116_IIC_SDA_INT) 
			data= data | 0x01;	
		
	}
	
	//安全
	//CY8CMBR3116_IIC_SCL_L;
	
	return data;
	
}



/*************************************************************************************
**功能: 发送CY8CMBR3116器件地址并等待唤醒
**参数: 读/写操作		=0写		=1读
**返回:  =1无应答退出		=0有效地址有应答并操作完成
**描述: 判断IIC是否有有效地址的确认应答
*************************************************************************************/
uint8_t CY8CMBR3116_Start(uint8_t flag)
{
uint8_t loop;	
	
	loop=0;
	do
	{
		loop++;
		CY8CMBR3116_iic_start();		
		CY8CMBR3116_iic_send_byte(CY8CMBR3116_ADDR+flag);					//发送器件地址 读/写操作
		if(CY8CMBR3116_iic_get_ack()==0)													//接收返回的确认信号
		{return 0;}
	}while(loop<20);
	
 	CY8CMBR3116_iic_stop();	
	return 1;	
}

/*************************************************************************************
**功能: 向CY8CMBR3116读取数据
**参数: dat:要写入的命令 / 数据(用于指示函数将读取的数据存储在哪里)
**返回:  =1无应答退出		=0操作完成
**描述: 这三个参数共同指定了函数应该读取哪个寄存器的数据，将数据存储到哪个缓冲区中，并且读取多少个字节的数据。
*************************************************************************************/
uint8_t CY8CMBR3116_RdData(uint8_t reg_addr,uint8_t *dat,uint8_t len)
{
uint8_t ack;
uint32_t loop;
	
	ack=CY8CMBR3116_Start(0);				//发送device地址 写操作
	if(ack)
	{return 1;}

	CY8CMBR3116_iic_send_byte(reg_addr);					//发送寄存器地址字节（设置数据指针）
	ack=CY8CMBR3116_iic_get_ack();
	if(ack)
	{return 1;}

	CY8CMBR3116_iic_stop();


	ack=CY8CMBR3116_Start(1);				//发送device地址 读操作
	if(ack)
	{return 1;}

// for(loop=0;loop<200;loop++);		//延时

	loop=0;
	do
	{		
		*(dat+loop)=CY8CMBR3116_iic_read_byte();		//读取数据
		loop++;
		if(loop==len)
		{CY8CMBR3116_iic_send_ack(1);}
		else
		{CY8CMBR3116_iic_send_ack(0);}		
	}while(loop<len);

	CY8CMBR3116_iic_stop();
	
	return 0;
}


/*************************************************************************************
**功能: 向CY8CMBR3116写入数据
**参数: dat:要写入的命令 / 数据
**返回:  =1无应答退出		=0操作完成
**描述: 
*************************************************************************************/
uint8_t CY8CMBR3116_WrData(uint8_t reg_addr,uint8_t *dat,uint8_t len)
{
uint8_t ack;
uint32_t loop;
	
	ack=CY8CMBR3116_Start(0);				//发送device地址 写操作
	if(ack)
	{return 1;}

	CY8CMBR3116_iic_send_byte(reg_addr);					//发送寄存器地址字节
	ack=CY8CMBR3116_iic_get_ack();
	if(ack)
	{return 1;}

	for(loop=0;loop<len;loop++)
	{
		CY8CMBR3116_iic_send_byte(*(dat+loop));		//发送数据
		ack=CY8CMBR3116_iic_get_ack();
		if(ack)
		{return 1;}		
	}

	CY8CMBR3116_iic_stop();											//结束传输
	
	return 0;
}



/**************************************寄存器配置*************************************************/


/*************************************************************************************
**功能: CY8CMBR3116读取配置状态
**参数: 
**返回: 0.非默认的出厂配置			1: 默认的出厂配置
**描述: 
*************************************************************************************/
uint8_t CY8CMBR3116_RdCfgStatus(void)
{
uint8_t buff[1];
	buff[0]=0;
	CY8CMBR3116_RdData(SYSTEM_STATUS,buff,1);
	printf("buff = %d\n",buff[0]);
	return buff[0]; 
}

/*************************************************************************************
**功能: CY8CMBR3116读取配置数据 CRC
**参数: 
**返回: 
**描述: 主机指令操作码 0x03 计算的配置数据 CRC
*************************************************************************************/
 uint16_t CY8CMBR3116_RdCrc(void)
 {
 uint8_t buff[2];
 	buff[0]=0; buff[1]=0;	
 	CY8CMBR3116_RdData(CALC_CRC,buff,2);
 	return buff[1]<<8 | buff[0]; 
 }



/*************************************************************************************
**功能: CY8CMBR3116读取命令执行状态
**参数: 
**返回: 0: 没有任何错误		1: 发生了错误
**描述:
*************************************************************************************/
uint8_t CY8CMBR3116_RdCmdStatus(void)
{
uint8_t buff[1];
	buff[0]=0;
	CY8CMBR3116_RdData(CTRL_CMD_STATUS,buff,1);
	return buff[0]; 
}

/*************************************************************************************
**功能: CY8CMBR3116命令寄存器操作
**参数: 
**返回: 
**描述: 
2: 器件将计算该寄存器映射中配置数据的 CRC 校验和，并把得到的结果同 CONFIG_CRC 中的值进行比较。如果两个值相匹配，器件会将该配置以及 CRC 校验和一同保存到非易失性存储器内。
3: 器件对该寄存器映射中的配置数据进行 CRC 校验和，然后将结果存储在 CALC_CRC 寄存器中。请注意，该指令仅用于测试和调试，并不推荐将它适用在生产配置中。
7: 器件不再进行扫描，而会进入低功耗模式。当发生 I2C 地址匹配事件时，器件将退出该模式。
0xff: 器件本身自复位
*************************************************************************************/
uint8_t CY8CMBR3116_WrCmd(uint8_t cmd)
{
	uint8_t ack;	
	
	ack=CY8CMBR3116_WrData(CTRL_CMD,&cmd,1);
	return ack;
}
// CY8CMBR3116_WrCmd(0x2);
// CY8CMBR3116_WrCmd(0x3);
// CY8CMBR3116_WrCmd(0xff);



/*************************************************************************************
**功能: CY8CMBR3116读取指令执行错误状态
**参数: 
**返回: 0: 指令执行成功		0xfd: 对闪存写入失败		0xfe: CONFIG_CRC 所存储的配置CRC校验和与计算得到的配置CRC校验和不一致	0xff: 指令无效
**描述: 
*************************************************************************************/
 uint8_t CY8CMBR3116_RdCmdErr(void)
 {
 uint8_t buff[2];
	buff[0]=0; 	
 	CY8CMBR3116_RdData(CTRL_CMD_ERR,buff,1);
 	return buff[0]; 
 }
 
 
 

/*************************************************************************************
**功能: CY8CMBR3116寄存器初始化配置
**参数: force_cfg=1强制重新配置寄存器表 =0若无配置则配置，若已配置则不再配置
**返回: =0曾经已配置		=1配置成功
**描述: 
*************************************************************************************/
// 将配置数据和 CRC 值写入到 CY8CMBR3xxx 控制器寄存器内
// 将 CMD_OP_CODE 的数值 2 写入到CTRL_CMD (0x86)寄存器内后等待 220 ms，将配置数据保存到非易失性存储器内。
// 再 读 取CTRL_CMD_STATUS (0x88)寄存器，以便检查配置数据是否成功被存储到非易失性存储器内，。
// 如果成功（CTRL_CMD_STATUS 寄存器的值为 0），将 CMD_OP_CODE 的数值 255 写入到 CTRL_CMD (0x86)寄存器内来发送复位指令。
// 如果失败（CTRL_CMD_STATUS 寄存器的值为 1），表示配置数据未被保存到非易失性存储器内。这时请读取 CTRL_CMD_ERR (0x89)寄存器，以了解保存配置数据到非易失性存储器内失败的原因。
uint8_t CY8CMBR3116_RegCfg(uint8_t force_cfg)
{
uint8_t ack;
uint16_t val;	
uint32_t loop;
	
ReInit:	
	
	val=CY8CMBR3116_RdCfgStatus();				//0.非默认的出厂配置			1: 默认的出厂配置
// Debug_sprintf("MBR3116_CfgStatus:%02x.\r\n",val);

	if(val==0 && force_cfg==0)
	{return 0;}


	for(loop=0;loop<10;loop++)
	{
		ack=CY8CMBR3116_WrData(REGCFG_ADDR,(uint8_t *)CY8CMBR3116_RegPara,128);
		printf("MBR3116SetREG:%d\r\n",ack);		
		if(ack==0)
		{break;}
	}
	
	for(loop=0;loop<10;loop++)
	{
		ack=CY8CMBR3116_WrCmd(0x2);				//计算该寄存器映射中配置数据的CRC校验和，并把得到的结果同CONFIG_CRC中的值进行比较。如果两个值相匹配，器件将该配置以及 CRC 校验和一同保存到存储器内。
		printf("MBR3116CfgSave:%d\r\n",ack);			
		if(ack==0)
		{break;}
	}
	
	Tim2_Delay_ms(300);
	
	val=CY8CMBR3116_RdCmdStatus();
	printf("MBR3116_CmdStatus:%02x.\r\n",val);
	if(val)
	{goto ReInit;}

 	val=CY8CMBR3116_RdCrc();							//读取命令crc值，测试用	
	printf("CY8CMBR3116_Crc:%04x.\r\n",val);
	
 	val=CY8CMBR3116_RdCmdErr();						//读取命令操作状态，测试用
	printf("CY8CMBR3116_cmderr:%02x.\r\n",val);
 	if(val)
 	{goto ReInit;}	

	CY8CMBR3116_WrCmd(0xff);					//复位
	printf("ceshi\n");
	return 1;
}
/***************************************CY8CMBR3116************************************/

/**
 * 函数名    :CY8CMBR3116_Init
 * 函数功能  :IO初始化+复位
 * 函数参数  :无
 * 函数返回值:无
 * 函数描述  :PA1低电平复位
 */
void CY8CMBR3116_Init(void)
{
	uint8_t cfg;
	
	//IIC通信IO初始化
	CY8CMBR3116_iic_io_init();
	CY8CMBR3116_RESET;
	
	
	#if FORCECFG_REG
	cfg=1;							//强制重新配置寄存器，改变参数重新配置后需要最好重新启动
	#else	
		cfg=0;
	#endif
	
	if(CY8CMBR3116_RegCfg(cfg)==0)
	{
 		printf("MBR3116曾经配置.\r\n");
	}
	else
	{
 		printf("MBR3116配置成功.\r\n");
	}
	
	
}

/****************************实现功能************************/


/*************************************************************************************
功能: 按键键值转换
参数:
返回: 0－9 10（*）	11（#）		-1无按键		-2无效按键
描述: 
CS0(K7)		CS1(*)		CS2(K4)		CS3(K1)		CS4(K2)		CS5(K5)		
CS6(K0)		CS7(K8)		CS8(K3)		CS9(K6)		CS10(#)		CS11(K9)
*************************************************************************************/
uint16_t CY8CMBR3116_RdKeyVal(void)
{
	uint8_t ack;	
	uint8_t buff[2] = {0};
	uint16_t But_val = 0;
	
	ack = CY8CMBR3116_RdData(BUTTON_STA,buff,2);  //读取按键按下的状态 -- 按下后，读取到按键键值
	(ack) ?  (printf("读取键值失败...\r\n")) : (ack);

	But_val =(buff[1]<<8 | buff[0]); 		//拼接为16位数据
	
//	printf("But_val = 0x%x\r\n",But_val);
//	Tim2_Delay_ms(50);
	switch(But_val)
	{
		case 0x0001:return '7';break;
		case 0x0400:return '#';break;
		case 0x0080:return '8';break;
		case 0x0002:return '*';break;
		case 0x0800:return '9';break;
		case 0x0040:return '0';break;
		case 0x0008:return '1';break;
		case 0x0100:return '3';break;
		case 0x0020:return '5';break;
		case 0x0004:return '4';break;
		case 0x0200:return '6';break;
		case 0x0010:return '2';break;
		default:return 0xff;break;
	}
}


//扫描检测函数
u8 BR3116_KeyScan(void)
{
	//1.设定一个标签，做单次检测
	static u8 BR3116_flag = 1;
	//2.声明变量，存储键值
	u8 BR3116_value = 0;
	//3.存储最新的键值
	u8 BR3116_key = 0xff;   //给有效值
 	
	BR3116_value = CY8CMBR3116_RdKeyVal();
	
	if(BR3116_value != 0xff && BR3116_flag)  //判断按下
	{
		BR3116_key = BR3116_value;
		BR3116_flag = 0;
	}
	if(BR3116_value == 0xff)
	{
		BR3116_flag = 1;
	}
	return BR3116_key;
}

/*
	函数功能：密码控制开门
	函数参数：无
	函数返回值：无
	描述：
		需要一个内存存储密码--user_password
		需要一个地方提供输入密码  user_pwd
		需要一个计数器，计算密码个数
		需要提供一个“#”确定按键码
*/
void BR3116_Open_Door(void)
{
	u8 key = 0xff;
	//1.预设一个密码
	u8 open_pwd[10] = "123";
	
	//2.设置计数器，记录密码个数
	static u8 cnt = 0;
	
	//3.设置一个空间，存储输入的密码
	static u8 user_pwd[10] = {0};
	
	//4.调用按键输入函数，获取键值
	key = BR3116_KeyScan();  // 1234....*#
	
	//5.处理数字键盘
	if(key != 0xff && key != '#')  //判断是按下同时不是#号
	{
		//printf("键值：%c\r\n", key);
		//lcd显示密码 -- 改为*号显示
		Lcd_Show_Szie_Ch(50, 50+(cnt*32), RED, LGRAY, 1, 32, '*');
		user_pwd[cnt++] = key;   //将键值存到数组中
	}
	//6.处理“#”号确认键，意味着密码输入完成
	if(key == '#')
	{
		printf("输入的密码：%s\r\n",user_pwd);
		
		//7.对比两个密码
		if(strcmp((const char*)user_pwd, (const char*)open_pwd) == 0)
		{
			printf("密码正确\r\n");
			//音频提示：密码正确，欢迎回家
			Voice_Send_Cmd(DOOROPEN_SUCCESS);
			//开门操作/led提示
			Open_Door();
			LED_G_ON;
			delay_ms(1000);
			LED_G_OFF;
		}
		else
		{
			printf("密码错误\r\n");
			//音频提示：密码错误，重新输入
			Voice_Send_Cmd(PASSWORD_INCONFORMITY);
			//开门失败/led提示
			LED_R_ON;
			delay_ms(1000);
			LED_R_OFF;
		}
		//8.不管对比成不成功，数组都要清除掉
		cnt = 0;
		memset(user_pwd,0,sizeof(user_pwd));
	}
}


//加入音频






















