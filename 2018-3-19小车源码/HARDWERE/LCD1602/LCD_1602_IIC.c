#include "LCD_1602_IIC.h"



u8 LCDdata;

void PCF8574_IIC_send(u8 add,char Achar)
{
//	IICStart();
//	IICsendByte(0x80);
//	delay_us(2);
//	IICStop();
//	IICsendACK();
//	IICsendNoACK();
//	IICreadAByte();
		IICStart();
		IICsendByte(add);
		IICsendByte(Achar);
		IICStop();		
}

void LCD_1602_Init()
{
	LCDdata|=4;	//	EN=1
//	PCF8574_IIC_send(0x27,0x3);
	delay_us(2);
	LCDdata&=11;//EN =0
	PCF8574_IIC_send(0x27,01);
}

void try1()
{
		LCD_1602_Init();
}



