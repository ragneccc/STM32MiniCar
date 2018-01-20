#include "PWM.h"


//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM14_PWM_Init(u32 arr,u32 psc)		//	通道 2
																				//EN2    PF9
																				//IN3    PF6
																				//IN4    PF7
{		 					 
	//此部分需手动修改IO口设置
	RCC->APB1ENR|=1<<8; 	//TIM14时钟使能    
	RCC->AHB1ENR|=1<<5;   	//使能PORTF时钟	
	GPIO_Set(GPIOF,PIN9,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);//复用功能,上拉输出
	GPIO_AF_Set(GPIOF,9,9);	// 	EN2 
	
	
	GPIO_Set(GPIOF,PIN6|PIN7,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD); //IN3 IN4
	IN3=1;
	IN4=0;
	
	
	TIM14->ARR=arr;			//设定计数器自动重装值 
	TIM14->PSC=psc;			//预分频器不分频 
	TIM14->CCMR1|=6<<4;  	//CH1 PWM1模式		 
	TIM14->CCMR1|=1<<3; 	//CH1 预装载使能	   
	TIM14->CCER|=1<<0;   	//OC1 输出使能	
	TIM14->CCER|=1<<1;   	//OC1 低电平有效	   
	TIM14->CR1|=1<<7;   	//ARPE使能 
	TIM14->CR1|=1<<0;    	//使能定时器14 											  
}  


void TIM13_PWM_Init(u32 arr,u32 psc)			//	通道1  
																					//EN1   PF8
																					//IN1   PC0
																					//IN2   PC1
{		 					 
	//此部分需手动修改IO口设置
	RCC->APB1ENR|=1<<7; 	//TIM13时钟使能    
	RCC->AHB1ENR|=1<<5;   	//使能PORTF时钟	
	RCC->AHB1ENR|=1<<2;   //使能 io c
	GPIO_Set(GPIOF,PIN8,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);//复用功能,上拉输出
	GPIO_AF_Set(GPIOF,8,9);	// EN 1
	
	
	GPIO_Set(GPIOC,PIN1|PIN0,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD); //IN1 IN2
	IN1=0;
	IN2=1;
	
	
	TIM14->ARR=arr;			//设定计数器自动重装值 
	TIM14->PSC=psc;			//预分频器不分频 
	TIM14->CCMR1|=6<<4;  	//CH1 PWM1模式		 
	TIM14->CCMR1|=1<<3; 	//CH1 预装载使能	   
	TIM14->CCER|=1<<0;   	//OC1 输出使能	
	TIM14->CCER|=1<<1;   	//OC1 低电平有效	   
	TIM14->CR1|=1<<7;   	//ARPE使能 
	TIM14->CR1|=1<<0;    	//使能定时器14 											  
}

