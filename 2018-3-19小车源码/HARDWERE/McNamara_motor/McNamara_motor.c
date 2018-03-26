#include "McNamara_motor.h"
#include "math.h"




/********************************************************************
������McNamara�������
������ǰ������ �� ��ͷ���� �� ǰ���ٶ� ��ת���ٶ�
���أ�void
������ͨ�������ĸ�����������ĸ�������ת���򣬺��ٶȣ�PWM���ٶ������£�
����ʱ�䣺2018��3��26��17:59:02
�����ߣ�range
���¸���ʱ�䣺2018��3��26��17:59:27
********************************************************************/
void McMamara_Solve(u16 goAngle,u16 lookAt,u16 go_V,u16 turn_V)
{
	int chacha=(int)lookAt-(int)working_Angle;
	if(cos(chacha)>1.414)
	{
		
	}
	
}

/********************************************************************
**�����������ľ��ʼ��
**������void
**���أ�void
**�����������ķ���������pwm��ʼ��
**����ʱ�䣺2018��3��26��17:14:06
**�����ߣ�range
**���¸���ʱ�䣺
********************************************************************/
void McNamara_Init()
{
	McNamara_PWM_Init();
	McNamara_Direct_Config();	
}

/*********************************************************************
**������PWMռ�ձȵ���
**���������ӱ��	�� pwmֵ��-70~70����������ת
**���أ�void
**�������Ե������ӽ���ռ�ձȵ���
**����ʱ�䣺2018��3��26��17:55:16
**�����ߣ�range
**���¸���ʱ�䣺2018��3��19��14:57:59
**********************************************************************/
void Set_McNamara_PWM(u8 whichWheel,s16 pwmARR)     //���70��С-70
{ 
	u8 Status=0;
	if(pwmARR>=0)
	{
		Status++;
	}
	TIM_SetCompare2(TIM4,(u32)fabs(pwmARR));
	switch(whichWheel)
	{
		case 1:{INa=Status;INb=!Status;}break;
		case 2:{INc=Status;INd=!Status;}break;
		case 3:{INe=Status;INf=!Status;}break;
		case 4:{INg=Status;INh=!Status;}break;
		default:break;
	}
}



/*********************************************************************
**���������PWM��ʼ��
**������void
**���أ�void
**���������ú�pwm�����ڣ���ʹ��
**����ʱ�䣺2018��3��26��17:55:32
**���¸���ʱ�䣺2018��3��26��17:55:40
**********************************************************************/
void McNamara_PWM_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  		//TIM4ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); 	//ʹ��PORTDʱ��	
	
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4); //GPIOD12����Ϊ��ʱ��4
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource15,GPIO_AF_TIM4);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13|GPIO_Pin_14 | GPIO_Pin_15;//GPIOd12/13/14/15
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
//ͨ��1	
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);  				//����Tָ���Ĳ�����ʼ������TIM4 4OC1
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIM4��CCR1�ϵ�Ԥװ�ؼĴ���
//ͨ��2
	TIM_OC2Init(TIM4, &TIM_OCInitStructure); 			 		//����Tָ���Ĳ�����ʼ������TIM1 4OC2
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIM4��CCR1�ϵ�Ԥװ�ؼĴ���
//ͨ��3
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);  				//����Tָ���Ĳ�����ʼ������TIM4 4OC3
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIM4��CCR1�ϵ�Ԥװ�ؼĴ���
//ͨ��4
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);  				//����Tָ���Ĳ�����ʼ������TIM4 4OC4
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIM4��CCR1�ϵ�Ԥװ�ؼĴ���
 
	TIM_ARRPreloadConfig(TIM4,ENABLE);//ARPEʹ�� 
	TIM_Cmd(TIM4, ENABLE); 					  //ʹ��TIM4 
}  

/*********************************************************************
**������McNamara���ת�����ų�ʼ��
**������void
**���أ�void
**�����������ת����������� ��ʼ��
**����ʱ�䣺2018��3��26��17:55:54
**���¸���ʱ�䣺2018��3��19��15:13:50
**********************************************************************/
void McNamara_Direct_Config()             											
{												
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//ʹ��GPIOFʱ��

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_8 | GPIO_Pin_10 | GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��
	
		INa=0;
		INb=1;
	
		INc=0;
		INd=1;
	 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��
		
		INe=0;
		INf=1;
		
		INg=0;
		INh=1;
}









