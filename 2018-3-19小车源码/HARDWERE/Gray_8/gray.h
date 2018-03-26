#ifndef __GRAY_IN_H
#define __GRAY_IN_H

/****************引用文件************///更改日期：2018年3月19日15:04:20

#include "sys.h"

/*****************宏定义*************///更改日期：2018年3月19日15:04:20

#define DI1		PAin(1)     //数字输入1
#define DI2		PAin(2)     //数字输入2
#define DI3		PAin(4)    	//数字输入3
#define DI4		PAin(7)     //数字输入4
#define DI5		PFin(3)     //数字输入5
#define DI6		PFin(5)    	//数字输入6.........................
#define DI7		PFin(7)     //数字输入7
#define DI8		PFin(9)     //数字输入8
//#define DIF		PDin(5)						
//#define DIS 	PEin(0)     //上面的距离传感器
//#define DIQY	PBin(4)     //前面右边的距离传感器
//#define DIQZ	PDin(7)     //前面左边的距离传感器
//#define DIH 	PDin(3)     //上面的距离传感器
//#define DIJG 	PCin(12)    //激光传感器


/*****************函数声明************///更改日期：2018年3月19日15:05:29
void Digital_Init(void);/*函数名称：数字接口初始化		|函数功能：初始化数字输入引脚			|函数形参： 无			|返回值特性：无*/

int DI(int number);




#endif

