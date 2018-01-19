#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"

//STM32F4工程模板-库函数版本

void changePwm(u16 x)		//调节占空比 int 类型的 0---100
{
	u16 y;
	y = 100000 *x/100;
	TIM_SetCompare1(TIM14,y);
}
	



int main(void)
{
	//初始化部分
	//void TIM_PWM(u32 arr,u32 psc); //定时器分分频  ；自动重装值
	uart_init(115200);
	delay_init(84);
	
		while(1)		
	{
		printf("你好在此打印任何东西\n"   );
		delay_ms(500);
		delay_ms(500);
		//函数体
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


