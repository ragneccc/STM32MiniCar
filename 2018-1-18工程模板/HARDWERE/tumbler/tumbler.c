#include "tumbler.h"
#include "delay.h"


u32 ADC_DataWork()				//因为采样值跳动大所以取 平均值
{
	u8 i;
	u32 m = 0;
	for(i=0;i<5;i++){
		m += Get_Adc3(ADC_Channel_9);
		delay_ms(2);
	}
	m/=5;
	return m/8;
}



