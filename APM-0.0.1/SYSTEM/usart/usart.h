#ifndef __USART_H
#define __USART_H
#include "stdio.h"

//֧����Ӧ��ͬƵ���µĴ��ڲ���������.
//�����˶�printf��֧��
//�����˴��ڽ��������.
//������printf��һ���ַ���ʧ��bug


#define receEnable() PAout(7)=0
#define sendEnable() PAout(7)=1

#define receEnable2() PAout(5)=0
#define sendEnable2() PAout(5)=1

void uart1_init(u32 bound);
void uart2_init(u32 bound);
void beginSend(void);
void beginSend2(void);

#endif
