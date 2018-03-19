#include "stm32f4xx.h"
#include "usart.h"		//��ʹ��printf���
#include "delay.h"		
#include "PWM.h"			//�������
#include "tumbler.h"	//������
#include "ADC_ADXL335.H"

//AD�ź�ǰ������
//���IN1=0 ; IN4 = 0  Ϊǰ��

int main(void)
{	

	u8 pwm = 110;
	Init();//��ʼ��
		TIM_SetCompare1(TIM4,pwm);	//���֣�����32�� GPIOD12
	  TIM_SetCompare2(TIM4,pwm);	//GPIOD13
//while(1){	
//	if(pwm>150|pwm<85)
//	{	
//		stop();break;
//	}
//		k =ADC_DataWork();
//	if(initname!=k)	  //��ƽ��
//	{
//		if(initname>k)		//�����б
//		{												
//			if(IN1==1&&IN2==0)  	//ǰ��״̬
//				pwm-=2;
//			else if(IN1==1&&IN2==0)	//����״̬
//				pwm+=2;
//		}	
//		else if(initname<k) //��ǰ��б
//		{
//			if(IN1==1&&IN2==0)  		//ǰ��״̬
//				pwm+=2;
//			else if(IN1==1&&IN2==0)	//����״̬
//				pwm-=2;
//		}
//		delay_ms(300);
//		TIM_SetCompare1(TIM4,pwm);	
//	}
//	
//	//	printf("***%d ** \n",x);
//	//	delay_ms(120);
//	}	
}






void Init(){
	Moter_PWM_Init(200,84);	  	 //pwm ��ʼ��
	GPIO_IN_Init();							 //D8 D9 10 D11
	uart_init(115200);					//����ͨ�ų�ʼ��
	Stm32_Clock_Init(336,8,2,7);//����ʱ��,168Mhz 
	delay_init(168);	//��ʱ��ʼ�� 	
	ADXL_335_Init();
}







