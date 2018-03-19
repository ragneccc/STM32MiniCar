#include "myIIc.h"
#include "delay.h"
#include "stm32f4xx_gpio.h"


/*********************************************************************
**函数：IO口模拟IIC的相关函数
**描述：根据IIC协议创建 包含多个函数，
**创建时间：不详
**创建者：学长
**最新更改时间：2018年3月19日15:37:14
**********************************************************************/






/*********************************************************************
略。。IO初始
**********************************************************************/
void IICInit(void)
{		
	  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//使能GPIOB时钟

  //GPIOB8,B9初始化设置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化
	SCL=1;
	SDA=1;
}

/*********************************************************************
略。。开始
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
略。。结束
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
**函数：等待从机应答
略。。
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
**函数：作为从机，发送已经应答
略。。
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
**函数：作为从机，不发送应答
略。。
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
**函数：发送一个8位字节
略。。
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
//		printf("ACK!\n");//IIC检查应答
	}
	else 
	{		
//		printf("NO ACK!\n");
	}
//	IIC_CheakR(); 
}


/*********************************************************************
**函数：读取一个字节
**返回：一个字节
略。。
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








