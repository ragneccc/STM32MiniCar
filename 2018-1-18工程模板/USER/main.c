#include "stm32f4xx.h"
#include "usart.h"		//可使用printf语句
#include "delay.h"		
#include "PWM.h"			//电锯驱动
#include "tumbler.h"	//不倒翁
#include "ADC_ADXL335.H"

//AD信号前倾增大
//电机IN1=0 ; IN4 = 0  为前进

int main(void)
{	

	u8 pwm = 110;
	Init();//初始化
		TIM_SetCompare1(TIM4,pwm);	//右轮（靠近32） GPIOD12
	  TIM_SetCompare2(TIM4,pwm);	//GPIOD13
//while(1){	
//	if(pwm>150|pwm<85)
//	{	
//		stop();break;
//	}
//		k =ADC_DataWork();
//	if(initname!=k)	  //不平衡
//	{
//		if(initname>k)		//向后倾斜
//		{												
//			if(IN1==1&&IN2==0)  	//前进状态
//				pwm-=2;
//			else if(IN1==1&&IN2==0)	//倒退状态
//				pwm+=2;
//		}	
//		else if(initname<k) //向前倾斜
//		{
//			if(IN1==1&&IN2==0)  		//前进状态
//				pwm+=2;
//			else if(IN1==1&&IN2==0)	//倒退状态
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
	Moter_PWM_Init(200,84);	  	 //pwm 初始化
	GPIO_IN_Init();							 //D8 D9 10 D11
	uart_init(115200);					//串口通信初始化
	Stm32_Clock_Init(336,8,2,7);//设置时钟,168Mhz 
	delay_init(168);	//延时初始化 	
	ADXL_335_Init();
}







