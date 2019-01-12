#ifndef __PID_H
#define __PID_H
#include "stm32f4xx.h"

extern float ResultValue;
extern float ResultValueBack;
extern float ResultValueBackOne;
extern float ResultValueBackTwo;
extern float GiveValueBack;
extern float ResultValuess;
extern float PIDErrADD;
extern float ErrBack;
extern float SeqIntPIDErrADD;
extern float SeqIntErrBack;
extern float OverIntPIDErrADD;
extern float OverIntResultBack;
extern float OverIntErrBack;

extern float SeqIntPIDErrADD1;
extern float SeqIntErrBack1;



float PID(float Kp, float Ki, float Kd, float GiveValue, float ActualValue);
float SeqIntPID(float Kp, float Ki, float Kd, u16 GiveValue, u16 ActualValue);//���ַ���
float OverIntPID(float Kp, float Ki, float Kd, float GiveValue, float ActualValue);//�����ͻ���

float SeqIntPID1(float Kp, float Ki, float Kd, float GiveValue, float ActualValue);//���ַ���




#endif  //__PID_H
