#include "compassGY273.h"
#include "sys.h"
#include "delay.h"
#include "math.h"

#include "usart.h"
u8 BUFcompass[6]={0,0,0,0,0,0};
u16 x,y,z;
double argleX,argleY,argleZ;

void compassGY273Init(){
		IICStart();                         
    IICsendByte(0x3C);          //写信号
		IICsendByte(0x00);
    IICsendByte(0x70);          //发送存储单元地址
    IICStart();
		IICsendByte(0x3C);          //写信号
		IICsendByte(0x01);
    IICsendByte(0x20);
		IICStop();
}
	

void IICreadByte(void){					//约500us +
		u8  i;
    IICStart();                         
    IICsendByte(0x3C);          //写信号
    IICsendByte(0x03);          //发送存储单元地址
       IICStart();
 IICsendByte(0x3D);         	//读信号
	delay_us(200);
	 for (i=0; i<6; i++)                      //连续读取6个地址数据，存储中BUF
   {
        BUFcompass[i] = IICreadAByte();          //BUF[0]存储数据
        if (i == 5)
        {
           IICsendNoACK();        	//最后一个数据需要回NOACK
        }
        else
				{
					IICsendACK();            	//回应ACK
				}
   }
    IICStop();                     	//停止信号
    delay_us(5);
}


void dealCompassData(void){
	
	extern u8 BUFcompass[];
	extern u16 x,y,z;
	
		x=BUFcompass[0] << 8 | BUFcompass[1];
    z=BUFcompass[2] << 8 | BUFcompass[3]; 
    y=BUFcompass[4] << 8 | BUFcompass[5]; 
		
		argleZ= atan2((double)y,(double)x) * (180 / 3.14159265) + 180;
		argleY= atan2((double)x,(double)z) * (180 / 3.14159265) + 180;
		argleX= atan2((double)y,(double)z) * (180 / 3.14159265) + 180;
		
}

void getCompassAngle(void){

	extern double argleX,argleY,argleZ;
	//compassInit();
		IICreadByte();
		dealCompassData();
		printf("mm%f\t%f\t%f\n",argleX,argleY,argleZ);

}









