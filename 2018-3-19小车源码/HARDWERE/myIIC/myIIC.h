#ifndef _IICIIC_h
#define _IICIIC_h


/************************引用文***********************/

#include "sys.h"



/**************************宏定义***********************/

#define SDA_IN()  {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=0<<9*2;}	//PB9输入模式
#define SDA_OUT() {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=1<<9*2;} //PB9输出模式
#define SCL    PBout(8) //SCL
#define SDA    PBout(9) //SDA	 
#define READ_SDA   PBin(9)  //输入SDA 



/*************************函数声明***********************/


void IICInit(void);						//配置引脚
void IICStart(void);					
void IICStop(void);
void IICsendACK(void);				//发送	ACK
void IICsendNoACK(void);			//发送 No ACK
void IICsendByte(u8 i);				//发送命令
u8 IICreadAByte(void);				//单子接读取


#endif
