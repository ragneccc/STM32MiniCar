#ifndef _LCD16026IO_HH
#define _LCD16026IO_HH


/***************�ļ�����*****************/
#include "sys.h"
#include "delay.h"


/***************��������*****************/
#define LCD1602_RS 			PEout(8)
#define LCD1602_EN 			PEout(9)
#define LCD1602_D4 			PEout(10)
#define LCD1602_D5 			PEout(11)
#define LCD1602_D6 			PEout(12)
#define LCD1602_D7 			PEout(13)


/***************��������*****************/
void LCD_1602_6IO_Init(void);
void Write_char_LCD1602(u8 RS,u8 Achar);
void LCD_Write_char(char achar);
void Show_Achar(u8 hang,u8 space,char achar);//ʵ���ڵ�hang�еĵ�space��λ�ô�ӡ����������achar
void Show_ANum_LCD1602_6IO(u8 hang,u8 space,u16 NUm);//ʵ���ڵ�hang�еĵ�space��λ�ÿ�ʼ��ӡ������������NUm��С��65535��������




	
#endif


