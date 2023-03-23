#include "uart.h"
#include "stdio.h"
/*  ��λ��������    */

uint8_t Serial_Rxdata;

void USART1_Init(void)
{
	//USART1_TX:PA 9   
	//USART1_RX:PA10
	GPIO_InitTypeDef GPIO_InitStructure;     //���ڶ˿����ýṹ�����
	USART_InitTypeDef USART_InitStructure;   //���ڲ������ýṹ�����
	NVIC_InitTypeDef NVIC_InitStructure;     //�����ж����ýṹ�����

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);   //��PA�˿�ʱ��

    //USART1_TX   PA9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;          		 //PA9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  		 //�趨IO�ڵ�����ٶ�Ϊ50MHz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	   		 //�����������
    GPIO_Init(GPIOA, &GPIO_InitStructure);             	 	 //��ʼ��PA9
    //USART1_RX	  PA10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;             //PA10
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  //��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);                 //��ʼ��PA10 

    //USART ��ʼ������
	USART_InitStructure.USART_BaudRate = 115200;                  //���ڲ�����Ϊ115200
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;   //�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;        //һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;           //����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   //��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	                  //�շ�ģʽ
    USART_Init(USART1, &USART_InitStructure);                     //��ʼ������1
	
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //ʹ���ж�

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
	
	//USART1 NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;  //��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		    //�����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			      //IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	                          //����ָ���Ĳ�����ʼ��VIC�Ĵ���


    USART_Cmd(USART1, ENABLE);                     //ʹ�ܴ���1

  	//�����������1���ֽ��޷���ȷ���ͳ�ȥ������
	USART_ClearFlag(USART1, USART_FLAG_TC);        //�崮��1���ͱ�־
		
}

void USART1_IRQHandler(void)			 
{
	if( USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)  	   //�����ж�  
	{
		Serial_Rxdata = USART_ReceiveData(USART1);
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);   //����жϱ�־
	}
	switch(Serial_Rxdata)
	{
		case 0x11:
			GPIO_ResetBits(GPIOA,GPIO_Pin_4);
			break;
		case 0x10:
			GPIO_SetBits(GPIOA,GPIO_Pin_4);
			break;
		case 0x21:
			GPIO_ResetBits(GPIOA,GPIO_Pin_5);
			break;
		case 0x20:
			GPIO_SetBits(GPIOA,GPIO_Pin_5);
			break;
		case 0x31:
			GPIO_ResetBits(GPIOA,GPIO_Pin_6);
			break;
		case 0x30:
			GPIO_SetBits(GPIOA,GPIO_Pin_6);
			break;
		case 0x41:
			GPIO_ResetBits(GPIOA,GPIO_Pin_7);
			break;
		case 0x40:
			GPIO_SetBits(GPIOA,GPIO_Pin_7);
			break;
		default:
			break;	
	}
}
