#include "staticData.h"
#include "sys.h"



/******************************************************
函数：获得该往哪个角度走
参数：当前位置、下一个目的地
返回：角度值
描述：根据“地图”获取目的地范围
创建人：ragne
创建日期：2018年3月19日17:44:53
最新更改时间：2018年3月19日17:45:16
备注：当地图文件出现问题会返回0
******************************************************/
u16 getStaticAngle(u16 space,u16 nextSpace){
	u8 i;
	for(i=0;i<5;i++){
		if(nextSpace==nextNode[space][i]){
			return nextAngle[space][i];
		}
	}
	return 0;//出现问题才会返回0
}




