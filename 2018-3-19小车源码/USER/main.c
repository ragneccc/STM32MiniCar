#include "stm32f4xx.h"		//����ͷ�ļ�
#include "usart.h"				//����1 ������ʹ��printf��
#include "delay.h"	
#include "blance_Usart6.h"			//����6
#include "motor.h"				//���
//#include "compassGY273.h"	//ָ����
//#include "QMCGY273.h"			//ָ�������
#include "myIIc.h"				//ģ��IIC
#include "TIMDataCollect.h"
#include "staticData.h"		//��̬���ݱ��
#include "workingData.h"	//��̬���ݱ��

/********************************************/


int main(void)
{
	
/**************����������ʼ��*****************/
			delay_init(84);			//��ʱ������ʼ��
			uart_init(115200);	//����1��ʼ��
			IICInit();					//IIC��ʼ������
			NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//�ж����ȼ�����
			delay_ms(100);			//�ȴ��ȶ�
	
/**************ģ���ʼ��*********************/
			MOTOR_Config_Init();			//�����ʼ��
			blance_Usart6_Init();
			//QMCGY273_Init();
			//compassGY273Init();
	
	

	
/***************�߼�����**********************/
	
	delay_ms(300);	//�ȴ��ȶ�
while(1){
		delay_ms(500);
		
		
/***************************���Դ���***********************************/


		/*****����1 ͨ������6���С����б�ķ���Ƕ�	ȡֵ0~360*********/
//		printf("%d\t",working_Blance_Angle_X);
//		printf("%dend\n",working_Blance_Angle_Y);
//		get_balance_Angle();		�������� working_Blance_Angle_X��working_Blance_Angle_Y
		
		
		
		/*****����2 ͨ������6���С����б�ķ���Ƕ�	ȡֵ0~360*********/
		
		

/****************************���Դ������*******************************/
		delay_ms(500);
	}
}
