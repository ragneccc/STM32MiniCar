#include "PWM.h"


//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM14_PWM_Init(u32 arr,u32 psc)		//	ͨ�� 2
																				//EN2    PF9
																				//IN3    PF6
																				//IN4    PF7
{		 					 
	//�˲������ֶ��޸�IO������
	RCC->APB1ENR|=1<<8; 	//TIM14ʱ��ʹ��    
	RCC->AHB1ENR|=1<<5;   	//ʹ��PORTFʱ��	
	GPIO_Set(GPIOF,PIN9,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);//���ù���,�������
	GPIO_AF_Set(GPIOF,9,9);	// 	EN2 
	
	
	GPIO_Set(GPIOF,PIN6|PIN7,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD); //IN3 IN4
	IN3=1;
	IN4=0;
	
	
	TIM14->ARR=arr;			//�趨�������Զ���װֵ 
	TIM14->PSC=psc;			//Ԥ��Ƶ������Ƶ 
	TIM14->CCMR1|=6<<4;  	//CH1 PWM1ģʽ		 
	TIM14->CCMR1|=1<<3; 	//CH1 Ԥװ��ʹ��	   
	TIM14->CCER|=1<<0;   	//OC1 ���ʹ��	
	TIM14->CCER|=1<<1;   	//OC1 �͵�ƽ��Ч	   
	TIM14->CR1|=1<<7;   	//ARPEʹ�� 
	TIM14->CR1|=1<<0;    	//ʹ�ܶ�ʱ��14 											  
}  


void TIM13_PWM_Init(u32 arr,u32 psc)			//	ͨ��1  
																					//EN1   PF8
																					//IN1   PC0
																					//IN2   PC1
{		 					 
	//�˲������ֶ��޸�IO������
	RCC->APB1ENR|=1<<7; 	//TIM13ʱ��ʹ��    
	RCC->AHB1ENR|=1<<5;   	//ʹ��PORTFʱ��	
	RCC->AHB1ENR|=1<<2;   //ʹ�� io c
	GPIO_Set(GPIOF,PIN8,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);//���ù���,�������
	GPIO_AF_Set(GPIOF,8,9);	// EN 1
	
	
	GPIO_Set(GPIOC,PIN1|PIN0,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PD); //IN1 IN2
	IN1=0;
	IN2=1;
	
	
	TIM14->ARR=arr;			//�趨�������Զ���װֵ 
	TIM14->PSC=psc;			//Ԥ��Ƶ������Ƶ 
	TIM14->CCMR1|=6<<4;  	//CH1 PWM1ģʽ		 
	TIM14->CCMR1|=1<<3; 	//CH1 Ԥװ��ʹ��	   
	TIM14->CCER|=1<<0;   	//OC1 ���ʹ��	
	TIM14->CCER|=1<<1;   	//OC1 �͵�ƽ��Ч	   
	TIM14->CR1|=1<<7;   	//ARPEʹ�� 
	TIM14->CR1|=1<<0;    	//ʹ�ܶ�ʱ��14 											  
}

