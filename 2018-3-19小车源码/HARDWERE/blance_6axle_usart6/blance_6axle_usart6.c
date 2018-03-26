#include "blance_6axle_Usart6.h"
#include "sys.h"
#include "usart.h"
#include "workingData.h"
//mpu6050ģ��ͨ�����ڷ��ͽǶȵ����ݣ������������
//���ļ�������ʼ��usart6 �� ����жϺ���



//ȫ�ֱ���

u8 BUF_6axle[11];
/****************************************************************************
������				��blance_6axle_Usart6_Init	��ʼ������6
����				��void			
����				��void
����				����ʼ���������жϵȡ���
������				��ragne
��������			��2018��3��26��14:07:54
���¸���ʱ��	��2018��3��26��14:09:24
****************************************************************************/
void blance_6axle_Usart6_Init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6,ENABLE);//ʹ��USART6ʱ��
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
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;	//������
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;//ʹ�ܷ��ͽ���
	USART_InitStructure.USART_Parity=USART_Parity_No;					//У��λ
	USART_InitStructure.USART_StopBits=USART_StopBits_1;			//ֹͣλ
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;	//8����λ
	
	USART_Init(USART6,&USART_InitStructure);
	USART_Cmd(USART6,ENABLE);
  
	
	
	//��������ռ��̫��cpu
	//����������ö�ʱ���жϽ��з�ʱ�β��� eg. 1ms����һ��
	
	
	//�ж����
	USART_ITConfig(USART6,USART_IT_RXNE,ENABLE);
	
	
	NVIC_InitStructure.NVIC_IRQChannel=USART6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;			//�ж����ȼ�����
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructure);
	
	
}

/****************************************************************************
������				��get_balance_Angle	�������Ǻ���б�ǡ�ƫ���
����				��void				
����				��void
����				������Ƕ����� �����������ݿ�working_Data.�ļ���
������				��ragne
��������			��2018��3��26��14:07:54
���¸���ʱ��	��
****************************************************************************/
void get_balance_6axle_Angle()
{
	if(		1)		//У��λУ��
	{	
					
		working_Blance_Angle_X=(u16)(((BUF_6axle[3]<<8)|BUF_6axle[2])/182);//(32768/180=180.04)
														//��ת�ǣ�x �ᣩ Roll=((RollH<<8)|RollL)/32768*180(��)
		working_Blance_Angle_Y=(u16)(((BUF_6axle[5]<<8)|BUF_6axle[4])/182);
														//�����ǣ�y �ᣩ Pitch=((PitchH<<8)|PitchL)/32768*180(��)
		working_Blance_Angle_Z=(u16)(((BUF_6axle[7]<<8)|BUF_6axle[6])/182);
														//ƫ���ǣ�z �ᣩ Yaw=((YawH<<8)|YawL)/32768*180(��)
	}
}

/****************************************************************************
������				��			����6�жϷ�����
����				��void				
����				��void
����				���ռ��������ݲ�������BUF_6axle[]���Ա��ڽ�һ������
������				��ragne
��������			��2018��3��26��14:07:41
���¸���ʱ��	��
****************************************************************************/
void USART6_IRQHandler(void)
	{
		static u16 axle6_i=0;	//������̬�������ڼ���
		// BUF_6axle[]
/*=======================6��ģ����жϺ���========================*/
		if(USART_GetITStatus(USART6,USART_IT_RXNE))
			{
				if(axle6_i<2)
					{
							BUF_6axle[axle6_i]=USART_ReceiveData(USART6);	//���պ���
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
				//USART_ReceiveData(USART6);	//���պ���
				//USART_SendData(USART6, res1);		//���ڷ���
			}

	}




