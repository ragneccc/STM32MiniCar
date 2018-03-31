#include "LCD_1602_IIC.h"




void LCD_1602_IIC_Init()
{
			IICStart();
			IICsendByte(0x4e);	//IICģ��Ĭ�ϵ�ַ0x27 -��0x4f/0x4e���Ӷ�д��
			LCD_1602_IIC_Send_Byte(0,0x28);	//��ʾ��ʽ
			LCD_1602_IIC_Send_Byte(0,0x0e);	//����ʾ���
			LCD_1602_IIC_Send_Byte(0,0x06);	//������ƣ���Ļ��
			LCD_1602_IIC_Send_Byte(0,0x01);		//��ʾ���㣬����ָ������
			IICStop();
}

void LCD_1602_IIC_Send_Byte(u8 RS,u8 achar)	//������
{
	u8 name=0;
		name |= RS|0x04;		//EN = 1;RS = RS; RW = 0;
			IICsendByte(name);
		delay_us(30);
		name = (name&0x0f)|(achar&0xf0);			//name��4λ���� ����λ=achar����λ
			IICsendByte(name);		//����gao4λ
		name &= 0xfb;				//EN = 0;
			IICsendByte(name);
		name |= 0x04;				//EN = 1;
			IICsendByte(name);	
		delay_us(30);
		name = (name&0x0f)|((achar<<4)&0xf0);			//name��4λ���� ����λ=achar����λ
			IICsendByte(name);		//���͵�4 Ϊ
		name &= 0xfb;				//EN = 0;
			IICsendByte(name);
		delay_us(30);
}

