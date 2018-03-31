#include "LCD_1602_6IO.h"




/********************************************************
函数名：			6IO控制LCD1602 的 初始化
参数：				void	
返回：				void
描述：				初始化io PE（8~13），并设置相关的寄存器，模式设置等（参考手册）
创建人：			ragne
创建时间：		2018年3月31日17:33:39
最新更新时间：2018年3月31日17:33:43
********************************************************/
void LCD_1602_6IO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//使能GPIOB时钟

  //GPIOB8,B9初始化设置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化


		Write_char_LCD1602(0,0x28);//设置16*显示，5x7点阵，4位数据高4位
		//delay_ms(1);
		LCD1602_EN=1;
		LCD1602_EN=0;
		Write_char_LCD1602(0,0x28);		//显示方式
		Write_char_LCD1602(0,0x0e);		//不显示光标
		Write_char_LCD1602(0,0x06);		//光标右移，屏幕动
		Write_char_LCD1602(0,0x01);		//显示清零，数据指针清零
}




/********************************************************
函数名：			写字符
参数：				Achar		
返回：				void
描述：				向并口写字符
创建人：			ragne
创建时间：		2018年3月31日17:39:29
最新更新时间：2018年3月31日17:42:03
********************************************************/
void Write_char_LCD1602(u8 RS,u8 Achar)
{	
		LCD1602_RS = RS;				//写/读寄存器
					//LCD1602_RW = 0;	//默认接地,不读取，6线IO口
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
函数名：			写半个字符
参数：				achar		
返回：				void
描述：				半个字符传到并口
创建人：			ragne
创建时间：		2018年3月31日17:39:29
最新更新时间：2018年3月31日17:39:34
********************************************************/
void LCD_Write_char(char achar)
{
		LCD1602_D4=achar%2;
		LCD1602_D5=(achar>>1)%2;
		LCD1602_D6=(achar>>2)%2;
		LCD1602_D7=(achar>>3)%2;
}



/********************************************************
函数名：			在LCD1602上显示一个数字（小于99999）
参数：				hang 、space、achar		
返回：				void
描述：				实现在地hang行的第space的位置打印出给定的字achar
创建人：			ragne
创建时间：		2018年3月31日17:39:29
最新更新时间：2018年3月31日17:39:34
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
函数名：			在LCD1602上显示一个数字（小于99999）
参数：				hang 、space、NUm		
返回：				void
描述：				实现在地hang行的第space的位置开始打印出给定的数字NUm
创建人：			ragne
创建时间：		2018年3月31日17:23:59
最新更新时间：2018年3月31日17:24:08
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



