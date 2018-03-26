#include "run.h"
#include "pwm.h"
#include "delay.h"
//DI1距离传感器
//DI2右灰度
//DI3左灰度
//DI4激光
/***停止函数***/
//距离传感器顺时针调远，逆时针近
int DICount()
{
	int count=DI(1)+DI(2)+DI(3)+DI(4)+DI(5)+DI(6)+DI(7)+DI(8);
		return count;
}

void stop()
{
   Set_Motor(0,0);
}
/***延时函数***/
//void delay(unsigned long int i)
//{
//	i--;
//}
/*********
前进直线函数快(1)
*********/
void run1()
{ 
	if(DI(4)==1&&DI(5)==1){Set_Motor(60,50);}//1时为灰度亮
		
		 else if(DI(3)==1||DI(4)==1){Set_Motor(40,55);}//向右微调
		 else if(DI(6)==1||DI(5)==1){Set_Motor(50,40);}//向左微调
		 
		// else if(DI(7)==1){Set_Motor(45,30);}
		 else {Set_Motor(53,45);}
//	if(DI(4)==1&&DI(5)==1){Set_Motor(60,53);}//1时为灰度亮
//	else if(DI(5)==1&&DI(6)==1){Set_Motor(35,45);}//向右微调
//  else if(DI(3)==1&&DI(4)==1){Set_Motor(50,35);}//向左微调
//	else if(DI(5)==1){Set_Motor(35,45);}
//	else if(DI(6)==1){Set_Motor(35,45);}
//  else if(DI(3)==1){Set_Motor(50,35);}
//	else if(DI(4)==1){Set_Motor(50,35);}
//	else if(DI(8)==1){Set_Motor(35,45);}
//	else if(DI(1)==1){Set_Motor(50,35);}
//	else {Set_Motor(53,45);}
}
/*********
前进直线函数慢（1）
*********/
void run2()
{ 
	if(DI(4)==1&&DI(5)==1){Set_Motor(45,45);}//1时为灰度亮
		
		 else if(DI(3)==1||DI(4)==1){Set_Motor(35,45);}//向右微调
		 else if(DI(6)==1||DI(5)==1){Set_Motor(45,30);}//向左微调
		 
		// else if(DI(7)==1){Set_Motor(45,30);}
		 else {Set_Motor(45,45);}
		
}
/*********
turnleft
*********/
//void run2()
void turnLeft1()
{ 
	if(DI(4)==1&&DI(5)==1){Set_Motor(50,50);}//1时为灰度亮
		
		 else if(DI(3)==1||DI(4)==1){Set_Motor(-40,40);}//向右微调
		 else if(DI(6)==1||DI(5)==1){Set_Motor(50,30);}//向左微调
		 else if(DI(2)==1||DI(1)==1){Set_Motor(-40,40);}
		 //else if(DI(7)==1){Set_Motor(50,30);}
		 else {Set_Motor(50,50);}
}
void turnLeft2(){}
void turnLeft3(){}
/*********
turnright
*********/
//void run3()
void turnRight1()
{
	//delay_ms(2000);
	while(1)
	{
		if(DI(7)==1||DI(8)==1)
			while(1)
			{
				if(DI(5)==1&&DI(6)==1){break;}
				else{Set_Motor(50,-50);}
			}
		else {break;}
	}
	run2();
//	   if(DI(4)==1&&DI(5)==1){Set_Motor(50,50);}//1时为灰度亮
//		 else if(DI(3)==1||DI(4)==1){Set_Motor(35,45);}//向右微调
//		 else if(DI(6)==1||DI(5)==1){Set_Motor(50,-30);}//向左微调
//		 else if(DI(7)==1){Set_Motor(50,-30);}
//		// else {Set_Motor(50,50);}	 
 }
