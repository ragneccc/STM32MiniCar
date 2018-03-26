#ifndef _McNamara_motor_h
#define _McNamara_motor_h

		//麦克拉姆轮驱动程序
		
/**************************文件引用*******************/
#include "sys.h"
#include "math.h"
#include "workingData.h"

/*************************变量声明********************/
#define INa 	PDout(8)
#define INb 	PDout(9)
#define INc		PDout(10)
#define INd 	PDout(11)

#define INe 	PBout(12)
#define INf 	PBout(13)
#define INg		PBout(14)
#define INh 	PBout(15)


/*************************函数声明********************/
void McNamara_Init(void);						//总的初始化
void Set_McNamara_PWM(u8 whichWheel,s16 pwmARR);//单个轮子控制PWM包括正反
void McNamara_PWM_Init(void);				//pwm的初始化
void McNamara_Direct_Config(void);	//McNamara轮方向控制引脚初始化 

void McMamara_Solve(u16 goAngle,u16 lookAt,u16 go_V,u16 turn_V);//速度解算




#endif














