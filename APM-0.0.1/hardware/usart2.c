#include "usart2.h"	


void uart2_init(u32 bound){
   //GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(MY_USART2_AHBxPeriph_GPIOx,ENABLE); //ʹ��GPIODʱ��
	RCC_APB1PeriphClockCmd(MY_USART2_APBxPeriph_USARTx,ENABLE);//ʹ��USART2ʱ��
 
	//����1��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(MY_USART2_GPIOx,MY_USART2_PinSource1,MY_USART2_AF_USARTx); //GPIOD5����ΪUSART2
	GPIO_PinAFConfig(MY_USART2_GPIOx,MY_USART2_PinSource2,MY_USART2_AF_USARTx); //GPIOD6����ΪUSART2
	
	//USART2�˿�����
	GPIO_InitStructure.GPIO_Pin = MY_USART2_TX_Pin | MY_USART2_RX_Pin; //GPIOD5��GPIOD6
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(MY_USART2_GPIOx,&GPIO_InitStructure); //��ʼ��PD5��PD6

   //USART2 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;						//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;		//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;			//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;				//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	USART_Init(MY_USART2_USARTx, &USART_InitStructure);				 //��ʼ������
	
	USART_Cmd(MY_USART2_USARTx, ENABLE);  //ʹ�ܴ��� 
	
#ifdef MY_USART2_EN_RX	
	USART_ITConfig(MY_USART2_USARTx, USART_IT_RXNE, ENABLE);//��������ж�

	//Usart2 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = MY_USART2_IRQn;	//����2�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;	//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);							//����ָ���Ĳ�����ʼ��VIC�Ĵ�����

#endif
	
}

#ifdef	MY_USART2_EN_RX	
	//bit15��	������ɱ�־
	//bit14��	���յ�0x0d
	//bit13~0��	���յ�����Ч�ֽ���Ŀ
	u16 MY_USART2_RX_STA=0;      			 //����״̬���	
	u8 	MY_USART2_RX_BUF[MY_USART2_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
#endif

#if MY_USART2==3
	void USART3_IRQHandler(void)                	//����2�жϷ������
	{
		u8 Res;
		if(USART_GetITStatus(MY_USART2_USARTx, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
			Res =USART_ReceiveData(MY_USART2_USARTx);//(USART1->DR);	//��ȡ���յ�������
			
			if((MY_USART2_RX_STA&0x8000)==0)//����δ���
			{
				if(MY_USART2_RX_STA&0x4000)//���յ���0x0d
				{
					if(Res!=0x0a)MY_USART2_RX_STA=0;//���մ���,���¿�ʼ
					else MY_USART2_RX_STA|=0x8000;	//��������� 
				}
				else //��û�յ�0X0D
				{	
					if(Res==0x0d)MY_USART2_RX_STA|=0x4000;
					else
					{
						MY_USART2_RX_BUF[MY_USART2_RX_STA&0X3FFF]=Res ;
						MY_USART2_RX_STA++;
						if((MY_USART2_RX_STA&0X3FFF)>(MY_USART2_REC_LEN-1))MY_USART2_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
					}		 
				}
			}   		 
		}
	}
#endif	





