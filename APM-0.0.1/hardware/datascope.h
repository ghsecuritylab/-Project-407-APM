#ifndef	__DATASCOPE_H
#define __DATASCOPE_H

#include "stm32f4xx.h" 

/***********��Ӧ���迪��***************/
#define	DATASCOPE					//��λ��

/**************************************/

extern	u8 DataScope_Delay_Flag;
extern	u8 DataScope_Flag_50ms;

void DataScope(void);

#endif
