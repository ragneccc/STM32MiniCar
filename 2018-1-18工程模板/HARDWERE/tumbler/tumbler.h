#ifndef	tumblerr_h
#define tumblerr_h
#include "PWM.h"
#include "sys.h"
#include "ADC_ADXL335.H"

#define NowADC_x ADC_DataWork()

void tumbler(void);
void Init(void);
u32 ADC_DataWork(void);
#endif



