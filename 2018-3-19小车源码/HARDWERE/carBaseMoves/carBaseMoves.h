#ifndef _carbasemoves_h
#define _carbasemoves_h


/***********************�����ļ�*************************/
#include "sys.h"
#include "delay.h"
#include "motor.h"
#include "gray.h"
#include "staticData.h"
#include "workingData.h"

/***********************�궨��**************************/


/***********************��������************************/
void car_Straight_Line(void);	//С����ֱ��
void car_TurnToAngle(u16 goal_Angle);//С��ԭ��ת����ָ���Ƕ�ֵ
																			//�˺��������ڼ��������жϺ����޷�����
u8 ture_Angle(u16 goal_Angle);//�жϵ�ǰ�Ƕ���ȷ��							




#endif





