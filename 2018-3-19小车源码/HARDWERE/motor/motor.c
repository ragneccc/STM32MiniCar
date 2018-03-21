#include "motor.h"
#include "math.h"
#include "sys.h"

/********************************************************************
**�����������ʼ������
**������void
**���أ�void
**������׼��Ŷ�õ��������ռ�ձ�Ϊ0�ȴ�����
**����ʱ�䣺2018��3��20��21:01:00
**�����ߣ�range
**���¸���ʱ�䣺2018��3��20��21:01:09
********************************************************************/
void MOTOR_Config_Init()
{
	MOTOR_Pwm_Config();
	MOTOR_Direct_Config();  
	TIM_SetCompare2(TIM4,0);TIM_SetCompare1(TIM4,0);		//Ĭ��
	//TIM_SetCompare2(TIM4,fabs(50));TIM_SetCompare1(TIM4,40); ������
}

/*********************************************************************
**������PWMռ�ձȵ���
**������ͨ��1���ֵ�����֣� ��ͨ��2���ֵ�����֣�
**���أ�void
**���������루70~-70���������Ե���pwm�������Ƶ��ת��
**����ʱ�䣺����
**�����ߣ�����
**���¸���ʱ�䣺2018��3��19��14:57:59
**********************************************************************/
void Set_Motor(s32 left_wheel,s32 right_wheel)     //���70��С-70
{ 
	
	if(left_wheel>=0)
	{
		IN1=1;
		IN2=0;
		TIM_SetCompare1(TIM4,left_wheel);
	}
	else 
	{
		IN1=0;
		IN2=1;
		TIM_SetCompare1(TIM4,fabs(left_wheel));            //ȡ����ֵ
	}
	
	if(right_wheel>=0)
	{
		IN3=0;
		IN4=1;
		TIM_SetCompare2(TIM4,right_wheel);
	}
	else 
	{
		IN3=1;
		IN4=0;
		TIM_SetCompare2(TIM4,fabs(right_wheel));             //ȡ����ֵ

	}
}



/*********************************************************************
**���������PWM��ʼ��
**������void
**���أ�void
**���������ú�pwm�����ڣ���ʹ��
**����ʱ�䣺����
**���¸���ʱ�䣺2018��3��19��15:11:43
**********************************************************************/
void MOTOR_Pwm_Config()
{
GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  		//TIM4ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); 	//ʹ��PORTDʱ��	
	
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4); //GPIOD12����Ϊ��ʱ��4
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;           //GPIOd12/13
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOD,&GPIO_InitStructure);              //��ʼ��PF9
	  
	TIM_TimeBaseStructure.TIM_Prescaler=168;  			//��ʱ����Ƶ	psc
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=100;   				//�Զ���װ��ֵ	arr
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);	//��ʼ����ʱ��4
	
	//��ʼ��TIM4 Channel1 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);  				//����Tָ���Ĳ�����ʼ������TIM4 4OC1

	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIM4��CCR1�ϵ�Ԥװ�ؼĴ���
	
	TIM_OC2Init(TIM4, &TIM_OCInitStructure); 			 //����Tָ���Ĳ�����ʼ������TIM1 4OC1

	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIM4��CCR1�ϵ�Ԥװ�ؼĴ���
 
	TIM_ARRPreloadConfig(TIM4,ENABLE);//ARPEʹ�� 
	
	TIM_Cmd(TIM4, ENABLE); 					  //ʹ��TIM4 
}  


/*
 *��������MOTOR_Direct_Config
 *����  :��ʼ�����ת������
 *����  ����
 *����  ����
 *����  : ���ڲ�����
 */

/*********************************************************************
**���������ת�����ų�ʼ��
**������void
**���أ�void
**�����������ת����������� ��ʼ��
**����ʱ�䣺����
**���¸���ʱ�䣺2018��3��19��15:13:50
**********************************************************************/
void MOTOR_Direct_Config()             											
{												
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//ʹ��GPIOFʱ��

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_8 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��
	
		IN1=1;
		IN2=0;

  //RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//ʹ��GPIOFʱ��
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��
	
		IN3=0;
		IN4=1;
}


/*********************************************************************
???????????????????????


**********************************************************************/

void MOTOR_Direct_Control(u8 Which_Side,u8 Direct)
{
	if(Which_Side==LEFT_SIDE)
	{
				if(Direct==FORWARD)
				{
					IN1=1;
					IN2=0;
				}
				else if(Direct==BACKWARD)
				{
					IN1=0;
					IN2=1;
				}
	}
	else if(Which_Side==RIGHT_SIDE)
	{
				if(Direct==FORWARD)
				{
					IN3=1;
					IN4=0;
				}
				else if(Direct==BACKWARD)
				{
					IN3=0;
					IN4=1;
				}
	}
	
}




