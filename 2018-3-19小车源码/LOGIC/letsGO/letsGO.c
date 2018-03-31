#include "letsGO.h"



void letsGO(void)
{
	while(1)
	{
		car_Straight_Line();//行走直线，矫正一次
		//检查是否到达
		if(Find_node_Status(50))
		//是否转弯
		{
				if(travel_Way[50]>30)//到达的地点是焦点
				{
							car_TurnToAngle(getStaticAngle(travel_Way[1] , travel_Way[1+1]));
							delay_ms(300);
				}
				else			//到达  景点
				{
							
				}
		}
	}



}











