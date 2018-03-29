#include "DMA.h"
#include "workingData.h"
u8 buf[33];


/********************************************************
**������			��DMAusart6�ɼ���ʼ��
**����			��void
**����			��void
**����			��dmaʵ�ִ���6���ݲɼ�����6�ᴫ���������ݲɼ�����
**����ʱ��		��2018��3��29��13:03:55
**������			��range
**����ʱ��		��2018��3��29��13:04:00

********************************************************/

void DMA_6axle_Usart6_Config(void)
{ 
	DMA_InitTypeDef  DMA_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6,ENABLE);//ʹ��USART6ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG,ENABLE);
	
	GPIO_PinAFConfig(GPIOG,GPIO_PinSource9,GPIO_AF_USART6);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOG, &GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate=9600;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;	//������
	USART_InitStructure.USART_Mode=USART_Mode_Rx;//ʹ�ܷ��ͽ���
	USART_InitStructure.USART_Parity=USART_Parity_No;					//У��λ
	USART_InitStructure.USART_StopBits=USART_StopBits_1;			//ֹͣλ
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;	//8����λ
	
	USART_Init(USART6,&USART_InitStructure);
	USART_Cmd(USART6,ENABLE);
	
	

	
	
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);//DMA2ʱ��ʹ��
	
  DMA_DeInit(DMA2_Stream2);	//usart6_RX
	
	while (DMA_GetCmdStatus(DMA2_Stream2) != DISABLE){}//�ȴ�DMA������ 
	
  /* ���� DMA Stream */
  DMA_InitStructure.DMA_Channel = DMA_Channel_5;  //ͨ��ѡ��usart6RX
  DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&USART6->DR;//DMA�����ַ
  DMA_InitStructure.DMA_Memory0BaseAddr = (u32)buf;//�洢����ַ
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;//����ģʽ���洢��
  DMA_InitStructure.DMA_BufferSize = 33;//���ݴ����� 
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//���������ģʽ
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//�洢������ģʽ
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//�������ݳ���:8λ
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//�洢�����ݳ���:8λ
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;// ʹ��ѭ��ģʽ 
  DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;//�е����ȼ�
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;//�洢��ͻ�����δ���
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;//����ͻ�����δ���
  DMA_Init(DMA2_Stream2, &DMA_InitStructure);//��ʼ��DMA Stream
		

} 


/********************************************************
**������			��6������ʹ��
**����			��void
**����			��void
**����			��ʹ��
**����ʱ��		��2018��3��29��13:52:31
**������			��range
**����ʱ��		��2018-03-29 13:52:332
********************************************************/
	void DMA_6axle_usart6RX_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	DMA_Cmd(DMA2_Stream2, DISABLE);                      //�ر�DMA���� 
	DMA_ClearFlag(DMA2_Stream2,DMA_FLAG_TCIF5);
	while (DMA_GetCmdStatus(DMA2_Stream2) != DISABLE){}	//ȷ��DMA���Ա�����  
		
	DMA_SetCurrDataCounter(DMA2_Stream2,33);          //���ݴ�����  
 
	DMA_Cmd(DMA2_Stream2, ENABLE);                      //����DMA���� 
	
		
		/*******�����жϺ���********/
	DMA_ITConfig(DMA2_Stream2,DMA_IT_TC,ENABLE);//����DMA�ж� ������������ж�
	
	NVIC_InitStructure.NVIC_IRQChannel=DMA2_Stream2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;			//�ж����ȼ�����
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructure);
}	  


/********************************************************
**������			��DMA�жϺ���
**����			��void
**����			��void
**����			��DMA��������ж� �����������ݿ�
**����ʱ��		��2018��3��29��13:53:20
**������			��range
**����ʱ��		��2018��3��29��13:53:23
********************************************************/
void DMA2_Stream2_IRQHandler(void)	//DMA2������2�жϺ���
{
		if(DMA_GetITStatus(DMA2_Stream2,DMA_FLAG_TCIF5))		//�Ƿ����ж�
		{
			u8 i;
			for(i=0;i<33;i++)
			{
					if(	(buf[i]==0x55)	&&	(buf[(i+1)%33]==0x55) )
					{
							working_Blance_Angle_X=(u16)(((buf[(i+3)%33]<<8)|buf[(i+2)%33])/182);//(32768/180=180.04)
																	//��ת�ǣ�x �ᣩ Roll=((RollH<<8)|RollL)/32768*180(��)
							working_Blance_Angle_Y=(u16)(((buf[(i+5)%33]<<8)|buf[(i+4)&33])/182);
																	//�����ǣ�y �ᣩ Pitch=((PitchH<<8)|PitchL)/32768*180(��)
							working_Blance_Angle_Z=(u16)(((buf[(i+7)%33]<<8)|buf[(i+6)%33])/182);
																	//ƫ���ǣ�z �ᣩ Yaw=((YawH<<8)|YawL)/32768*180(��)
							break;
					}
			}
		}
}







