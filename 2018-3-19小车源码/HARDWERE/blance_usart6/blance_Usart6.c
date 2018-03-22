#include "blance_Usart6.h"
#include "sys.h"
#include "usart.h"
#include "workingData.h"
//mpu6050模块通过串口发送角度等数据，本程序负责接收
//本文件包含初始化usart6 和 相关中断函数



//	全局变量 = USART_ReceiveData(USART6);
u8 bufg61_i=0,BUF_G61_usart6[11],BUF_G61_usart6Ture[4];

void blance_Usart6_Init()
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
	
	USART_InitStructure.USART_BaudRate=115200;
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
函数名				：get_balance_Angle	更新仰角和倾斜角
参数				：void				
返回				：void
描述				：处理数据 并更新至数据库working_Data.文件内
创建人				：ragne
创建日期			：2018年3月22日14:59:31
最新更改时间	：
****************************************************************************/
void get_balance_Angle()
{
	if(BUF_G61_usart6[1]==0x53&&BUF_G61_usart6[6]==0x00&&BUF_G61_usart6[7]==0x00
														&&BUF_G61_usart6[8]==0x00&&BUF_G61_usart6[9]==0x00)
	{	
					
		working_Blance_Angle_X=(u16)(((BUF_G61_usart6Ture[1]<<8)|BUF_G61_usart6Ture[0])/182);//(32768/180=180.04)
														//滚转角（x 轴） Roll=((RollH<<8)|RollL)/32768*180(°)
		working_Blance_Angle_Y=(u16)(((BUF_G61_usart6Ture[3]<<8)|BUF_G61_usart6Ture[2])/182);
														//俯仰角（y 轴） Pitch=((PitchH<<8)|PitchL)/32768*180(°)
	}
}

/****************************************************************************
函数名				：			串口6中断服务函数
参数				：void				
返回				：void
描述				：收集以0x55开头为长11字节存于数组 BUF_G61_usart6[11] 中
创建人				：ragne
创建日期			：2018年3月22日14:53:35
最新更改时间	：2018年3月22日14:55:36
****************************************************************************/
void USART6_IRQHandler(void)
	{
		if(USART_GetITStatus(USART6,USART_IT_RXNE))
			{
				if(!bufg61_i)
					{
						BUF_G61_usart6[0]=USART_ReceiveData(USART6);	//接收函数
						bufg61_i++;
					}
				else
					{
						if(BUF_G61_usart6[0]!=0x55)
							{
									bufg61_i=0;
							}
						else
							{
									BUF_G61_usart6[bufg61_i]=USART_ReceiveData(USART6);
								if(bufg61_i==10)
									{
											u8 i;
											for(i=2;i<=5;i++)
											{
													BUF_G61_usart6Ture[i-2]=BUF_G61_usart6[i];
											}
									}
									bufg61_i=(bufg61_i+1)%11;
							}
					}
				//USART_ReceiveData(USART6);	//接收函数
				//USART_SendData(USART6, res1);		//串口发送
			}

	}




