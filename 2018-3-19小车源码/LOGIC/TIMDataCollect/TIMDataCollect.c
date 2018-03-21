#include "TIMDataCollect.h"





/***********************************************************************
**��������ʱ���жϳ�ʼ��
**������arr��psc		Ԥװ��ֵ��Ԥ��Ƶϵ��	��Tout=((arr+1)*(psc+1))/Ft us.��
**���أ�void
**������׼��һ����ʱ�жϣ����ڷ�����ʱɨ�贫��������
**����ʱ�䣺2018��3��19��20:44:28
**�����ߣ�range
**���¸���ʱ�䣺2018��3��19��20:44:34
���������������⣺��ʱ��3�Ѿ���ռ�ã�
***********************************************************************/
void TIMDataCollect_IRQ_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///ʹ��TIM3ʱ��

  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 

	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//��ʼ��TIM3

	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //����ʱ��3�����ж�
	TIM_Cmd(TIM3,ENABLE); //ʹ�ܶ�ʱ��3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}


/***********************************************************************
**��������ʱ���жϷ�����
**������void
**���أ�void
**�������жϺ������һ�θ�·����������Ϣɨ�裻
**����ʱ�䣺2018��3��19��20:48:31
**�����ߣ�range
**���¸���ʱ�䣺2018��3��19��20:48:35
���������������⣺3�Ѿ���ռ�ã���������д
***********************************************************************/
void TIM3_IRQHandler(void)
{
	//����д
}

