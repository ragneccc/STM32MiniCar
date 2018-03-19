#ifndef	_compass_hh
#define _compass_hh


#include "sys.h"	
#include "myIIC.h"


void compassGY273Init(void);

void IICreadByte(void);

void dealCompassData(void);

void getCompassAngle(void);



#endif

