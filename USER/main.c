#include "stm32f4xx.h"
#include "usart.h"		//可使用printf语句
#include "delay.h"		
#include "PWM.h"			//电锯驱动
#include "tumbler.h"	//不倒翁


void changePwm14(u16 x)		//通道1：调节占空比 int 类型的 1---99
{
	u16 y;
	y =2*x-1;
	TIM_SetCompare1(TIM14,y);
}
void changePwm13(u16 x)		//通道2：调节占空比 int 类型的 1---99
{
	u16 y;
	y =2*x-1;
	TIM_SetCompare1(TIM13,y);
}
	




int main(void)
{
	//初始化部分
	//TIM14_PWM_Init(200-1,84-1);	//2kHz PWM
	TIM13_PWM_Init(200-1,84-1); //定时器分分频  ；自动重装值
	uart_init(115200);					//串口通信初始化
	Stm32_Clock_Init(336,8,2,7);//设置时钟,168Mhz 
	delay_init(168);			//延时初始化 
	
	
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





/*	原工程模板代码

#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"

//STM32F4工程模板-库函数版本

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


