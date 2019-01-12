#ifndef	__USART1_H
#define	__USART1_H

#include "stm32f4xx.h" 

#define MY_USART1_REC_LEN  			1024  	//�����������ֽ��� 200
/*****************MY_USART1*****************************/
#define	MY_USART1							2
#define MY_USART1_EN_RX   													//�Ƿ��������ж� ����������ע�͵�����
#define MY_USART1_USARTx					USART2						//���� ��
#define	MY_USART1_AHBxPeriph_GPIOx			RCC_AHB1Periph_GPIOD		//���� ��ӦGPIOʱ��
#define	MY_USART1_APBxPeriph_USARTx			RCC_APB1Periph_USART2		//���� ʱ��
#define	MY_USART1_PinSource1				GPIO_PinSource5				//���� ��������1
#define	MY_USART1_PinSource2				GPIO_PinSource6				//���� ��������2
#define	MY_USART1_AF_USARTx					GPIO_AF_USART2				//���� ���ù���
#define	MY_USART1_GPIOx						GPIOD						//���� GPIO
#define	MY_USART1_TX_Pin					GPIO_Pin_5					//���� TX��
#define	MY_USART1_RX_Pin					GPIO_Pin_6					//���� RX��

#define MY_USART1_IRQn						USART2_IRQn					//���� �ж�������

/****************************************************/

extern	u8 	MY_USART1_RX_BUF[MY_USART1_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.


void uart1_init(u32 bound);


#endif
