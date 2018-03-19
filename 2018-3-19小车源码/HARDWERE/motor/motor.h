#ifndef __MOTOR_H
#define __MOTOR_H

/*
头文件信息：将 1 串口，2 pwm，3 TFT屏幕GY_61（三轴加速度计——测倾角），还有 4 传感器引脚义集合为此头文件
-----------------------------------------------------------------华丽的分割线------------------------------------------------------------------
引脚：参考下面引脚设定
		
---------------------------------------------------------------华丽的分割线------------------------------------------------------------------
函数：	 		 int AI(unsigned int a) -->获得此某一AI上的数值
				 void Display_Desc()  -->打印特定的一串字符
				 void Print_Ai();  -->从屏幕上打印AI的数值
				 void Init_stc();  -->初始化所有资源，主函数必加
		 
主要引用头文件里面的函数

				◢TFT.h头文件中的可用接口函数◣

				void Display_ASCII8X16_Color(uint x0,uint y0,uchar *s,uint forecolor,uint backgroundcolor)-->从屏幕上打印一串字符串


				◢pwm.h头文件中的可用接口函数◣

				void pwm_init() -->pwm信号初始化函数		
				void pwm1_set(int y)  -->第一路PWM信号设置		 
				void pwm2_set(int x);  -->第二路PWM信号设置
				void delay(unsigned int n);  -->延时

				◢GY_61.h头文件中的可用接口函数◣

				◢uart.h头文件中的可用接口函数◣
				void UartInit();					   -->串口通信初始化
				void SendOneByte(unsigned char x); 	   -->串口发送一字节数据
				void SendPICE(unsigned char *ll);	   -->串口发送一条数据
				
				
编写人：李懿聪
----------------------------------------------------------------华丽的分割线----------------------------------------------------------------*/


#include "sys.h"


#define LEFT_SIDE  0
#define RIGHT_SIDE 1
#define FORWARD  0
#define BACKWARD 1


#define IN1 	PDout(8)
#define IN2 	PDout(9)
#define IN3		PDout(10)
#define IN4 	PDout(11)

void Set_Motor(s32 left_wheel,s32 right_wheel);              //左右四个电机控制
/*
|函数名称：Set_Motor
|函数功能：控制两路电机的转动
|函数形参:
left_wheel, 左轮速度   -60到60之间
right_wheel, 右轮速度  -60到60之间
|返回值特性:
GPIOD12控制左侧left电机转的方向     D12=1前转  D12=0后转
GPIOD13控制右侧right电机转的方向    D13=0前转  D13=1后转
*/

void MOTOR_Pwm_Config(void);
/*
|函数名称：MOTOR_Pwm_Config
|函数功能:初始化电机控制PWM信号
|函数形参：无
|返回值特性：无
*/

void MOTOR_Direct_Config(void);
/*
|函数名称：MOTOR_Direct_Config
|函数功能:初始化电机转向引脚
|函数形参：无
|返回值特性：无
*/

void MOTOR_Config(void);
/*
|函数名称：MOTOR_Config
|函数功能：初始化电机
|函数形参：无
|返回值特性：无
*/

void MOTOR_Direct_Control(u8 Which_Side,u8 Direct);
/*
|函数名称：MOTOR_Direct_Control
|函数功能：控制两路电机的方向
|函数形参：
left_wheel, 左轮  
right_wheel,右轮

|返回值特性：
GPIOD5_D6控制左侧left电机转的方向     D8=1，D10=0前转  D8=0，D10=1后转
GPIOD7_D8控制右侧right电机转的方向    D9=1，D11=0前转  D9=0，D11=1后转
*/




#endif
