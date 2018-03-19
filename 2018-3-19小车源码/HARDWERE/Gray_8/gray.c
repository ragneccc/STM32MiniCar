#include "gray.h"



/*********************************************************************
**�������Ҷȴ�������ʼ��
**������void
**���أ�void
**������IO��������ߵ͵�ƽ�ȵĲɼ���
**			PA(1.2.4.7)��PF(3.5.7.9) ������������
**����ʱ�䣺����
**�����ߣ�����
**���¸���ʱ�䣺2018��3��19��14:57:59
**********************************************************************/
void Digital_Init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//RCC->AHB1ENR|=1<<0;     //ʹ��PORTAʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//RCC->AHB1ENR|=1<<5;     //ʹ��PORTFʱ��
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	GPIO_Set(GPIOA,PIN1|PIN2|PIN4|PIN7,GPIO_MODE_IN,0,0,GPIO_PUPD_PD);	//PA(1.2.4.7) ������������
	GPIO_Set(GPIOF,PIN3|PIN5|PIN7|PIN9,GPIO_MODE_IN,0,0,GPIO_PUPD_PD);  //PF(3.5.7.9) ������������
	//GPIO_Set(GPIOx,PINx|,GPIO_MODE_IN,0,0,GPIO_PUPD_PD);
	//GPIO_Set(GPIOx,PINx|,GPIO_MODE_IN,0,0,GPIO_PUPD_PD);
	GPIO_Set(GPIOE,PIN13|PIN14,GPIO_MODE_IN,0,0,GPIO_PUPD_PD); 
}


/*********************************************************************
**�������Ҷȵ���
**�������ڼ����Ҷ�
**���أ�״̬
**����ʱ�䣺����
**�����ߣ�����
**���¸���ʱ�䣺2018��3��19��15:01:16
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



