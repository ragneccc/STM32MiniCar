
#ifndef runrunrun_h
#define runrunrun_h



/*************************引用文件**********************/
#include "stm32f4xx.h" 
//#include "serson_IN.h"
#include "sys.h"			
//#include "PID.h"		//
#include "motor.h"	//电机驱动
#include "gray.h"		//灰度




/************************运行函数***********************/

/*********
1.直线函数快
2.quely 灰传感器值
*********/
void delay();
void run1();
/*********
1.直线函数快
2.quely 灰传感器值
*********/

void run2();
/*********
直线函数较慢(turnleft) 
**********/

void run3();
/*********
直线程序慢
**********/
void run4();
/*******
后退直线程序
********/
//void lrun5();
//void rrun6();
void turnRight1();//int L,int R
/********
1.右转弯函数
2.quely 灰传感器值
*********/
void turnRight2();//int L,int R
/********
1.右转弯函数
2.quely 灰传感器值
*********/
void turnRight3();//int L,int R
/********
1.右转弯函数
2.quely 灰传感器值
*********/

void turnLeft1();//int L,int R
/********
1.左转弯函数
2.quely 灰传感器值
*********/
void turnLeft2();//int L,int R
/********
1.左转弯函数
2.quely 灰传感器值
*********/
void turnLeft3();//int L,int R
/********
1.左转弯函数
2.quely 灰传感器值
*********/

void stop();
/******停止函数
********/
void test1();
/******测试函数
********/
void test2();
/******测试函数
********/
void test3();
/******测试函数
********/
void start1();
void start2();
void start3();
void start4();



#endif

