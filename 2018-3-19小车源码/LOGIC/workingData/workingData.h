#ifndef	_workingdata_H
#define _workingdata_H
#include "sys.h"
/****************************说明********************&&&&&&**************
			本文件声明小车运行驶时所有必要的变量
						包括：
							*	传感器时时变量值
							*	小车行驶路线“记忆”
							*	与其他电路通信的数据缓冲区
			本文件的值由一定时器中断更新
			或本身为使用时扫描IO口状态获得
对应的IO口 的更该需要更改源文件的函数  *_Init()更改IO配置以及硬件电路的更改

！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
		所有全局变量必须	用extern声明 并在workingData中初始化；
！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
************************************************************************/




/******************************基本状态**********************************/
extern s32 working_v;							//当前速度	no
extern u16 working_Angle;					//当前小车角度 no
extern u16 working_Blance_Angle_X;				//水平方向x轴角度（倾斜）
extern u16 working_Blance_Angle_Y;				//水平方向y轴角度（倾斜）
extern u16 working_Blance_Angle_Z;				//竖直方向z轴角度（指南）
extern u16 working_Length;				//从计数开始累计行驶长度


/*****************************数字传感器值********************************/
#define Gray1		DI1		//灰度传感器
#define Gray2		DI2
#define Gray3		DI3
#define Gray4		DI4
#define Gray5		DI5
#define Gray6		DI6
#define Gray7		DI7
#define Gray8		DI8

/*******************************函数声明**********************************/



#endif








