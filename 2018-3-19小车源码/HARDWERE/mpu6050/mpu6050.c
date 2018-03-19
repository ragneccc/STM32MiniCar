#include "mpu6050.h"
#include "sys.h"
#include "usart.h"
//mpu6050ģ��ͨ�����ڷ��ͽǶȵ����ݣ������������
//���ļ�������ʼ��usart6 �� ����жϺ���

//	ȫ�ֱ��� = USART_ReceiveData(USART6);

u16 res;
void mpu6050_Init()
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

void USART6_IRQHandler(void)
	{
		u8 res;
		if(USART_GetITStatus(USART6,USART_IT_RXNE))
			{
				res=USART_ReceiveData(USART6);	//���պ���
				USART_SendData(USART6, res);		//���ڷ���
			}

	}




