#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"

//STM32F4����ģ��-�⺯���汾

void changePwm(u16 x)		//����ռ�ձ� int ���͵� 0---100
{
	u16 y;
	y = 100000 *x/100;
	TIM_SetCompare1(TIM14,y);
}
	



int main(void)
{
	//��ʼ������
	//void TIM_PWM(u32 arr,u32 psc); //��ʱ���ַ�Ƶ  ���Զ���װֵ
	uart_init(115200);
	delay_init(84);
	
		while(1)		
	{
		printf("����ڴ˴�ӡ�κζ���\n"   );
		delay_ms(500);
		delay_ms(500);
		//������
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


