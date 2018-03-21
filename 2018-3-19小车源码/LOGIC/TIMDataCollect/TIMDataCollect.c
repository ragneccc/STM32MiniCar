#include "TIMDataCollect.h"





/***********************************************************************
**函数：定时器中断初始化
**参数：arr；psc		预装载值、预分频系数	（Tout=((arr+1)*(psc+1))/Ft us.）
**返回：void
**描述：准备一个定时中断，用于反复定时扫描传感器数据
**创建时间：2018年3月19日20:44:28
**创建者：range
**最新更改时间：2018年3月19日20:44:34
！！！：遗留问题：定时器3已经被占用；
***********************************************************************/
void TIMDataCollect_IRQ_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///使能TIM3时钟

  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 

	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//初始化TIM3

	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //允许定时器3更新中断
	TIM_Cmd(TIM3,ENABLE); //使能定时器3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //定时器3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}


/***********************************************************************
**函数：定时器中断服务函数
**参数：void
**返回：void
**描述：中断函数完成一次各路传感器的信息扫描；
**创建时间：2018年3月19日20:48:31
**创建者：range
**最新更改时间：2018年3月19日20:48:35
！！！：遗留问题：3已经被占用；函数待编写
***********************************************************************/
void TIM3_IRQHandler(void)
{
	//待编写
}

