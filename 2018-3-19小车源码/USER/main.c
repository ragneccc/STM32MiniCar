#include "stm32f4xx.h"					//����ͷ�ļ�
#include "usart.h"							//����1 ������ʹ��printf��
#include "delay.h"							//�δ���ʱ
#include "myIIc.h"							//ģ��IIC
#include "DMA.h"									//dma���ڽ��մ���������
#include "blance_Usart6.h"				//����6	3���ͷ�ļ�
#include "blance_6axle_usart6.h"	//����6 6���ͷ�ļ�		ͨ��ֻ�� 3���ͷ�ļ�ʹ������һ��������6��Դ��ͻ��
#include "motor.h"							//���
#include "McNamara_motor.h"			//�����ĸ��
#include "gray.h"								//���ֻҶ�
#include "compassGY273.h"		//ָ����
#include "QMCGY273.h"				//ָ�������
#include "LCD_1602_IIC.h"				//lcd1602ģ��IIC����
#include "TIMDataCollect.h"			//��ʱ�������ݿ�
#include "staticData.h"					//��̬���ݱ��
#include "workingData.h"				//��̬���ݱ��
#include "carBaseMoves.h"
/*==============ͷ�ļ����þ�������=========================*/

u8 i=0;
int main(void)
{
	
/**************����������ʼ��*****************/					//����ռ��	2018��3��23��
			delay_init(84);			//��ʱ������ʼ��
			NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//�ж����ȼ�����
			uart_init(115200);	//����1��ʼ��									PA9		PA10
			IICInit();					//IIC��ʼ������								PB8		PB9
			delay_ms(50);			//�ȴ��ȶ�
			
/**************Ӳ��ģ���ʼ��*********************/
//			McNamara_Init();		//�����ĸ��������4·����	��	PB(12,13,14,15)PD(8,9,10,11 + 12,13,14,15)
			MOTOR_Config_Init();			//�����ʼ��							TIM4	PB12	PB13	D8 D9 D10 D11
//			blance_Usart6_Init();			//6�ᴫ��������ģ��			usart6	PG9	PG14									//�������������z������
//			blance_6axle_Usart6_Init();	//ͨ��֮��3��ģ���ʼ������ѡ��һ����usart6��Դ��ͻ��
			DMA_6axle_Usart6_Config();
			DMA_6axle_usart6RX_Init();	//DMA��������	DMA�жϴ�������
//			QMCGY273_Init();					//iicͨ�����̴�����			ģ��iic������������ʼ��
//			compassGY273Init();				//iic����								ģ��IIC����
			Digital_Init();						//���ֻҶ�								PA(1.2.4.7) PF(3.5.7.9)
		
	
/**************�������ģ���ʼ��******************/
			//TIMDataCollect_IRQ_Init(u16 arr,u16 psc);				//��ʱ�������ݿ�����

	
/***************�߼�����**********************/

	delay_ms(500);	//�ȴ��ȶ�
	while(1){
		delay_ms(500);

//		car_TurnToAngle(getStaticAngle(travel_Way[i] , travel_Way[1+i]));delay_ms(500);
//		Set_Motor(20,20);
//		delay_ms(500);
//		i++;
/***************�߼����ֽ���******************/


/******************���Դ���*************************/


		/*****����1 ͨ������6���С����б�ķ���Ƕ�	ȡֵ0~360*********/
//		printf("%d\t",working_Blance_Angle_X);
//		printf("%dend\n",working_Blance_Angle_Y);
//			//printf("���ݸ��´�%d��ʧ��%dend\n",tt,aa-tt);tt=0;aa=0;
//		get_balance_Angle();		//�������� working_Blance_Angle_X��working_Blance_Angle_Y
		
		
			/*****����2 ͨ������6���С��������̬�Ƕ�ֵ	ȡֵ0~360*********/
//		printf("%d\t",working_Blance_Angle_X);
//		printf("%d\t",working_Blance_Angle_Y);
//		printf("%d\n",working_Blance_Angle_Z);
//		//get_balance_6axle_Angle();		//�������� working_Blance_Angle_X��Y and Z
//		
		
		/*****����3                  *********/
		
		

/*****************���Դ������***********************/
	}
}
