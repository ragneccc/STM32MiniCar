#include "carBaseMoves.h"




/**********************************************************************待调整
**函数：小车走直线		motor_Straight_Line
**参数：v  速度
**返回：void
**描述：设置占空比;通过测量的静态数据调节两轮的速度偏差
**创建时间：2018年3月20日21:16:58
**创建者：range
**最新更改时间：2018年3月20日21:17:02
***********************************************************************/
void car_Straight_Line(){
	Set_Motor(working_v,working_v+static_FalsePWM);
}



/**********************************************************************待完善
**函数名			：car_TurnToAngle	原地转弯
**参数			：目标角度
**返回			：void
**描述			：原地转弯，通过多扫描角度值直到为指定角度为止
**创建时间		：2018年3月20日21:16:58
**创建者			：range
**更改时间		：2018年3月21日18:49:06
**全局参数		：
			//working_TurnV				转角速度
			//working_Angle				当前角度
			//goal_Angle					目标角度
			//working_FalsePWM		占空比偏差
			//working_FalseAngle	允许角度偏差
bug？
***********************************************************************/
void car_TurnToAngle(u16 goal_Angle)
{
	if( ((working_Angle+360-goal_Angle)%360)>180)			//判断应该向左转还是向右转（更近）
	{
			Set_Motor(-static_TurnV,static_TurnV+static_FalsePWM);//左
	}
	else
	{	
			Set_Motor(static_TurnV,-(static_TurnV+static_FalsePWM));
	}
	while(1)			//扫描车是否转弯完毕
	{
			if(ture_Angle(goal_Angle))	//角度正确
			{
					Set_Motor(0,0);
					break;
			}
			else												//角度不正确,继续扫描
			{
					delay_us(50);	//词句不知道有没有用
			}
			//可在这里添加判断条件时间过长跳出函数（产生：迷路，错误，bug）
	}
}




/**********************************************************************待完善
**函数名			：判断角度是否正确
**参数			：目标角度
**返回			：1/0
**描述			：在 误差值 范围内角度是否匹配匹配则反会1
**创建时间		：2018年3月21日12:54:09
**创建者			：range
**更改时间		：2018年3月21日18:49:23
***********************************************************************/
u8 ture_Angle(u16 goal_Angle)
{
	//working_Angle				当前角度
	//goal_Angle					目标角度
	//working_FalseAngle	允许角度偏差
	if(goal_Angle>(360-static_FalseAngle))
	{
			//(goal_Angle+360-static_FalseAngle)<=(working_Angle+360
			if(			(working_Angle<=((goal_Angle+static_FalseAngle)%360))
					||(	(working_Angle+360)>=(goal_Angle+360-static_FalseAngle)	)		)
			{
					return 1;		//角度在目标内
			}
			else
			{
					return 0;
			}
	}
	else
	{	
			if(			(working_Angle<=(goal_Angle+static_FalseAngle))
					&&(	(working_Angle+360)>=(goal_Angle+360-static_FalseAngle)	)		)
			{
					return 1;		//角度在目标内
			}
			else
			{
					return 0;
			}
	}
}









