#include "status.h"



u8 Find_node_Status(u16 nextspace)
{
		if(nextspace>30)					//��ͼ��ǰ��ʮ��Ϊ���㣬��30��λ�����߽���
		{
				return cleck_turnDI_Status();
		}
		else											//���� ����
		{
				return cleck_X_Angle();
		}
}


u8 cleck_X_Angle()
{
		if(cos(working_Blance_Angle_X/57.3)>cos(10/57.3))
		{
				return 1;
		}
		return 0;
}


u8 cleck_Y_Angle()
{
		if(cos(working_Blance_Angle_Y/57.3)>cos(10/57.3))
		{
				return 1;
		}
		return 0;
}


u8 cleck_turnDI_Status()
{
		if(DI(1)==1||DI(8)==1)
		{
				return 1;
		}
		else
		{
				return 0;
		}
}

