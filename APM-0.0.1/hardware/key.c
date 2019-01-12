/**********************************************************************************************************
*
*	ģ������ : �������ģ��
*	�ļ����� : key.c
*	��    �� : V1.0
*	˵    �� :
*	�޸ļ�¼ :
*		�汾��  ����        ����           ˵��
*
*		v1.0    2013-4-20   jiezhi320(UP MCU ������)
*
*	Copyright (C), 2012-2013,
*   �Ա��꣺   http://shop73275611.taobao.com
*   QQ����Ⱥ�� 258043068
*
**********************************************************************************************************/
#include <rtthread.h>
#include "stm32f4xx.h"
#include "key.h"






u8 key_scan(rt_uint8_t mode);


void key_thread_entry(void* parameter)
{
    rt_hw_key_init();

    while(1)
    {
        if(key_scan(0) == KEY1_PRES)
						//timer_conrol();
				rt_thread_delay(5);
    }
}


void rt_hw_key_init(void)
{

    GPIO_InitTypeDef  GPIO_InitStructure;

		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOE, ENABLE);//ʹ��GPIOA,GPIOEʱ��
 
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4; //KEY2 KEY3��Ӧ����
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
		GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIOE2,3,4
	
	 
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//WK_UP��Ӧ����PA0
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN ;//����
		GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA0
}



//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//0��û���κΰ�������
//1��KEY0����
//2��KEY1����
//3��KEY2���� 
//4��WKUP���� WK_UP
//ע��˺�������Ӧ���ȼ�,KEY0>KEY1>KEY2>WK_UP!!
u8 key_scan(rt_uint8_t mode)
{
    static u8 key_up=1;//�������ɿ���־
		if(mode)key_up=1;  //֧������		  
		if(key_up&&(KEY0==0||KEY1==0||WK_UP==1))
				{
					rt_thread_delay(1);//ȥ���� 
					key_up=0;
					if(KEY0==0)return 1;
					else if(KEY1==0)return 2;
//				else if(KEY2==0)return 3;
					else if(WK_UP==1)return 4;
				}	
		else if(KEY0==1&&KEY1==1&&WK_UP==0)key_up=1; 	    
 	return 0;// �ް�������
}




