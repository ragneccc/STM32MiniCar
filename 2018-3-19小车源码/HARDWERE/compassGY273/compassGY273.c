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
    IICsendByte(0x3C);          //д�ź�
		IICsendByte(0x00);
    IICsendByte(0x70);          //���ʹ洢��Ԫ��ַ
    IICStart();
		IICsendByte(0x3C);          //д�ź�
		IICsendByte(0x01);
    IICsendByte(0x20);
		IICStop();
}
	

void IICreadByte(void){					//Լ500us +
		u8  i;
    IICStart();                         
    IICsendByte(0x3C);          //д�ź�
    IICsendByte(0x03);          //���ʹ洢��Ԫ��ַ
       IICStart();
 IICsendByte(0x3D);         	//���ź�
	delay_us(200);
	 for (i=0; i<6; i++)                      //������ȡ6����ַ���ݣ��洢��BUF
   {
        BUFcompass[i] = IICreadAByte();          //BUF[0]�洢����
        if (i == 5)
        {
           IICsendNoACK();        	//���һ��������Ҫ��NOACK
        }
        else
				{
					IICsendACK();            	//��ӦACK
				}
   }
    IICStop();                     	//ֹͣ�ź�
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









