#include "DMA.h"
#include "workingData.h"
u8 buf[33];


/********************************************************
**函数名			：DMAusart6采集初始化
**参数			：void
**返回			：void
**描述			：dma实现串口6数据采集，对6轴传感器的数据采集处理
**创建时间		：2018年3月29日13:03:55
**创建者			：range
**更改时间		：2018年3月29日13:04:00

********************************************************/

void DMA_6axle_Usart6_Config(void)
{ 
	DMA_InitTypeDef  DMA_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6,ENABLE);//使能USART6时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG,ENABLE);
	
	GPIO_PinAFConfig(GPIOG,GPIO_PinSource9,GPIO_AF_USART6);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOG, &GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate=9600;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;	//数据流
	USART_InitStructure.USART_Mode=USART_Mode_Rx;//使能发送接收
	USART_InitStructure.USART_Parity=USART_Parity_No;					//校验位
	USART_InitStructure.USART_StopBits=USART_StopBits_1;			//停止位
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;	//8数据位
	
	USART_Init(USART6,&USART_InitStructure);
	USART_Cmd(USART6,ENABLE);
	
	

	
	
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);//DMA2时钟使能
	
  DMA_DeInit(DMA2_Stream2);	//usart6_RX
	
	while (DMA_GetCmdStatus(DMA2_Stream2) != DISABLE){}//等待DMA可配置 
	
  /* 配置 DMA Stream */
  DMA_InitStructure.DMA_Channel = DMA_Channel_5;  //通道选择usart6RX
  DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&USART6->DR;//DMA外设地址
  DMA_InitStructure.DMA_Memory0BaseAddr = (u32)buf;//存储器地址
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;//外设模式到存储器
  DMA_InitStructure.DMA_BufferSize = 33;//数据传输量 
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//外设非增量模式
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//存储器增量模式
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//外设数据长度:8位
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//存储器数据长度:8位
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;// 使用循环模式 
  DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;//中等优先级
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;//存储器突发单次传输
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;//外设突发单次传输
  DMA_Init(DMA2_Stream2, &DMA_InitStructure);//初始化DMA Stream
		

} 


/********************************************************
**函数名			：6传感器使能
**参数			：void
**返回			：void
**描述			：使能
**创建时间		：2018年3月29日13:52:31
**创建者			：range
**更改时间		：2018-03-29 13:52:332
********************************************************/
	void DMA_6axle_usart6RX_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	DMA_Cmd(DMA2_Stream2, DISABLE);                      //关闭DMA传输 
	DMA_ClearFlag(DMA2_Stream2,DMA_FLAG_TCIF5);
	while (DMA_GetCmdStatus(DMA2_Stream2) != DISABLE){}	//确保DMA可以被设置  
		
	DMA_SetCurrDataCounter(DMA2_Stream2,33);          //数据传输量  
 
	DMA_Cmd(DMA2_Stream2, ENABLE);                      //开启DMA传输 
	
		
		/*******产生中断函数********/
	DMA_ITConfig(DMA2_Stream2,DMA_IT_TC,ENABLE);//配置DMA中断 传输数据完成中断
	
	NVIC_InitStructure.NVIC_IRQChannel=DMA2_Stream2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;			//中断优先级设置
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructure);
}	  


/********************************************************
**函数名			：DMA中断函数
**参数			：void
**返回			：void
**描述			：DMA传输完成中断 并更新至数据库
**创建时间		：2018年3月29日13:53:20
**创建者			：range
**更改时间		：2018年3月29日13:53:23
********************************************************/
void DMA2_Stream2_IRQHandler(void)	//DMA2数据流2中断函数
{
		if(DMA_GetITStatus(DMA2_Stream2,DMA_FLAG_TCIF5))		//是否发上中断
		{
			u8 i;
			for(i=0;i<33;i++)
			{
					if(	(buf[i]==0x55)	&&	(buf[(i+1)%33]==0x55) )
					{
							working_Blance_Angle_X=(u16)(((buf[(i+3)%33]<<8)|buf[(i+2)%33])/182);//(32768/180=180.04)
																	//滚转角（x 轴） Roll=((RollH<<8)|RollL)/32768*180(°)
							working_Blance_Angle_Y=(u16)(((buf[(i+5)%33]<<8)|buf[(i+4)&33])/182);
																	//俯仰角（y 轴） Pitch=((PitchH<<8)|PitchL)/32768*180(°)
							working_Blance_Angle_Z=(u16)(((buf[(i+7)%33]<<8)|buf[(i+6)%33])/182);
																	//偏航角（z 轴） Yaw=((YawH<<8)|YawL)/32768*180(°)
							break;
					}
			}
		}
}







