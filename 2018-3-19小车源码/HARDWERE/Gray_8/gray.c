#include "gray.h"



/*********************************************************************
**函数：灰度传感器初始化
**参数：void
**返回：void
**描述：IO引脚输入高低电平度的采集，
**			PA(1.2.4.7)和PF(3.5.7.9) 设置上拉输入
**创建时间：不详
**创建者：不详
**最新更改时间：2018年3月19日14:57:59
**********************************************************************/
void Digital_Init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//RCC->AHB1ENR|=1<<0;     //使能PORTA时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//RCC->AHB1ENR|=1<<5;     //使能PORTF时钟
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	GPIO_Set(GPIOA,PIN1|PIN2|PIN4|PIN7,GPIO_MODE_IN,0,0,GPIO_PUPD_PD);	//PA(1.2.4.7) 设置上拉输入
	GPIO_Set(GPIOF,PIN3|PIN5|PIN7|PIN9,GPIO_MODE_IN,0,0,GPIO_PUPD_PD);  //PF(3.5.7.9) 设置上拉输入
	//GPIO_Set(GPIOx,PINx|,GPIO_MODE_IN,0,0,GPIO_PUPD_PD);
	//GPIO_Set(GPIOx,PINx|,GPIO_MODE_IN,0,0,GPIO_PUPD_PD);
	GPIO_Set(GPIOE,PIN13|PIN14,GPIO_MODE_IN,0,0,GPIO_PUPD_PD); 
}


/*********************************************************************
**函数：灰度调用
**参数：第几个灰度
**返回：状态
**创建时间：不详
**创建者：不详
**最新更改时间：2018年3月19日15:01:16
**********************************************************************/
int DI(int  number)
{
	u8 value;
	switch(number)
	{
		case 1 :if(DI1==1) value=1; else value=0;break;
		case 2 :if(DI2==1) value=1; else value=0;break;
		case 3 :if(DI3==1) value=1; else value=0;break;
		case 4 :if(DI4==1) value=1; else value=0;break;
		case 5 :if(DI5==1) value=1; else value=0;break;
		case 6 :if(DI6==1) value=1; else value=0;break;
		case 7 :if(DI7==1) value=1; else value=0;break;
		case 8 :if(DI8==1) value=1; else value=0;break;
	}
	if(value==1)
		return 0;
	else
		return 1;	
}



