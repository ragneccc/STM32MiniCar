#include "blance_6axle_Usart6.h"
#include "sys.h"
#include "usart.h"
#include "workingData.h"
//mpu6050模块通过串口发送角度等数据，本程序负责接收
//本文件包含初始化usart6 和 相关中断函数



//全局变量

u8 BUF_6axle[11];
/****************************************************************************
函数名				：blance_6axle_Usart6_Init	初始化串口6
参数				：void			
返回				：void
描述				：初始化波特率中断等。。
创建人				：ragne
创建日期			：2018年3月26日14:07:54
最新更改时间	：2018年3月26日14:09:24
****************************************************************************/
void blance_6axle_Usart6_Init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6,ENABLE);//使能USART6时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG,ENABLE);
	
	GPIO_PinAFConfig(GPIOG,GPIO_PinSource9,GPIO_AF_USART6);
	GPIO_PinAFConfig(GPIOG,GPIO_PinSource14,GPIO_AF_USART6);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOG, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOG, &GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate=9600;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;	//数据流
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;//使能发送接收
	USART_InitStructure.USART_Parity=USART_Parity_No;					//校验位
	USART_InitStructure.USART_StopBits=USART_StopBits_1;			//停止位
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;	//8数据位
	
	USART_Init(USART6,&USART_InitStructure);
	USART_Cmd(USART6,ENABLE);
  
	
	
	//这样可能占用太多cpu
	//初步打算采用定时器中断进行分时段采样 eg. 1ms采样一次
	
	
	//中断相关
	USART_ITConfig(USART6,USART_IT_RXNE,ENABLE);
	
	
	NVIC_InitStructure.NVIC_IRQChannel=USART6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;			//中断优先级设置
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructure);
	
	
}

/****************************************************************************
函数名				：get_balance_Angle	更新仰角和倾斜角、偏向角
参数				：void				
返回				：void
描述				：处理角度数据 并更新至数据库working_Data.文件内
创建人				：ragne
创建日期			：2018年3月26日14:07:54
最新更改时间	：
****************************************************************************/
void get_balance_6axle_Angle()
{
	if(		1)		//校验位校验
	{	
					
		working_Blance_Angle_X=(u16)(((BUF_6axle[3]<<8)|BUF_6axle[2])/182);//(32768/180=180.04)
														//滚转角（x 轴） Roll=((RollH<<8)|RollL)/32768*180(°)
		working_Blance_Angle_Y=(u16)(((BUF_6axle[5]<<8)|BUF_6axle[4])/182);
														//俯仰角（y 轴） Pitch=((PitchH<<8)|PitchL)/32768*180(°)
		working_Blance_Angle_Z=(u16)(((BUF_6axle[7]<<8)|BUF_6axle[6])/182);
														//偏航角（z 轴） Yaw=((YawH<<8)|YawL)/32768*180(°)
	}
}

/****************************************************************************
函数名				：			串口6中断服务函数
参数				：void				
返回				：void
描述				：收集有用数据并保存至BUF_6axle[]内以便于进一步处理
创建人				：ragne
创建日期			：2018年3月26日14:07:41
最新更改时间	：
****************************************************************************/
void USART6_IRQHandler(void)
	{
		static u16 axle6_i=0;	//声明静态变量用于计数
		// BUF_6axle[]
/*=======================6轴模块的中断函数========================*/
		if(USART_GetITStatus(USART6,USART_IT_RXNE))
			{
				if(axle6_i<2)
					{
							BUF_6axle[axle6_i]=USART_ReceiveData(USART6);	//接收函数
							axle6_i++;
					}
				else
					{
							if(BUF_6axle[0]!=0x55||BUF_6axle[1]!=0x53)
								{
											if(BUF_6axle[1]==0x55)
											{
												BUF_6axle[0]=0x55;
												axle6_i=1;
											}
											else
											{
												axle6_i=0;
											}
								}
							else
								{
											BUF_6axle[axle6_i]=USART_ReceiveData(USART6);
											axle6_i=(axle6_i+1)%11;
								}
					}
				//USART_ReceiveData(USART6);	//接收函数
				//USART_SendData(USART6, res1);		//串口发送
			}

	}




