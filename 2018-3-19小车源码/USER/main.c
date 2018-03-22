#include "stm32f4xx.h"		//顶层头文件
#include "usart.h"				//串口1 （可以使用printf）
#include "delay.h"	
#include "blance_Usart6.h"			//串口6
#include "motor.h"				//电机
//#include "compassGY273.h"	//指南针
//#include "QMCGY273.h"			//指南针国产
#include "myIIc.h"				//模拟IIC
#include "TIMDataCollect.h"
#include "staticData.h"		//静态数据表格
#include "workingData.h"	//动态数据表格

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
			MOTOR_Config_Init();			//电机初始化
			blance_Usart6_Init();
			//QMCGY273_Init();
			//compassGY273Init();
	
	

	
/***************逻辑部分**********************/
	
	delay_ms(300);	//等待稳定
while(1){
		delay_ms(500);
		
		
/***************************测试代码***********************************/


		/*****测试1 通过串口6获得小车倾斜的方向角度	取值0~360*********/
//		printf("%d\t",working_Blance_Angle_X);
//		printf("%dend\n",working_Blance_Angle_Y);
//		get_balance_Angle();		更新数据 working_Blance_Angle_X、working_Blance_Angle_Y
		
		
		
		/*****测试2 通过串口6获得小车倾斜的方向角度	取值0~360*********/
		
		

/****************************测试代码结束*******************************/
		delay_ms(500);
	}
}
