#include "motor.h"
#include "math.h"
#include "sys.h"

/********************************************************************
**函数：电机初始化函数
**参数：void
**返回：void
**描述：准备哦好电机，调节占空比为0等待命令
**创建时间：2018年3月20日21:01:00
**创建者：range
**最新更改时间：2018年3月20日21:01:09
********************************************************************/
void MOTOR_Config_Init()
{
	MOTOR_Pwm_Config();
	MOTOR_Direct_Config();  
	TIM_SetCompare2(TIM4,0);TIM_SetCompare1(TIM4,0);		//默认
	//TIM_SetCompare2(TIM4,fabs(50));TIM_SetCompare1(TIM4,40); 测试用
}

/*********************************************************************
**函数：PWM占空比调节
**参数：通道1溢出值（左轮） 、通道2溢出值（右轮）
**返回：void
**描述：传入（70~-70）的数据以调节pwm波来控制电机转速
**创建时间：不详
**创建者：不详
**最新更改时间：2018年3月19日14:57:59
**********************************************************************/
void Set_Motor(s32 left_wheel,s32 right_wheel)     //最大70最小-70
{ 
	
	if(left_wheel>=0)
	{
		IN1=1;
		IN2=0;
		TIM_SetCompare1(TIM4,left_wheel);
	}
	else 
	{
		IN1=0;
		IN2=1;
		TIM_SetCompare1(TIM4,fabs(left_wheel));            //取绝对值
	}
	
	if(right_wheel>=0)
	{
		IN3=0;
		IN4=1;
		TIM_SetCompare2(TIM4,right_wheel);
	}
	else 
	{
		IN3=1;
		IN4=0;
		TIM_SetCompare2(TIM4,fabs(right_wheel));             //取绝对值

	}
}



/*********************************************************************
**函数：电机PWM初始化
**参数：void
**返回：void
**描述：配置好pwm的周期，并使能
**创建时间：不详
**最新更改时间：2018年3月19日15:11:43
**********************************************************************/
void MOTOR_Pwm_Config()
{
GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  		//TIM4时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); 	//使能PORTD时钟	
	
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4); //GPIOD12复用为定时器4
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13;           //GPIOd12/13
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOD,&GPIO_InitStructure);              //初始化PF9
	  
	TIM_TimeBaseStructure.TIM_Prescaler=168;  			//定时器分频	psc
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=100;   				//自动重装载值	arr
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);	//初始化定时器4
	
	//初始化TIM4 Channel1 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性低
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);  				//根据T指定的参数初始化外设TIM4 4OC1

	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  //使能TIM4在CCR1上的预装载寄存器
	
	TIM_OC2Init(TIM4, &TIM_OCInitStructure); 			 //根据T指定的参数初始化外设TIM1 4OC1

	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);  //使能TIM4在CCR1上的预装载寄存器
 
	TIM_ARRPreloadConfig(TIM4,ENABLE);//ARPE使能 
	
	TIM_Cmd(TIM4, ENABLE); 					  //使能TIM4 
}  


/*
 *函数名：MOTOR_Direct_Config
 *描述  :初始化电机转向引脚
 *输入  ：无
 *返回  ：无
 *调用  : 被内部调用
 */

/*********************************************************************
**函数：电机转向引脚初始化
**参数：void
**返回：void
**描述：电机旋转方向控制引脚 初始化
**创建时间：不详
**最新更改时间：2018年3月19日15:13:50
**********************************************************************/
void MOTOR_Direct_Config()             											
{												
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//使能GPIOF时钟

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_8 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化
	
		IN1=1;
		IN2=0;

  //RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//使能GPIOF时钟
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化
	
		IN3=0;
		IN4=1;
}


/*********************************************************************
???????????????????????


**********************************************************************/

void MOTOR_Direct_Control(u8 Which_Side,u8 Direct)
{
	if(Which_Side==LEFT_SIDE)
	{
				if(Direct==FORWARD)
				{
					IN1=1;
					IN2=0;
				}
				else if(Direct==BACKWARD)
				{
					IN1=0;
					IN2=1;
				}
	}
	else if(Which_Side==RIGHT_SIDE)
	{
				if(Direct==FORWARD)
				{
					IN3=1;
					IN4=0;
				}
				else if(Direct==BACKWARD)
				{
					IN3=0;
					IN4=1;
				}
	}
	
}




