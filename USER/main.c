#include "stm32f4xx.h"
#include "usart.h"		//��ʹ��printf���
#include "delay.h"		
#include "PWM.h"			//�������
#include "tumbler.h"	//������


void changePwm14(u16 x)		//ͨ��1������ռ�ձ� int ���͵� 1---99
{
	u16 y;
	y =2*x-1;
	TIM_SetCompare1(TIM14,y);
}
void changePwm13(u16 x)		//ͨ��2������ռ�ձ� int ���͵� 1---99
{
	u16 y;
	y =2*x-1;
	TIM_SetCompare1(TIM13,y);
}
	




int main(void)
{
	//��ʼ������
	//TIM14_PWM_Init(200-1,84-1);	//2kHz PWM
	TIM13_PWM_Init(200-1,84-1); //��ʱ���ַ�Ƶ  ���Զ���װֵ
	uart_init(115200);					//����ͨ�ų�ʼ��
	Stm32_Clock_Init(336,8,2,7);//����ʱ��,168Mhz 
	delay_init(168);			//��ʱ��ʼ�� 
	
	
		IN1 = 1;
		IN2 = 0;
		IN3 = 1;
		IN4 = 0;

		while(1)		
	{
		//changePwm13(5);	
	delay_ms(500);
		changePwm14(1);
	delay_ms(500);

	}

}





/*	ԭ����ģ�����

#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"

//STM32F4����ģ��-�⺯���汾

int main(void)
{
	u32 t=0;
	uart_init(115200);
	delay_init(84);
	
  while(1){
    printf("t:%d\r\n",t);
		delay_ms(500);
		t++;
	}
}

*/


