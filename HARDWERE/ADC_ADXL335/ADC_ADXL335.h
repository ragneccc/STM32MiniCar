#ifndef ADxl335_h
#define	ADxl335_h
#include "sys.h"


void ADXL_335_Init(void);
void GPIO_ADCin_Init(void);
void ADC3__Init(void);
u16 Get_Adc3(u8 ch);
#endif

