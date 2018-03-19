#include "stm32f4xx.h"		//顶层头文件
#include "usart.h"				//串口1 （可以使用printf）
#include "delay.h"	
#include "mpu6050.h"			//串口6
#include "motor.h"				//电机
//#include "compassGY273.h"	//指南针
//#include "QMCGY273.h"			//指南针国产
#include "myIIc.h"				//模拟IIC


/********************************************/


int main(void)
{
	
/**************基本环境初始化*****************/
			delay_init(84);			//延时函数初始化
			uart_init(115200);	//串口1初始化
			IICInit();					//IIC初始化函数
			NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//中断优先级分组
			delay_ms(100);			//等待稳定
	
/**************模块初始化*********************/
			MOTOR_Config();			//电机初始化
			mpu6050_Init();
			//QMCGY273_Init();
			//compassGY273Init();
	
	delay_ms(300);	//等待稳定
	
/***************逻辑部分**********************/
	while(1){
		printf("begin\n");
		printf("end\n");
		delay_ms(500);delay_us(500);
	}
}
