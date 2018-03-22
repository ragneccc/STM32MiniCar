#include "blance_Usart6.h"
#include "sys.h"
#include "usart.h"
#include "workingData.h"
//mpu6050ģ��ͨ�����ڷ��ͽǶȵ����ݣ������������
//���ļ�������ʼ��usart6 �� ����жϺ���



//	ȫ�ֱ��� = USART_ReceiveData(USART6);
u8 bufg61_i=0,BUF_G61_usart6[11],BUF_G61_usart6Ture[4];

void blance_Usart6_Init()
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
	
	USART_InitStructure.USART_BaudRate=115200;
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
������				��get_balance_Angle	�������Ǻ���б��
����				��void				
����				��void
����				���������� �����������ݿ�working_Data.�ļ���
������				��ragne
��������			��2018��3��22��14:59:31
���¸���ʱ��	��
****************************************************************************/
void get_balance_Angle()
{
	if(BUF_G61_usart6[1]==0x53&&BUF_G61_usart6[6]==0x00&&BUF_G61_usart6[7]==0x00
														&&BUF_G61_usart6[8]==0x00&&BUF_G61_usart6[9]==0x00)
	{	
					
		working_Blance_Angle_X=(u16)(((BUF_G61_usart6Ture[1]<<8)|BUF_G61_usart6Ture[0])/182);//(32768/180=180.04)
														//��ת�ǣ�x �ᣩ Roll=((RollH<<8)|RollL)/32768*180(��)
		working_Blance_Angle_Y=(u16)(((BUF_G61_usart6Ture[3]<<8)|BUF_G61_usart6Ture[2])/182);
														//�����ǣ�y �ᣩ Pitch=((PitchH<<8)|PitchL)/32768*180(��)
	}
}

/****************************************************************************
������				��			����6�жϷ�����
����				��void				
����				��void
����				���ռ���0x55��ͷΪ��11�ֽڴ������� BUF_G61_usart6[11] ��
������				��ragne
��������			��2018��3��22��14:53:35
���¸���ʱ��	��2018��3��22��14:55:36
****************************************************************************/
void USART6_IRQHandler(void)
	{
		if(USART_GetITStatus(USART6,USART_IT_RXNE))
			{
				if(!bufg61_i)
					{
						BUF_G61_usart6[0]=USART_ReceiveData(USART6);	//���պ���
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
				//USART_ReceiveData(USART6);	//���պ���
				//USART_SendData(USART6, res1);		//���ڷ���
			}

	}




