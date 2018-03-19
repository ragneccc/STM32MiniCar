#include "myIIc.h"
#include "delay.h"
#include "stm32f4xx_gpio.h"


/*********************************************************************
**������IO��ģ��IIC����غ���
**����������IICЭ�鴴�� �������������
**����ʱ�䣺����
**�����ߣ�ѧ��
**���¸���ʱ�䣺2018��3��19��15:37:14
**********************************************************************/






/*********************************************************************
�ԡ���IO��ʼ
**********************************************************************/
void IICInit(void)
{		
	  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//ʹ��GPIOBʱ��

  //GPIOB8,B9��ʼ������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��
	SCL=1;
	SDA=1;
}

/*********************************************************************
�ԡ�����ʼ
**********************************************************************/
void IICStart(void){
	SDA_OUT();
	SDA = 1;
	SCL = 1;
	delay_us(4);
	SDA = 0;
	delay_us(4);
	SCL = 0;
}

/*********************************************************************
�ԡ�������
**********************************************************************/
void IICStop(void){
	SDA_OUT();
	SCL = 0;
	SDA = 0;
	SCL = 1;
	delay_us(4);
	SDA = 1;
	delay_us(4);	
}

/*********************************************************************
**�������ȴ��ӻ�Ӧ��
�ԡ���
**********************************************************************/
u8 IIC_Wait_Ack(void)
{
	u16 Over_time =0;
	SCL = 0;
	SDA_IN();
	SDA = 1;  delay_us(1);
	SCL = 1;  delay_us(2);
//	printf("cheakACK\n");
	while(READ_SDA)
	{
		Over_time++;
		if(Over_time>250) 
		{
			IICStop();
//			printf("NO ACK!\n");
			return 0;		
		}
		
	}
	delay_us(2);
	SCL = 0;
	return 1; 
}

/*********************************************************************
**��������Ϊ�ӻ��������Ѿ�Ӧ��
�ԡ���
**********************************************************************/
void IICsendACK(void){				//4us
	SDA_OUT();
	SCL = 0;
	SDA = 0;
	delay_us(4);
	SCL = 1;
	delay_us(4);
	SCL = 0;
}

/*********************************************************************
**��������Ϊ�ӻ���������Ӧ��
�ԡ���
**********************************************************************/
void IICsendNoACK(void){			//4us
	SCL = 0;
	SDA_OUT();
	SDA = 1;
	delay_us(2);
	SCL = 1;
	delay_us(2);
	SCL = 0;
}

/*********************************************************************
**����������һ��8λ�ֽ�
�ԡ���
**********************************************************************/
void IICsendByte(u8 dat){
		u8 t;
	SDA_OUT();
	SCL = 0;
	for(t=0;t<8;t++)
	{
		SDA = (dat&0x80)>>7;
		dat<<=1;
		delay_us(2);
		SCL = 1;
		delay_us(2);
		SCL = 0;
		delay_us(2);
	}
	if(IIC_Wait_Ack())
	{		
//		printf("ACK!\n");//IIC���Ӧ��
	}
	else 
	{		
//		printf("NO ACK!\n");
	}
//	IIC_CheakR(); 
}


/*********************************************************************
**��������ȡһ���ֽ�
**���أ�һ���ֽ�
�ԡ���
**********************************************************************/
u8 IICreadAByte(void){
	u8 i, ReciverData=0x00;
	SDA_IN();
	SDA = 1;
	for(i=0;i<8;i++)
	{
		SCL = 0;
		delay_us(2);
		SCL = 1;
		ReciverData|=READ_SDA;
//		printf("%d\t",READ_SDA);
		if(i==7) break;
		ReciverData<<=1;
		delay_us(4);
		
	}
//	printf("receive:%d\n",ReciverData);
//	if(Ack) IIC_Reply();
//	else    IIC_Norepl();
	return ReciverData;
}








