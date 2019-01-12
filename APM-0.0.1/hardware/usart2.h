#ifndef	__USART2_H
#define	__USART2_H

#include "stm32f4xx.h" 

#define MY_USART2_REC_LEN  			20  	//�����������ֽ��� 200
/*****************MY_USART1*****************************/
#define	MY_USART2							3
#define MY_USART2_EN_RX   												//�Ƿ��������ж� ����������ע�͵�����
#define MY_USART2_USARTx					USART3						//���� ��
#define	MY_USART2_AHBxPeriph_GPIOx			RCC_AHB1Periph_GPIOD		//���� ��ӦGPIOʱ��
#define	MY_USART2_APBxPeriph_USARTx			RCC_APB1Periph_USART3		//���� ʱ��
#define	MY_USART2_PinSource1				GPIO_PinSource8				//���� ��������1
#define	MY_USART2_PinSource2				GPIO_PinSource9				//���� ��������2
#define	MY_USART2_AF_USARTx					GPIO_AF_USART3				//���� ���ù���
#define	MY_USART2_GPIOx						GPIOD						//���� GPIO
#define	MY_USART2_TX_Pin					GPIO_Pin_8					//���� TX��
#define	MY_USART2_RX_Pin					GPIO_Pin_9					//���� RX��

#define MY_USART2_IRQn						USART3_IRQn					//���� �ж�������

/****************************************************/

void uart2_init(u32 bound);


#endif
