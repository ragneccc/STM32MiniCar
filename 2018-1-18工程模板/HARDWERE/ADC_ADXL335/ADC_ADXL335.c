#include "ADC_ADXL335.h"

void ADXL_335_Init(void)
{
  GPIO_ADCin_Init();    
	ADC3__Init();
}




void GPIO_ADCin_Init(void)  
{  
  GPIO_InitTypeDef  GPIO_InitStructure;  
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);  		//使能GPIOF时钟  
      
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;//ADXL335 X Y Z  对应 ADC3 的通道 9 14 15
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;							//模拟输入  
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;					//不带上下拉  
  GPIO_Init(GPIOF, &GPIO_InitStructure);										//初始化 
}  


void  ADC3__Init(void)
{    
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef       ADC_InitStructure;
 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE); //使能ADC3时钟

  
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3,ENABLE);	  //ADC3复位
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3,DISABLE);	//复位结束	 
 
 
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;//独立模式
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//两个采样阶段之间的延迟5个时钟
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //DMA失能
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;//预分频4分频。ADCCLK=PCLK2/4=84/4=21Mhz,ADC时钟最好不要超过36Mhz 
  ADC_CommonInit(&ADC_CommonInitStructure);//初始化
	
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//12位模式
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;//非扫描模式	
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//关闭连续转换
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//禁止触发检测，使用软件触发
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//右对齐	
  ADC_InitStructure.ADC_NbrOfConversion = 1;//1个转换在规则序列中 也就是只转换规则序列1 
  ADC_Init(ADC3, &ADC_InitStructure);//ADC初始化
	
	ADC_Cmd(ADC3, ENABLE);//开启AD转换器	 
}


u16 Get_Adc3(u8 ch)   
{
	  	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC3, ch, 1, ADC_SampleTime_480Cycles );	//ADC3,ADC通道,480个周期,提高采样时间可以提高精确度			    
  
	ADC_SoftwareStartConv(ADC3);		//使能指定的ADC3的软件转换启动功能	
	 
	while(!ADC_GetFlagStatus(ADC3, ADC_FLAG_EOC ));//等待转换结束

	return ADC_GetConversionValue(ADC3);	//返回最近一次ADC3规则组的转换结果
}