void turnRight2(){}
void turnRight3(){}
/*********
左右直线均可以
*********/
void run3()
{
	if(DI(4)==1&&DI(5)==1){Set_Motor(60,50);}//1时为灰度亮
		
		 else if(DI(3)==1||DI(4)==1){Set_Motor(-40,40);}//向右微调
		 else if(DI(6)==1||DI(5)==1){Set_Motor(50,-38);}//向左微调
		
		 else if(DI(1)==1){Set_Motor(-40,40);}
		 //else if(DI(7)==1){Set_Motor(50,-40);}
		 else if(DI(8)==1){Set_Motor(50,-45);}
		 else {Set_Motor(53,45);}
}
/*********
back
*********/
void run4()
{
		
}
/*********
test
*********/
void test1()//车上箱子之后在转身下来走run2() DI(9)==1前传感器 DI(10)==1后传感器 DI(11)==1下传感器  全部距离传感器
{
	while(1)
{
	if(DI(11)==0)
	{
			while(1)
			{
				if(DI(9)==1)
				{	
					 while(1)
						{
							if(DI(10)==0){Set_Motor(60,-55);delay_ms(100);}//60,-50转的还可以，稳
							else if(DI(10)==1)break;
						}
				}
				else if(DI(9)==0)
				{
		//if(DI(3)==1&&DI(4)==1&&DI(5)==1&&DI(6)==1){turnRight();}
					run3();
				}
		}
	}
	else
		{
	   break;
		}		
}
run1();
		
	//}
	 //Set_Motor(60,-50);
			//else if(DI(1)==0&&DI(2)==0&&DI(3)==0&&DI(4)==0&&DI(5)==0&&DI(6)==0&&DI(7)==0&&DI(8)==0&&(DI(9)==1))
		//if(DI(10)==1)stop();
		//else {Set_Motor(35,30);}
			//if(DI(4)==1&&DI(5)==1)
				//while(1)
			// {			
//			  if(DI(9)==1) stop();
//		    else {Set_Motor(35,30);}
//				{
//		        while(1)
//						{Set_Motor(60,-60);}    	
//				}	
//       }
}
void test2()//2号灯有问题，为了平衡放弃使用7号灯
{
	if(DI(4)==1&&DI(5)==1){Set_Motor(40,34);}//1时为灰度亮
	else if(DI(5)==1&&DI(6)==1){Set_Motor(-40,40);}//向右微调
  else if(DI(3)==1&&DI(4)==1){Set_Motor(50,-30);}//向左微调
	else if(DI(6)==1){Set_Motor(-40,40);}
  else if(DI(3)==1){Set_Motor(50,-30);}
	else if(DI(8)==1){Set_Motor(-40,40);}
	else if(DI(1)==1){Set_Motor(50,-45);}
	else {Set_Motor(40,34);}
}
void test3()
{
	
}
void start1()//出门
{
	int i=0;
		while(1)
		{
			if(DI(9)==1){stop();}
			else if(DI(9)==0)//加DI(9)==0是排除其他因素的影响
				{
					delay_ms(4000);
					for(;i<2;i++)
					{
					SHAKE_Head();
					}
					Set_Motor(45,40);
					delay_ms(500);
					break;
			  }
		}
		run1();
		delay_ms(2000);
		
}
void start2()//过长桥
{
	while(1)
	{
		if(DI(17)==1)
		{
			while(1)
			{
				Set_Motor(55,50);
				delay_ms(2000);
				while(1)
				{
					if(DI(11)==1)
					{
						run1();
						delay_ms(2000);
						break;
					}
					else 
					{
						Set_Motor(38,30);
					}
				}
				break;
			}
		}
		else
		{
			run1();
		}
	}
}
//	if(DI(4)==1&&DI(5)==1){Set_Motor(60,50);}//1时为灰度亮
//		
//		 else if(DI(3)==1||DI(4)==1){Set_Motor(40,55);}//向右微调
//		 else if(DI(6)==1||DI(5)==1){Set_Motor(50,40);}//向左微调
//		 
//		// else if(DI(7)==1){Set_Motor(45,30);}
//		 else {Set_Motor(53,45);}
void start3()//后退
{
	run1();
	if(DI(9)==1)
	{
		while(1)
		{
			{Set_Motor(-60,50);}
			if(DI(3)==1&&DI(4)==1){run1();break;}
		}
	}
	else
	{
		run1();
	}
}
void start4()
{
	stop();
	delay_ms(2000);
	run1();
//	delay_ms(2000);
	if(DI(11)==0)
	{
		Set_Motor(60,50);
		delay_ms(2000);
		while(1)
		{
//			Set_Motor(38,30);
			if(DI(11)==0)
			{
				Set_Motor(38,30);
			}
			else if(DI(11)==1)
			{
				break;
			}
		}
		while(1)
		{
			run3();
			delay_ms(3000);
				while(1)
				{
					if(DI(11)==0)
					{
						while(1)
						{
							if(DI(9)==1)
							{	
								while(1)
								{
									if(DI(10)==0){Set_Motor(60,-55);delay_ms(100);}//60,-50转的还可以，稳
									else if(DI(10)==1)break;
								}
							}
							else if(DI(9)==0)
							{
								run3();
							}
							break;
						}
						while(1)
						{
							run3();
							delay_ms(2000);
							if(DI(13)==1)
							{
								while(1)
								{
									stop();
									delay_ms(1000);
									while(1)
									{
										Set_Motor(60,-50);//旋转时可以试试莫一边为0
										if(DI(4)==1&&DI(5)==1)
										{
											run3();
											delay_ms(2000);
											while(1)
											{
												if(DI(13)==1){stop();}
												else if(DI(13)==0){run1();}
											}
										}
									}
									
								}
								
							}
						}
					}
					else //if(DI(11)==1)
					{
						run1();
					}		
				}
				
		}
	}
	else 
	{
		run1();
	}
}



