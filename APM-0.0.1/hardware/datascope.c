#include "datascope.h"
#include "DataScope_DP.h"
#include "usart1.h"
#include "control.h"

/******************************/
//��Ҫ�õ���ͷ�ļ�
#include "encoder.h"
/******************************/

/*************��λ����ʱ����*****************/
u8 DataScope_Delay_Flag=0;
u8 DataScope_Flag_50ms=0;

/********************************************/

/*******************************/
//�����ļ����ù����ı���
extern short Encoder1_Speed;


/*******************************/



/*�������ݵ���λ��*/
void DataScope(void)
{   
	u8 i;
	u8 DataScope_Send_Count=0; //������Ҫ���͵����ݸ���
	
	DataScope_Get_Channel_Data(Encoder1_Speed, 1);      
	DataScope_Get_Channel_Data(30, 2);                      
	//DataScope_Get_Channel_Data(0, 3);
	//DataScope_Get_Channel_Data(0, 4);
	//DataScope_Get_Channel_Data(0, 5);
	//DataScope_Get_Channel_Data(0, 6);
	
	
	DataScope_Send_Count = DataScope_Data_Generate(2);
	for( i = 0 ; i < DataScope_Send_Count; i++) 
	{
		while((MY_USART1_USARTx->SR&0X40)==0);  
		MY_USART1_USARTx->DR = DataScope_OutPut_Buffer[i]; 
	}
	DataScope_Delay_Flag=1;	          //===50ms�жϾ�׼��ʱ��־λ  	
	while(DataScope_Delay_Flag);        //===50ms�жϾ�׼��ʱ  ��Ҫ�ǲ�����ʾ��λ����Ҫ�ϸ��50ms��������  

}
