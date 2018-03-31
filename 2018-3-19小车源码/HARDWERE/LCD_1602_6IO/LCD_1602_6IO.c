#include "LCD_1602_6IO.h"




/********************************************************
��������			6IO����LCD1602 �� ��ʼ��
������				void	
���أ�				void
������				��ʼ��io PE��8~13������������صļĴ�����ģʽ���õȣ��ο��ֲᣩ
�����ˣ�			ragne
����ʱ�䣺		2018��3��31��17:33:39
���¸���ʱ�䣺2018��3��31��17:33:43
********************************************************/
void LCD_1602_6IO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//ʹ��GPIOBʱ��

  //GPIOB8,B9��ʼ������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��


		Write_char_LCD1602(0,0x28);//����16*��ʾ��5x7����4λ���ݸ�4λ
		//delay_ms(1);
		LCD1602_EN=1;
		LCD1602_EN=0;
		Write_char_LCD1602(0,0x28);		//��ʾ��ʽ
		Write_char_LCD1602(0,0x0e);		//����ʾ���
		Write_char_LCD1602(0,0x06);		//������ƣ���Ļ��
		Write_char_LCD1602(0,0x01);		//��ʾ���㣬����ָ������
}




/********************************************************
��������			д�ַ�
������				Achar		
���أ�				void
������				�򲢿�д�ַ�
�����ˣ�			ragne
����ʱ�䣺		2018��3��31��17:39:29
���¸���ʱ�䣺2018��3��31��17:42:03
********************************************************/
void Write_char_LCD1602(u8 RS,u8 Achar)
{	
		LCD1602_RS = RS;				//д/���Ĵ���
					//LCD1602_RW = 0;	//Ĭ�Ͻӵ�,����ȡ��6��IO��
		delay_us(35);
		LCD1602_EN = 1;
		LCD_Write_char(Achar>>4);
		delay_us(35);
		LCD1602_EN = 0;
		LCD1602_EN = 1;
		LCD_Write_char(Achar);
		delay_us(35);
		LCD1602_EN = 0;

}



/********************************************************
��������			д����ַ�
������				achar		
���أ�				void
������				����ַ���������
�����ˣ�			ragne
����ʱ�䣺		2018��3��31��17:39:29
���¸���ʱ�䣺2018��3��31��17:39:34
********************************************************/
void LCD_Write_char(char achar)
{
		LCD1602_D4=achar%2;
		LCD1602_D5=(achar>>1)%2;
		LCD1602_D6=(achar>>2)%2;
		LCD1602_D7=(achar>>3)%2;
}



/********************************************************
��������			��LCD1602����ʾһ�����֣�С��99999��
������				hang ��space��achar		
���أ�				void
������				ʵ���ڵ�hang�еĵ�space��λ�ô�ӡ����������achar
�����ˣ�			ragne
����ʱ�䣺		2018��3��31��17:39:29
���¸���ʱ�䣺2018��3��31��17:39:34
********************************************************/
void Show_Achar(u8 hang,u8 space,char achar)
{
		u8 a1=0;
		if(hang==1)
		{
				a1=0x80|(space-1);
		}
		else
		{
				a1=0xc0|(space-1);
		}
		Write_char_LCD1602(0,a1);
		delay_us(35);
		Write_char_LCD1602(1,achar);
		delay_us(35);
}





/********************************************************
��������			��LCD1602����ʾһ�����֣�С��99999��
������				hang ��space��NUm		
���أ�				void
������				ʵ���ڵ�hang�еĵ�space��λ�ÿ�ʼ��ӡ������������NUm
�����ˣ�			ragne
����ʱ�䣺		2018��3��31��17:23:59
���¸���ʱ�䣺2018��3��31��17:24:08
********************************************************/
void Show_ANum_LCD1602_6IO(u8 hang,u8 space,u16 NUm)
{
		u8 ge=0,shi=0,bai=0,qian=0,wan=0;
	
		ge 	 = 	NUm%10				;
		shi	 = 	(NUm%100)			/10;
		bai	 = 	(NUm%1000)		/100;
		qian = 	(NUm%10000)		/1000;
		wan	 =	(NUm%100000)	/10000;
		Show_Achar(hang,space		,'0'+wan		);
		Show_Achar(hang,space+1	,'0'+qian		);
		Show_Achar(hang,space+2	,'0'+bai		);
		Show_Achar(hang,space+3	,'0'+shi		);
		Show_Achar(hang,space+4	,'0'+ge			);
}



