#include "mpu6050.h"
#include "sys.h"
#include "usart.h"
//mpu6050模块通过串口发送角度等数据，本程序负责接收
//本文件包含初始化usart6 和 相关中断函数

//	全局变量 = USART_ReceiveData(USART6);

u16 res;
void mpu6050_Init()
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

void USART6_IRQHandler(void)
	{
		u8 res;
		if(USART_GetITStatus(USART6,USART_IT_RXNE))
			{
				res=USART_ReceiveData(USART6);	//接收函数
				USART_SendData(USART6, res);		//串口发送
			}

	}




