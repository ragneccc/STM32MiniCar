#include "stm32f4xx.h"					//顶层头文件
#include "usart.h"							//串口1 （可以使用printf）
#include "delay.h"							//滴答延时
#include "myIIc.h"							//模拟IIC
#include "DMA.h"									//dma用于接收传感器数据
#include "blance_Usart6.h"				//串口6	3轴的头文件
#include "blance_6axle_usart6.h"	//串口6 6轴的头文件		通常只和 3轴的头文件使用其中一个（串口6资源冲突）
#include "motor.h"							//电机
#include "McNamara_motor.h"			//麦克纳母轮
#include "gray.h"								//数字灰度
#include "compassGY273.h"		//指南针
#include "QMCGY273.h"				//指南针国产
#include "LCD_1602_IIC.h"				//lcd1602模块IIC驱动
#include "LCD_1602_6IO.h"				//1602lcd 6个IO口驱动
#include "TIMDataCollect.h"			//定时更新数据库
#include "staticData.h"					//静态数据表格
#include "workingData.h"				//动态数据表格
#include "carBaseMoves.h"				//小车的一些基本运动
#include "letsGO.h"							//逻辑dog
#include "status.h"						//状态

/*==============头文件引用尽量不动=========================*/


 


int main(void)
{
	
		/**************基本环境初始化*****************/					//引脚占用	2018年3月23日
					delay_init(84);			//延时函数初始化
					NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//中断优先级分组
					uart_init(115200);	//串口1初始化									PA9		PA10
					IICInit();					//IIC初始化函数								PB8		PB9
					LCD_1602_6IO_Init();														//PE（8，9，10，11，12，13）
	
	
					delay_ms(50);			//等待稳定		
		/**************硬件模块初始化*********************/
//					McNamara_Init();		//麦克纳母轮驱动（4路驱动	）	PB(12,13,14,15)PD(8,9,10,11 + 12,13,14,15)
					MOTOR_Config_Init();			//电机初始化							TIM4	PB12	PB13	D8 D9 D10 D11
//					blance_Usart6_Init();			//6轴传感器串口模块			usart6	PG9	PG14									//发送命令可用于z轴清零
					blance_6axle_Usart6_Init();	//通常之和3轴模块初始化函数选用一个（usart6资源冲突）
//					DMA_6axle_Usart6_Config();
//					DMA_6axle_usart6RX_Init();	//DMA接收数据	DMA中断处理数据
//					QMCGY273_Init();					//iic通信罗盘传感器			模拟iic见基本环境初始化
//					compassGY273Init();				//iic罗盘								模拟IIC总线
					Digital_Init();						//数字灰度								PA(1.2.4.7) PF(3.5.7.9)
				


	
/***************逻辑部分**********************/
	delay_ms(1000);	//等待稳定
	while(1){
	//	delay_ms(200);
	
		

		
		
	
/***************逻辑部分结束******************/


	
		
		

/******************测试代码*************************/


			/*****测试1 通过串口6获得小车倾斜的方向角度	取值0~360*********///3轴
//		printf("%d\t",working_Blance_Angle_X);
//		printf("%dend\n",working_Blance_Angle_Y);
//			//printf("数据更新次%d丢失次%dend\n",tt,aa-tt);tt=0;aa=0;
//		get_balance_Angle();		//更新数据 working_Blance_Angle_X、working_Blance_Angle_Y
		
		
			/*****测试2 通过串口6获得小车三个姿态角度值	取值0~360*********///6轴
//		printf("%d\t",working_Blance_Angle_X);
//		printf("%d\t",working_Blance_Angle_Y);
//		printf("%d\n",working_Blance_Angle_Z);
//		get_balance_6axle_Angle();		//更新数据 working_Blance_Angle_X、Y and Z
	
		
			/*****测试3  按照预设路线方向依次转弯   ***********************/	
//		car_TurnToAngle(getStaticAngle(travel_Way[i] , travel_Way[1+i]));delay_ms(500);
//		Set_Motor(20,20);
//		delay_ms(500);
//		i++;


			/*****测试4 DMA6轴数据处理  ***********************/
//		printf("%d\t",buf[5]);
//		printf("%d\t",working_Blance_Angle_X);
//		get_balance_6axle_Angle();


			/*****测试5 LCD1602_1602显示角度*********///3轴
//		Show_Achar(1,1,'X');
//		Show_Achar(1,10,'Y');
//		Show_Achar(2,1,'Z');
//		Show_ANum_LCD1602_6IO(1,3,working_Blance_Angle_X);
//		Show_ANum_LCD1602_6IO(1,12,working_Blance_Angle_Y);
//		Show_ANum_LCD1602_6IO(2,3,working_Blance_Angle_Z);
//		get_balance_6axle_Angle();


/*****************测试代码结束***********************/

	}
}
