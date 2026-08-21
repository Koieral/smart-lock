#ifndef __VOICE_H_       //if not define 防止重定义
#define __VOICE_H_


//引用头文件
#include "stm32f4xx.h" 
#include "tim.h"

#define VOICE_BUSY    GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_4) 
#define VOICE_DATA_H  GPIO_SetBits(GPIOC, GPIO_Pin_5)  
#define VOICE_DATA_L  GPIO_ResetBits(GPIOC, GPIO_Pin_5)


//定义/变量声明
/* 语音对应的标号 */
#define CHANGE_ADMIN_PASSWORD	  	 0x00 //修改管理员密码
#define SET_DOOR_PASSWORD	   		   1    //设置开门密码
#define REGISTER_FINGER				     2 		//登记指纹
#define REGISTER_CARD			         3 		//登记卡片
#define CHANGE_TIME					       4 		//修改时间
#define DELETE_ALLFINGER		     	 5    //删除所有指纹
#define DELETE_ASSIGN_FINGER		 	 6    //删除指定指纹
#define RECOVER_ALL				         7    //恢复出厂设置
#define CHANGE_VOLUME				       8    //设置音量
#define DELETE_ALL_CARD				     9    //删除所有门卡
#define DELETE_ASSIGN_CARD			   10   //删除指定门卡
#define INPUT_ADMIN_PASSWORD       11   //请输入管理员密码  
#define INPUT_NEW_PASSWORD 			   12   //请输入新密码       
#define INPUT_NEW_PASSWORD_AGAIN   13   //请再次输入新密码 
#define CARD_REGISTERED 			     14   //卡重复             
#define DELETE_ALL_FIGNER		 	     15   //是否删除
#define DELETE_ASSIGNFIGNER		 	   16   //请放手指 0X16
#define FINGER_REPETITION 		 	   17   //指纹重复
#define DOOROPEN_SUCCESS			     18   //欢迎回家
#define DOOROPEN_FAIL				       19   //开门失败
#define BL_CONNECT_SUCCESS         20   //蓝牙连接成功
#define WIFI_CONNECT_SUCCESS       21   //WiFi连接成功
#define TIPS                       22   //按#号确认，按*号退出
#define REPETE                     23   //请重新设置
#define Warm 					             24   //报警声
#define MenLing 					         25   //叮咚 叮咚       
#define PASSWORD_ERROR     			   26   //验证失败
#define PASSWORD_INCONFORMITY		   27   //密码不一致
#define SETTING_SUCCESS				     28   //操作成功
#define PASSWORD_REPETITION			   29   //密码重复
#define PUTCARD 				           30   //请放置卡片
#define LING 				     	         31   //0
#define YI				     	 	         32   //1
#define ER				     	 	         33   //2
#define SAN			     	 	 	         34   //3
#define SI		     	 	  		       35   //4
#define WU	     	 	 			         36   //5
#define LIU     	 	 			         37   //6
#define QI 				     	 	         38   //7
#define BA 				     	 	         39   //8
#define JIU 				     	         40   //9
#define XING 				     	         41   //*
#define JING 				     	         42   //#
#define QUERENG 				           43   //确认
#define QUXIAO 				     	       44   //取消
#define XYD							           45   //欢迎使用信盈达智能锁
																		    
//#define Di 							         30   //嘟      



//函数声明
void Voice_Init(void);
void Voice_Start(void);
void Voice_Data_0(void);
void Voice_Data_1(void);
void Voice_Send_Data(u8 data);
void Voice_Send_Cmd(u8 cmd);

#endif   //结束定义

