#ifndef _status_hh
#define _status_hh


/*******************文件引用*********************/
#include "sys.h"
#include "delay.h"
#include "workingData.h"
#include "staticData.h"
#include "carBaseMoves.h"
#include "motor.h"
#include "math.h"


/*******************函数声明*********************/


void Check_X_Angle(void);
void Check_Y_Angle(void);
u8 cleck_X_Angle(void);
u8 cleck_turnDI_Status(void);
u8 Find_node_Status(u16 nextspace);

 





#endif



