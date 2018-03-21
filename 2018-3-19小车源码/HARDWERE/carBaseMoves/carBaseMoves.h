#ifndef _carbasemoves_h
#define _carbasemoves_h


/***********************引用文件*************************/
#include "sys.h"
#include "delay.h"
#include "motor.h"
#include "gray.h"
#include "staticData.h"
#include "workingData.h"

/***********************宏定义**************************/


/***********************函数声明************************/
void car_Straight_Line(void);	//小车走直线
void car_TurnToAngle(u16 goal_Angle);//小车原地转向至指定角度值
																			//此函数运行期间其它非中断函数无法运行
u8 ture_Angle(u16 goal_Angle);//判断当前角度正确性							




#endif





