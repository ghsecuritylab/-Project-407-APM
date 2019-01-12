#include "sample_time.h"

void Sample_Time_Init()
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStructure ;
	NVIC_InitTypeDef     NVIC_InitStructure ;
	
	/*��ʱ��Դ*/
	RCC_APB1PeriphClockCmd(SAMPLE_TIME_APBxPeriph_TIMx,ENABLE);
	
	/*�ṹ������*/
	TIM_TimeBaseInitStructure.TIM_Period = 4;
	TIM_TimeBaseInitStructure.TIM_Prescaler = 8399;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(SAMPLE_TIME_TIMx,&TIM_TimeBaseInitStructure);
	
	/*������ʱ���ж�*/
	TIM_ITConfig(SAMPLE_TIME_TIMx,TIM_IT_Update,ENABLE);
	
	/*���ö�ʱ���ж�*/
	NVIC_InitStructure.NVIC_IRQChannel = SAMPLE_TIME_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStructure);
	
	/*ʹ�ܶ�ʱ��x*/
	TIM_Cmd(SAMPLE_TIME_TIMx,ENABLE);
}
