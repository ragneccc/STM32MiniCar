#ifndef _pwm_H
#define _pwm_H
#include "sys.h"
#define IN1 PCout(0)	
#define IN2 PCout(1)
#define IN3 PFout(6)
#define IN4 PFout(7)


void TIM14_PWM_Init(u32 arr,u32 psc);
void TIM13_PWM_Init(u32 arr,u32 psc);
#endif
