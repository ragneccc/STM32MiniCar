#include "LCD_1602_IIC.h"




void LCD_1602_IIC_Init()
{
			IICStart();
			IICsendByte(0x4e);	//IIC模块默认地址0x27 -》0x4f/0x4e（加读写）
			LCD_1602_IIC_Send_Byte(0,0x28);	//显示方式
			LCD_1602_IIC_Send_Byte(0,0x0e);	//不显示光标
			LCD_1602_IIC_Send_Byte(0,0x06);	//光标右移，屏幕动
			LCD_1602_IIC_Send_Byte(0,0x01);		//显示清零，数据指针清零
			IICStop();
}

void LCD_1602_IIC_Send_Byte(u8 RS,u8 achar)	//带更改
{
	u8 name=0;
		name |= RS|0x04;		//EN = 1;RS = RS; RW = 0;
			IICsendByte(name);
		delay_us(30);
		name = (name&0x0f)|(achar&0xf0);			//name低4位不变 高四位=achar高四位
			IICsendByte(name);		//发送gao4位
		name &= 0xfb;				//EN = 0;
			IICsendByte(name);
		name |= 0x04;				//EN = 1;
			IICsendByte(name);	
		delay_us(30);
		name = (name&0x0f)|((achar<<4)&0xf0);			//name低4位不变 高四位=achar低四位
			IICsendByte(name);		//发送低4 为
		name &= 0xfb;				//EN = 0;
			IICsendByte(name);
		delay_us(30);
}

