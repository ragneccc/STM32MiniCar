#include "QMCGY273.h"
#include "math.h"



//ȫ�ֱ���
u8 BUFQMCcompass[6]={0,0,0,0,0,0};
u16 QMC5883Lx,	QMC5883Ly,	QMC5883Lz;
double QMC5883LargleX,	QMC5883LargleY,	QMC5883LargleZ;





/*********************************************************************
**������QMC5883lģ���ʼ��
**������void
**���أ�void
**������ͨ��IICдģ����ؼĴ������г�ʼ��
**����ʱ�䣺����
**�����ߣ�ragne
**���¸���ʱ�䣺2018��3��19��15:16:25
**********************************************************************/
void QMCGY273_Init(){
		Single_Write_HMC5883(0x09,0x1d);
																//0dH:����512������+ -2��˹������200kHz����������ģʽ
																//1dH:����512������+ -8��˹������200kHz����������ģʽ
}





/*********************************************************************
**������QMC5883lģ���ʼ��
**��������ַ	��д���ֵ
**���أ�void
**���������ַλд���ݣ���������ģʽ�������ѯ�ֲᣩ
**�����ߣ�ragne
**����ʱ�䣺2018��3��19��15:18:51
**���¸���ʱ�䣺2018��3��19��15:19:00
**********************************************************************/
void Single_Write_HMC5883(u8 REG_Address,u8 REG_data)
{
    IICStart();                  //��ʼ�ź�
    IICsendByte(0x1a);   //�����豸��ַ+д�ź�
    IICsendByte(REG_Address);    //�ڲ��Ĵ�����ַ����ο�����pdf 
    IICsendByte(REG_data);       //�ڲ��Ĵ������ݣ���ο�����pdf
    IICStop();                   //����ֹͣ�ź�
}



/*********************************************************************
**��������ȡ����
**��������ַ	��д���ֵ
**���أ�void
**��������ȡƬ�����ݣ�δ�����꣩��д��ȫ�ֱ���BUF[6]������
**�����ߣ�ragne
**����ʱ�䣺2018��3��19��15:18:51
**���¸���ʱ�䣺2018��3��19��15:23:06
**********************************************************************/
void QMCreadGY273(){
		u8  i;
    IICStart();                         
    IICsendByte(0x1a);          //д�ź�
    IICsendByte(0x00);          //���ʹ洢��Ԫ��ַ
    IICStart();
		IICsendByte(0x1b);       //���ź�
		delay_us(200);
	 for (i=0; i<6; i++)                      //������ȡ6����ַ���ݣ��洢��BUF
   {
        BUFQMCcompass[i] = IICreadAByte();          //BUF[0]�洢����
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



/*********************************************************************
**���������ݴ���
����������
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
**��������ȡ��������ĽǶ�ֵ
**��������ַ	��д���ֵ
**���أ�void
**��������BUF������ �������棬��ӡ���Ȳ���
**�����ߣ�ragne
**����ʱ�䣺2018��3��19��15:18:51
**���¸���ʱ�䣺2018��3��19��15:24:54
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

