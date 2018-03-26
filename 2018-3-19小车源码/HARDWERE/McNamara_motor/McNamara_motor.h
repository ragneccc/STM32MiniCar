#ifndef _McNamara_motor_h
#define _McNamara_motor_h

		//�����ķ����������
		
/**************************�ļ�����*******************/
#include "sys.h"
#include "math.h"
#include "workingData.h"

/*************************��������********************/
#define INa 	PDout(8)
#define INb 	PDout(9)
#define INc		PDout(10)
#define INd 	PDout(11)

#define INe 	PBout(12)
#define INf 	PBout(13)
#define INg		PBout(14)
#define INh 	PBout(15)


/*************************��������********************/
void McNamara_Init(void);						//�ܵĳ�ʼ��
void Set_McNamara_PWM(u8 whichWheel,s16 pwmARR);//�������ӿ���PWM��������
void McNamara_PWM_Init(void);				//pwm�ĳ�ʼ��
void McNamara_Direct_Config(void);	//McNamara�ַ���������ų�ʼ�� 

void McMamara_Solve(u16 goAngle,u16 lookAt,u16 go_V,u16 turn_V);//�ٶȽ���




#endif














