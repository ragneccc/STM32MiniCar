#include "QMCGY273.h"
#include "math.h"



//全局变量
u8 BUFQMCcompass[6]={0,0,0,0,0,0};
u16 QMC5883Lx,	QMC5883Ly,	QMC5883Lz;
double QMC5883LargleX,	QMC5883LargleY,	QMC5883LargleZ;





/*********************************************************************
**函数：QMC5883l模块初始化
**参数：void
**返回：void
**描述：通过IIC写模块相关寄存器进行初始化
**创建时间：不详
**创建者：ragne
**最新更改时间：2018年3月19日15:16:25
**********************************************************************/
void QMCGY273_Init(){
		Single_Write_HMC5883(0x09,0x1d);
																//0dH:带宽512、量程+ -2高斯、速率200kHz、连续采样模式
																//1dH:带宽512、量程+ -8高斯、速率200kHz、连续采样模式
}





/*********************************************************************
**函数：QMC5883l模块初始化
**参数：地址	、写入的值
**返回：void
**描述：向地址位写数据，用于设置模式（具体查询手册）
**创建者：ragne
**创建时间：2018年3月19日15:18:51
**最新更改时间：2018年3月19日15:19:00
**********************************************************************/
void Single_Write_HMC5883(u8 REG_Address,u8 REG_data)
{
    IICStart();                  //起始信号
    IICsendByte(0x1a);   //发送设备地址+写信号
    IICsendByte(REG_Address);    //内部寄存器地址，请参考中文pdf 
    IICsendByte(REG_data);       //内部寄存器数据，请参考中文pdf
    IICStop();                   //发送停止信号
}



/*********************************************************************
**函数：读取数据
**参数：地址	、写入的值
**返回：void
**描述：获取片内数据（未处理完），写入全局变量BUF[6]数组内
**创建者：ragne
**创建时间：2018年3月19日15:18:51
**最新更改时间：2018年3月19日15:23:06
**********************************************************************/
void QMCreadGY273(){
		u8  i;
    IICStart();                         
    IICsendByte(0x1a);          //写信号
    IICsendByte(0x00);          //发送存储单元地址
    IICStart();
		IICsendByte(0x1b);       //读信号
		delay_us(200);
	 for (i=0; i<6; i++)                      //连续读取6个地址数据，存储中BUF
   {
        BUFQMCcompass[i] = IICreadAByte();          //BUF[0]存储数据
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



/*********************************************************************
**函数：数据处理
？？？？？
**********************************************************************/
void QMC5883LGetArgleDelaDate(void){
	
	extern u8 BUFQMCcompass[];
	extern u16 QMC5883Lx,QMC5883Ly,QMC5883Lz;
	
		QMC5883Lx=BUFQMCcompass[1] << 8 | BUFQMCcompass[0];
    QMC5883Lz=BUFQMCcompass[3] << 8 | BUFQMCcompass[2]; 
    QMC5883Ly=BUFQMCcompass[5] << 8 | BUFQMCcompass[4]; 
		
		QMC5883LargleZ= atan2((double)QMC5883Ly,(double)QMC5883Lx) * (180 / 3.14159265) + 180;
		QMC5883LargleY= atan2((double)QMC5883Lx,(double)QMC5883Lz) * (180 / 3.14159265) + 180;
		QMC5883LargleX= atan2((double)QMC5883Ly,(double)QMC5883Lz) * (180 / 3.14159265) + 180;
		
}



/*********************************************************************
**函数：获取传感器测的角度值
**参数：地址	、写入的值
**返回：void
**描述：对BUF的数据 处理，保存，打印，等操作
**创建者：ragne
**创建时间：2018年3月19日15:18:51
**最新更改时间：2018年3月19日15:24:54
**********************************************************************/
void QMC5883LGetArgle(){
u8 k;
	extern double QMC5883LargleX,	QMC5883LargleY,	QMC5883LargleZ;
	extern u16 QMC5883Lx,QMC5883Ly,QMC5883Lz;
	//	QMCGY273_Init();
		QMCreadGY273();
		QMC5883LGetArgleDelaDate();
		printf("mm%d\t%d\t%d\n",QMC5883Lx,QMC5883Ly,QMC5883Lz);
	for(k=0;k<6;k++)
	{
		printf("%d  ",BUFQMCcompass[k]);
	}
	printf("\n"  );

}

