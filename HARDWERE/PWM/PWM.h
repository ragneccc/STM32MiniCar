#ifndef _pwm_H
#define _pwm_H
#include "sys.h"
#define IN1 PDout(8)	
#define IN2 PDout(10)
#define IN3 PDout(9)
#define IN4 PDout(11)


void Moter_PWM_Init(u16 arr,u16 psc); //pwm ��ʼ��
void GPIO_IN_Init(void);									//�����ʼ��
#endif	
