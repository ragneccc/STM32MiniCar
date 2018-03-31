#ifndef	LCD1602_IIC_h
#define	LCD1602_IIC_h


#include "myIIC.h"
#include "delay.h"


void LCD_1602_IIC_Init(void);

void LCD_1602_IIC_Send_Byte(u8 RS,u8 achar);

#endif


