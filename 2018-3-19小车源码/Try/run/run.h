
#ifndef runrunrun_h
#define runrunrun_h



/*************************�����ļ�**********************/
#include "stm32f4xx.h" 
//#include "serson_IN.h"
#include "sys.h"			
//#include "PID.h"		//
#include "motor.h"	//�������
#include "gray.h"		//�Ҷ�




/************************���к���***********************/

/*********
1.ֱ�ߺ�����
2.quely �Ҵ�����ֵ
*********/
void delay();
void run1();
/*********
1.ֱ�ߺ�����
2.quely �Ҵ�����ֵ
*********/

void run2();
/*********
ֱ�ߺ�������(turnleft) 
**********/

void run3();
/*********
ֱ�߳�����
**********/
void run4();
/*******
����ֱ�߳���
********/
//void lrun5();
//void rrun6();
void turnRight1();//int L,int R
/********
1.��ת�亯��
2.quely �Ҵ�����ֵ
*********/
void turnRight2();//int L,int R
/********
1.��ת�亯��
2.quely �Ҵ�����ֵ
*********/
void turnRight3();//int L,int R
/********
1.��ת�亯��
2.quely �Ҵ�����ֵ
*********/

void turnLeft1();//int L,int R
/********
1.��ת�亯��
2.quely �Ҵ�����ֵ
*********/
void turnLeft2();//int L,int R
/********
1.��ת�亯��
2.quely �Ҵ�����ֵ
*********/
void turnLeft3();//int L,int R
/********
1.��ת�亯��
2.quely �Ҵ�����ֵ
*********/

void stop();
/******ֹͣ����
********/
void test1();
/******���Ժ���
********/
void test2();
/******���Ժ���
********/
void test3();
/******���Ժ���
********/
void start1();
void start2();
void start3();
void start4();



#endif

