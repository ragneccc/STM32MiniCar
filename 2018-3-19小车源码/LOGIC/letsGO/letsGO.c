#include "letsGO.h"



void letsGO(void)
{
	while(1)
	{
		car_Straight_Line();//����ֱ�ߣ�����һ��
		//����Ƿ񵽴�
		if(Find_node_Status(50))
		//�Ƿ�ת��
		{
				if(travel_Way[50]>30)//����ĵص��ǽ���
				{
							car_TurnToAngle(getStaticAngle(travel_Way[1] , travel_Way[1+1]));
							delay_ms(300);
				}
				else			//����  ����
				{
							
				}
		}
	}



}











