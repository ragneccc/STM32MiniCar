#include "McNamara_motor.h"
#include "math.h"




/********************************************************************
函数：McNamara万象控制
参数：前进方向 、 车头朝向 、 前进速度 、转弯速度
返回：void
描述：通过如上四个参数结算出四个轮子旋转方向，和速度（PWM与速度两码事）
创建时间：2018年3月26日17:59:02
创建者：range
最新更新时间：2018年3月26日17:59:27
********************************************************************/
void McMamara_Solve(u16 goAngle,u16 lookAt,u16 go_V,u16 turn_V)
{
	int chacha=(int)lookAt-(int)working_Angle;
	if(cos(chacha)>1.414)
	{
		
	}
	
}

/********************************************************************
**函数：麦克纳木初始化
**参数：void
**返回：void
**描述：麦克拉姆拉电机驱动pwm初始化
**创建时间：2018年3月26日17:14:06
**创建者：range
**最新更改时间：
********************************************************************/
void McNamara_Init()
{
	McNamara_PWM_Init();
	McNamara_Direct_Config();	
}

/*********************************************************************
**函数：PWM占空比调节
**参数：轮子编号	、 pwm值（-70~70）负数代表反转
**返回：void
**描述：对单个轮子进行占空比调节
**创建时间：2018年3月26日17:55:16
**创建者：range
**最新更改时间：2018年3月19日14:57:59
**********************************************************************/
void Set_McNamara_PWM(u8 whichWheel,s16 pwmARR)     //最大70最小-70
{ 
	u8 Status=0;
	if(pwmARR>=0)
	{
		Status++;
	}
	TIM_SetCompare2(TIM4,(u32)fabs(pwmARR));
	switch(whichWheel)
	{
		case 1:{INa=Status;INb=!Status;}break;
		case 2:{INc=Status;INd=!Status;}break;
		case 3:{INe=Status;INf=!Status;}break;
		case 4:{INg=Status;INh=!Status;}break;
		default:break;
	}
}



/*********************************************************************
**函数：电机PWM初始化
**参数：void
**返回：void
**描述：配置好pwm的周期，并使能
**创建时间：2018年3月26日17:55:32
**最新更改时间：2018年3月26日17:55:40
**********************************************************************/
void McNamara_PWM_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  		//TIM4时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); 	//使能PORTD时钟	
	
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4); //GPIOD12复用为定时器4
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource15,GPIO_AF_TIM4);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13|GPIO_Pin_14 | GPIO_Pin_15;//GPIOd12/13/14/15
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
//通道1	
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);  				//根据T指定的参数初始化外设TIM4 4OC1
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  //使能TIM4在CCR1上的预装载寄存器
//通道2
	TIM_OC2Init(TIM4, &TIM_OCInitStructure); 			 		//根据T指定的参数初始化外设TIM1 4OC2
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);  //使能TIM4在CCR1上的预装载寄存器
//通道3
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);  				//根据T指定的参数初始化外设TIM4 4OC3
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  //使能TIM4在CCR1上的预装载寄存器
//通道4
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);  				//根据T指定的参数初始化外设TIM4 4OC4
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);  //使能TIM4在CCR1上的预装载寄存器
 
	TIM_ARRPreloadConfig(TIM4,ENABLE);//ARPE使能 
	TIM_Cmd(TIM4, ENABLE); 					  //使能TIM4 
}  

/*********************************************************************
**函数：McNamara电机转向引脚初始化
**参数：void
**返回：void
**描述：电机旋转方向控制引脚 初始化
**创建时间：2018年3月26日17:55:54
**最新更改时间：2018年3月19日15:13:50
**********************************************************************/
void McNamara_Direct_Config()             											
{												
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//使能GPIOF时钟

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_8 | GPIO_Pin_10 | GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化
	
		INa=0;
		INb=1;
	
		INc=0;
		INd=1;
	 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化
		
		INe=0;
		INf=1;
		
		INg=0;
		INh=1;
}









