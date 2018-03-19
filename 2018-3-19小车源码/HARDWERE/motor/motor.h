#ifndef __MOTOR_H
#define __MOTOR_H

/*
ͷ�ļ���Ϣ���� 1 ���ڣ�2 pwm��3 TFT��ĻGY_61��������ٶȼơ�������ǣ������� 4 �����������弯��Ϊ��ͷ�ļ�
-----------------------------------------------------------------�����ķָ���------------------------------------------------------------------
���ţ��ο����������趨
		
---------------------------------------------------------------�����ķָ���------------------------------------------------------------------
������	 		 int AI(unsigned int a) -->��ô�ĳһAI�ϵ���ֵ
				 void Display_Desc()  -->��ӡ�ض���һ���ַ�
				 void Print_Ai();  -->����Ļ�ϴ�ӡAI����ֵ
				 void Init_stc();  -->��ʼ��������Դ���������ؼ�
		 
��Ҫ����ͷ�ļ�����ĺ���

				��TFT.hͷ�ļ��еĿ��ýӿں�����

				void Display_ASCII8X16_Color(uint x0,uint y0,uchar *s,uint forecolor,uint backgroundcolor)-->����Ļ�ϴ�ӡһ���ַ���


				��pwm.hͷ�ļ��еĿ��ýӿں�����

				void pwm_init() -->pwm�źų�ʼ������		
				void pwm1_set(int y)  -->��һ·PWM�ź�����		 
				void pwm2_set(int x);  -->�ڶ�·PWM�ź�����
				void delay(unsigned int n);  -->��ʱ

				��GY_61.hͷ�ļ��еĿ��ýӿں�����

				��uart.hͷ�ļ��еĿ��ýӿں�����
				void UartInit();					   -->����ͨ�ų�ʼ��
				void SendOneByte(unsigned char x); 	   -->���ڷ���һ�ֽ�����
				void SendPICE(unsigned char *ll);	   -->���ڷ���һ������
				
				
��д�ˣ���ܲ��
----------------------------------------------------------------�����ķָ���----------------------------------------------------------------*/


#include "sys.h"


#define LEFT_SIDE  0
#define RIGHT_SIDE 1
#define FORWARD  0
#define BACKWARD 1


#define IN1 	PDout(8)
#define IN2 	PDout(9)
#define IN3		PDout(10)
#define IN4 	PDout(11)

void Set_Motor(s32 left_wheel,s32 right_wheel);              //�����ĸ��������
/*
|�������ƣ�Set_Motor
|�������ܣ�������·�����ת��
|�����β�:
left_wheel, �����ٶ�   -60��60֮��
right_wheel, �����ٶ�  -60��60֮��
|����ֵ����:
GPIOD12�������left���ת�ķ���     D12=1ǰת  D12=0��ת
GPIOD13�����Ҳ�right���ת�ķ���    D13=0ǰת  D13=1��ת
*/

void MOTOR_Pwm_Config(void);
/*
|�������ƣ�MOTOR_Pwm_Config
|��������:��ʼ���������PWM�ź�
|�����βΣ���
|����ֵ���ԣ���
*/

void MOTOR_Direct_Config(void);
/*
|�������ƣ�MOTOR_Direct_Config
|��������:��ʼ�����ת������
|�����βΣ���
|����ֵ���ԣ���
*/

void MOTOR_Config(void);
/*
|�������ƣ�MOTOR_Config
|�������ܣ���ʼ�����
|�����βΣ���
|����ֵ���ԣ���
*/

void MOTOR_Direct_Control(u8 Which_Side,u8 Direct);
/*
|�������ƣ�MOTOR_Direct_Control
|�������ܣ�������·����ķ���
|�����βΣ�
left_wheel, ����  
right_wheel,����

|����ֵ���ԣ�
GPIOD5_D6�������left���ת�ķ���     D8=1��D10=0ǰת  D8=0��D10=1��ת
GPIOD7_D8�����Ҳ�right���ת�ķ���    D9=1��D11=0ǰת  D9=0��D11=1��ת
*/




#endif
