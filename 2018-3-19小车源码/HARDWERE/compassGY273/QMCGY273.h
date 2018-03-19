#ifndef _QMCcompassGY273_h
#define _QMCcompassGY273_h


//						QMC国产的 HMC进口的

/*
7bit设备地址：0x0d
写地址：		0x1a
读地址：		0x1b
配置地址：	0x09
						bit7和bit6磁力计的采样率（OSR）用来控制内部数字滤波器的带宽。可选512、256、128、64

						bit5和bit4为量程选择位：
											00代表满量程 +/- 2Gauss，
											01代表满量程 +/- 8Gauss，
											10和11保留
						bit3和bit2为数据输出速率控制，其中：
											00：10Hz
											01：50Hz
											10：100Hz
											11：200Hz	一般选择200Hz
						bit1和bit0为模式选择位：
											00：停止测量
											01代表连续测量模式
											10和11保留
			控制寄存器0x09H默认值为0x00，此时没有数据输出。常用的配置为写入0x1d，即采样率512，量程+/- 8Gauss，输出速率200Hz，连续测量模式。
数据地址：	x低 00H		x高01H
					y低	02H		y高03H
					z低	04H		z高05H

*/
/********************引用******************///最新更改日期：2018年3月19日15:27:51

#include "myIIc.h"
#include "sys.h"
#include "usart.h"
#include "delay.h"

/**********************变量声明************///最新更改日期：2018年3月19日15:27:51






/**********************函数声明************///最新更改日期：2018年3月19日15:28:22
void QMCGY273_Init(void);	//初始化
void QMCreadGY273(void);//读取
void QMC5883LGetArgleDelaDate(void);//处理
void QMC5883LGetArgle(void);//获取

void Single_Write_HMC5883(u8 REG_Address,u8 REG_data);//配置模式


#endif

