#include "stm32f4xx.h"		//����ͷ�ļ�
#include "usart.h"				//����1 ������ʹ��printf��
#include "delay.h"	
#include "mpu6050.h"			//����6
#include "motor.h"				//���
//#include "compassGY273.h"	//ָ����
//#include "QMCGY273.h"			//ָ�������
#include "myIIc.h"				//ģ��IIC


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
			MOTOR_Config();			//�����ʼ��
			mpu6050_Init();
			//QMCGY273_Init();
			//compassGY273Init();
	
	delay_ms(300);	//�ȴ��ȶ�
	
/***************�߼�����**********************/
	while(1){
		printf("begin\n");
		printf("end\n");
		delay_ms(500);delay_us(500);
	}
}
