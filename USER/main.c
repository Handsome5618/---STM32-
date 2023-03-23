/****************************************
PA15:AD0   PB10:IIC_SCL   PB11:IIC_SDA
PA1:IIC_SCL_OLED      PA2:IIC_SDA_OLED
****************************************/
#include "oled.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "uart.h"
#include "stdio.h"
#include "angle.h"
#include "led.h"

int main(void)
{	 
	
	float pitch,roll,yaw; 		//ŷ����
	short aacx,aacy,aacz;		//���ٶȴ�����ԭʼ����
	short gyrox,gyroy,gyroz;	//������ԭʼ����
	short temp;                 //�¶�									

	LED_Init();
	delay_init();				//��ʱ��ʼ��
	OLED_Init();
	OLED_ColorTurn(0);          //0������ʾ��1 ��ɫ��ʾ
	OLED_DisplayTurn(0);        //0������ʾ 1 ��Ļ��ת��ʾ
	MPU_Init();				    //��ʼ��MPU6050
	USART1_Init();
	 
	OLED_ShowString(15,0,"Waiting",24,1);
	OLED_ShowString(0,28,"Initialise",24,1);
	OLED_Refresh();
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);		//ʹ��AFIOʱ��
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//��ֹJTAG,�Ӷ�PA15��������ͨIOʹ��,����PA15��������ͨIO!!!
	
	while(mpu_dmp_init())
 	{
		OLED_Clear();
		OLED_Refresh();
	}
	OLED_Clear();
	OLED_Refresh();
	
	OLED_Init();
	OLED_ColorTurn(0);          //0������ʾ��1 ��ɫ��ʾ
	OLED_DisplayTurn(0);        //0������ʾ 1 ��Ļ��ת��ʾ

	OLED_ShowString(0,0,"PITCH:",16,1);
	OLED_ShowString(0,15,"ROLL:",16,1);
	OLED_ShowString(0,31,"YAW:",16,1);
	OLED_ShowString(0,47,"TEMP:",16,1);
	OLED_Refresh();
 	while(1)
	{
		if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)
		{
			temp=MPU_Get_Temperature();					//�õ��¶�ֵ
			MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//�õ����ٶȴ���������
			MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//�õ�����������			
			
			printf("P%d ",(int)pitch);
			printf("R%d ",(int)roll);
			printf("y%d ",(int)yaw);
//			printf("temp:  %d\r\n",(int)temp);
//			printf(" \r\n");
			
			OLED_ShowFloat(50, 0,pitch,1,16,1);
			OLED_ShowFloat(50,15,roll,5,16,1);
			OLED_ShowFloat(50,31,yaw,5,16,1);
			OLED_ShowFloat(50,47,(float)temp/100,5,16,1);
			OLED_Refresh();	

//			Send_Angle();

		}
	} 	
}
