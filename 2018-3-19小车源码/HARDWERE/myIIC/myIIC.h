#ifndef _IICIIC_h
#define _IICIIC_h


/************************������***********************/

#include "sys.h"



/**************************�궨��***********************/

#define SDA_IN()  {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=0<<9*2;}	//PB9����ģʽ
#define SDA_OUT() {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=1<<9*2;} //PB9���ģʽ
#define SCL    PBout(8) //SCL
#define SDA    PBout(9) //SDA	 
#define READ_SDA   PBin(9)  //����SDA 



/*************************��������***********************/


void IICInit(void);						//��������
void IICStart(void);					
void IICStop(void);
void IICsendACK(void);				//����	ACK
void IICsendNoACK(void);			//���� No ACK
void IICsendByte(u8 i);				//��������
u8 IICreadAByte(void);				//���ӽӶ�ȡ


#endif
