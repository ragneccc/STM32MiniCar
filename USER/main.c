#include "stm32f4xx.h"
#include "usart.h"		//可使用printf语句
#include "delay.h"		
#include "PWM.h"			//电锯驱动
#include "tumbler.h"	//不倒翁
#include "ADC_ADXL335.H"

int main(void)
{
	
	Init();//初始化

	
	  TIM_SetCompare1(TIM4,150);	//右轮（靠近32） GPIOD12
	  TIM_SetCompare2(TIM4,150);	//GPIOD13
while(1){	
		u32 x = Get_Adc3(ADC_Channel_9);
		u32 y = Get_Adc3(ADC_Channel_14);
		u32 z = Get_Adc3(ADC_Channel_15);
		printf("%d **** %d ***** %d\n",x,y,z);
		delay_ms(120);
	}	
}






void Init(){
	Moter_PWM_Init(200,84);	  	 //pwm 初始化
	GPIO_IN_Init();							 //D8 D9 10 D11
	uart_init(115200);					//串口通信初始化
	Stm32_Clock_Init(336,8,2,7);//设置时钟,168Mhz 
	delay_init(168);	//延时初始化 	
	ADXL_335_Init();
}





