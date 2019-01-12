/**********************************************************************************************************
*
*	ģ������ : ������ʾ
*	�ļ����� : test.c
*	��    �� : V1.0
*	˵    �� :
*	�޸ļ�¼ :
*		�汾��  ����        ����                        ˵��
*
*		v1.0    2013-4-20   jiezhi320(UP MCU ������)    ��ʾ�ź�����ʵ��ʹ��
*
*	Copyright (C), 2012-2013,
*   �Ա��꣺   http://shop73275611.taobao.com
*   QQ����Ⱥ�� 258043068
*
**********************************************************************************************************/
#include <rtthread.h>
#include <stm32f4xx.h>
#include "test.h"
//#include "key.h"
//#include "led.h"




void timeout_callbak(void* parameter);

/*  ��������4�ֽڶ��� */
ALIGN(RT_ALIGN_SIZE)

/*  ��̬�̵߳� �̶߳�ջ*/
static rt_uint8_t key_stack[512];
/* ��̬�̵߳� �߳̿��ƿ� */

static struct rt_thread key_thread;

/* ��ʱ���Ŀ��ƿ� */
static rt_timer_t timer_test;
static rt_tick_t timeout_value=10;

rt_err_t demo_start(void)
{
    rt_err_t result;

    rt_hw_led_init();
	  
    /* ����key�߳� �� ���ȼ� 15 ��ʱ��Ƭ 5��ϵͳ�δ� */
    result = rt_thread_init(&key_thread,
                            "key",
                            key_thread_entry, RT_NULL,
                            (rt_uint8_t*)&key_stack[0], sizeof(key_stack), 15, 5);

    if (result == RT_EOK)
    {
        rt_thread_startup(&key_thread);
    }
    /*������̬��ʱ��*/
    timer_test = rt_timer_create("timer1",  /* ��ʱ�������� timer1 */
                                 timeout_callbak,  									/* ��ʱʱ�ص��Ĵ����� */
                                 RT_NULL,			 											/* ��ʱ��������ڲ��� */
                                 timeout_value, 											/* ��ʱ���ȣ���OS TickΪ��λ����timeout_value��OS Tick */
                                 RT_TIMER_FLAG_PERIODIC); 						/* �����Զ�ʱ�� */

    /* ������ʱ�� */
    if (timer_test != RT_NULL)
        rt_timer_start(timer_test);

    rt_kprintf("timer started !\n");
    return 0;
}

rt_uint8_t flag;
rt_uint32_t count=0;


/* ��ʱʱ�ص��Ĵ����� */
void timeout_callbak(void* parameter)
{
    flag^=1;
		count++;

    if (flag)
        rt_hw_led_off(0);
    else
        rt_hw_led_on(0);
    rt_kprintf("timer time out %d !\n",count);
		
}



/* ���ƶ�ʱ�� */
void timer_conrol(void)
{
    timeout_value+=10;
    /* ���Ķ�ʱ����ʱʱ��*/
    rt_timer_control(timer_test, RT_TIMER_CTRL_SET_TIME, (void *)&timeout_value);
    rt_kprintf("timer timeout time set to %d !\n", timeout_value);                    
    if (timeout_value==500)
    {
        rt_timer_stop(timer_test); /* ֹͣ��ʱ�� */
        rt_kprintf("timer stoped !\n");
    }

    if (timeout_value>=510)
    {
        /* �ٴ�������ʱ�� */
        rt_timer_start(timer_test);
        timeout_value=10;
        rt_timer_control(timer_test, RT_TIMER_CTRL_SET_TIME, (void *)&timeout_value);
    }

}


