/**************************************************************************************************
Title: 				USART source program based on STM32F10 c
Current 			version: v1.0
Function:			
processor: 	                
Clock:				8-72M  Hz
Author:			
Company:			
Contact:			
E-MAIL:				
Data:				  
***************************************************************************************************/


/**************************************************************************************************
========================================Include Head===============================================
***************************************************************************************************/
#include "Usart.h"
//#include <stdio.h>
/**************************************************************************************************
========================================Program Start===============================================
***************************************************************************************************/
#define  FLAG_TC         ((u16 )0x0040)
/**************************************************************************************************
========================================USART START===============================================
***************************************************************************************************/
  UartData  Uart_Data;


/****************************************************************************
* ���ƣ�USART1_Printf()
* ���ܣ��򴮿ڷ���һ�ַ��� �÷�ͬPrintf()����
* ��ڲ�����format Ҫ���͵��ַ�����ָ�� ... Ϊ����
* ���ڲ��������͵��ַ������ַ�����
****************************************************************************/
//int USART1_Printf(const char *format, ...)
//{
//va_list v_list;
//char *ptr;
//int i= 0;
//
//
//va_start(v_list, format);     // Initialize variable arguments. 
//vsprintf(tbuf1, format, v_list ); 
//va_end(v_list);
//
//
//ptr= tbuf1;
//while( (*ptr) && i<MAX_TBUF1) {
//  USART1_SendData(*ptr);
//  ptr++; i++;
//}//while
//
//return i;
//}


int fputc(int ch, FILE *f)
{
USART_SendData(USART2, (unsigned char) ch);// USART1 ???? USART2 ?
while (!(USART2->SR & USART_FLAG_TXE));
return (ch);
}

int GetKey (void) {
while (!(USART2->SR & USART_FLAG_RXNE));
return ((int)(USART2->DR & 0x1FF));
}




/**************************************************************************************************
Function:   uartx_send_Byte
Description:���ֽڴ��ڷ�������
Input:      no
Output:     no
Return:     no
**************************************************************************************************/
void Uart1_Send_Byte(u8 Byte)     //����1����
{
	USART1->SR &= (~FLAG_TC);
	USART1->DR =Byte;
	while((USART1->SR&FLAG_TC)==0); //�ȴ�һ��������һ������
}

void Uart2_Send_Byte(u8 Byte) //����2����
{
	
	USART2->SR &= (~FLAG_TC);
	USART2->DR =Byte;
	while((USART2->SR&FLAG_TC)==0); //�ȴ�һ��������һ������
}

void Uart3_Send_Byte(u8 Byte) //����3����
{
	USART3->SR &= (~FLAG_TC);
	USART3->DR =Byte;
	while((USART3->SR&FLAG_TC)==0); //�ȴ�һ��������һ������
}


void Uart4_Send_Byte(u8 Byte) //����4����
{
	UART4->SR &= (~FLAG_TC);
	UART4->DR =Byte;
	while((UART4->SR&FLAG_TC)==0); //�ȴ�һ��������һ������
}

void Uart5_Send_Byte(u8 Byte) //����5����
{
	UART5->SR &= (~FLAG_TC);
	UART5->DR =Byte;
	while((UART5->SR&FLAG_TC)==0); //�ȴ�һ��������һ������
}

/**************************************************************************************************
Function:   uartx_send
Description:���ֽڴ��ڷ�������
Input:      no
Output:     no
Return:     no
**************************************************************************************************/
void Uart1_Send(uint8_t *Data, uint8_t Len)     //����1����
{
     uint8_t i;
	   for(i=0;i<Len;i++)
	   {
			  Uart1_Send_Byte(*Data++);
		 }
}

void Uart2_Send(uint8_t *Data, uint8_t Len)     //����2����
{
     uint8_t i;
	   for(i=0;i<Len;i++)
	   {
			  Uart2_Send_Byte(*Data++);
		 }
}

void Uart3_Send(uint8_t *Data, uint8_t Len)     //����3����
{
     uint8_t i;
	   for(i=0;i<Len;i++)
	   {
			  Uart3_Send_Byte(*Data++);
		 }
}

void Uart4_Send(uint8_t *Data, uint8_t Len)     //����4����
{
     uint8_t i;
	   for(i=0;i<Len;i++)
	   {
			  Uart4_Send_Byte(*Data++);
		 }
}

void Uart5_Send(uint8_t *Data, uint8_t Len)     //����5����
{
     uint8_t i;
	   for(i=0;i<Len;i++)
	   {
			  Uart5_Send_Byte(*Data++);
		 }
}
/**************************************************************************************************
Function:   uartx_send
Description:�ַ�������
Input:      no
Output:     no
Return:     no
**************************************************************************************************/
void UART1_String_Send(char *SendData)//�ַ������ͺ���
{
	   u8 i=0;
	   while(1)
	   {
			 if(SendData[i]!=0)
				{
					USART_SendData(USART1,SendData[i]);  //����һ���ֽ�
					while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET){};//�ȴ����ͽ���
					i++;
				}
			 else 
			 return ;
		}
}

void UART2_String_Send(char *SendData)//�ַ������ͺ���
{
	   u8 i=0;
	   while(1)
	   {
			 if(SendData[i]!=0)
				{
					USART_SendData(USART2,SendData[i]);  //����һ���ֽ�
					while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET){};//�ȴ����ͽ���
					i++;
				}
			 else 
			 return ;
		}
}

void UART3_String_Send(char *SendData)//�ַ������ͺ���
{
	   u8 i=0;
	   while(1)
	   {
			 if(SendData[i]!=0)
				{
					USART_SendData(USART3,SendData[i]);  //����һ���ֽ�
					while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==RESET){};//�ȴ����ͽ���
					i++;
				}
			 else 
			 return ;
		}
}



void UART4_String_Send(char *SendData)//�ַ������ͺ���
{
	   u8 i=0;
	   while(1)
	   {
			 if(SendData[i]!=0)
				{
					USART_SendData(UART4,SendData[i]);  //����һ���ֽ�
					while(USART_GetFlagStatus(UART4,USART_FLAG_TXE)==RESET){};//�ȴ����ͽ���
					i++;
				}
			 else 
			 return ;
		}
}

void UART5_String_Send(char *SendData)//�ַ������ͺ���
{
	   u8 i=0;
	   while(1)
	   {
			 if(SendData[i]!=0)
				{
					USART_SendData(UART5,SendData[i]);  //����һ���ֽ�
					while(USART_GetFlagStatus(UART5,USART_FLAG_TXE)==RESET){};//�ȴ����ͽ���
					i++;
				}
			 else 
			 return ;
		}
}
/**************************************************************************************************
Function:   Printf
Description:ͨ������2�ַ�������
Input:      no
Output:     no
Return:     no
**************************************************************************************************/
void Printf(char *SendData)//�ַ������ͺ���
{
	   u8 i=0;
	   while(1)
	   {
			 if(SendData[i]!=0)
				{
					USART_SendData(USART2,SendData[i]);  //����һ���ֽ�
					while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET){};//�ȴ����ͽ���
					i++;
				}
			 else 
			 return ;
		}
}

/**************************************************************************************************
Function:   USARTx_IRQHandler
Description:4�����жϽ�������
Input:      no
Output:     no
Return:     no
**************************************************************************************************/
//void USART1_IRQHandler(void)  //�жϽ��պ���
//{
//if((USART1->SR)&0x0020) //�Ƿ�����ж� (���ռĴ����ǿ�)     
//{
//
//  //д��ִ�ж���
// }
//
//USART1->SR = 0xFFDF;
//
//}


void USART1_IRQHandler(void)// ����1�����ж�
{
    //UartData  Uart_Data;
	
	  if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET) 
		{  
			USART_ClearITPendingBit(USART1,USART_IT_RXNE);//
			Uart_Data.Buff[0][Uart_Data.Ind[0]] = (USART1->DR&0x1ff);//���ݴ洢
			Uart_Data.Time[0]=0;
			Uart_Data.Ind[0]++;
		}
		USART_ClearFlag(USART1,USART_FLAG_TC);//����жϱ�־
}

void USART2_IRQHandler(void)// ����2�����ж�
{
	  //UartData  Uart_Data;
	  if(USART_GetITStatus(USART2,USART_IT_RXNE)==SET) 
		{  
			USART_ClearITPendingBit(USART2,USART_IT_RXNE);//
      Uart_Data.Buff[1][Uart_Data.Ind[1]] = (USART2->DR&0x1ff);//���ݴ洢
			Uart_Data.Time[1]=0;
			Uart_Data.Ind[1]++;
			
						
		}
		USART_ClearFlag(USART2,USART_FLAG_TC);//����жϱ�־ 
}
//�ſڻ����ݽ���
void USART3_IRQHandler(void)	       // ����3�����ж�
{
	  //UartData  Uart_Data; 
	  if(USART_GetITStatus(USART3,USART_IT_RXNE)==SET) 
		{  
			USART_ClearITPendingBit(USART3,USART_IT_RXNE);//
      Uart_Data.Buff[2][Uart_Data.Ind[2]] = (USART3->DR&0x1ff);//���ݴ洢			
			Uart_Data.Time[2]=0;
			Uart_Data.Ind[2]++;
	 	  
		}
		USART_ClearFlag(USART3,USART_FLAG_TC);//����жϱ�־ 
}


 void UART4_IRQHandler(void)                	//����4�жϷ������
 	{
 	//u8 Res;

 	  if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
 		{
			USART_ClearITPendingBit(UART4,USART_IT_RXNE);//
 		//Res =USART_ReceiveData(UART4);//(USART1->DR);	//��ȡ���յ�������
			Uart_Data.Buff[3][Uart_Data.Ind[3]] = (UART4->DR&0x1ff);//���ݴ洢
			Uart_Data.Time[3]=0;
			Uart_Data.Ind[3]++;
 			 
    } 
    USART_ClearFlag(UART4,USART_FLAG_TC);//����жϱ�־ 
  } 


void UART5_IRQHandler(void)                	//����5�жϷ������
	{
	//u8 Res;

	   if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
			USART_ClearITPendingBit(UART5,USART_IT_RXNE);//
		//Res =USART_ReceiveData(UART5);//(USART1->DR);	//��ȡ���յ�������
			Uart_Data.Buff[4][Uart_Data.Ind[4]] = (UART5->DR&0x1ff);//���ݴ洢
			Uart_Data.Time[4]=0;
			Uart_Data.Ind[4]++;
			
		
			 
  		 
    } 
		USART_ClearFlag(UART4,USART_FLAG_TC);//����жϱ�־ 

}
/**************************************************************************************************
========================================USART =====================================================
***************************************************************************************************/


/**************************************************************************************************
Function:   UART1_Init(u32 bound)
Description:��ʼ������1
Input:      ������ bound
Output:     no
Return:     no
**************************************************************************************************/
//��ʼ��IO ����1 

 void UART1_Init(u32 bound)
 {
     //GPIO�˿�����
     GPIO_InitTypeDef GPIO_InitStructure;
 	  USART_InitTypeDef USART_InitStructure;
 	  NVIC_InitTypeDef NVIC_InitStructure;
 	 
 	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
  	USART_DeInit(USART1);  //��λ����1
 	 //USART1_TX   PA.9
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
     GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ��PA9
    
     //USART1_RX	  PA.10
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
     GPIO_Init(GPIOA, &GPIO_InitStructure);  //��ʼ��PA10


    //USART ��ʼ������

 	  USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
 	  USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
 	  USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
 	  USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
 	  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
 	  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

     USART_Init(USART1, &USART_InitStructure); //��ʼ������
 #if EN_USART1_RX		  //���ʹ���˽���  
    //Usart1 NVIC ����
     NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
 	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
 	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
 	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
 	  NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
    
     USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�����ж�
 #endif
     USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ��� 

 }
 
/**************************************************************************************************
Function:   UART2_Init(u32 bound)
Description:��ʼ������2
Input:      ������ bound
Output:     no
Return:     no
**************************************************************************************************/
 
void UART2_Init(u32 bound)
{
     //GPIO�˿�����
     GPIO_InitTypeDef GPIO_InitStructure;
 	USART_InitTypeDef USART_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
 	 
 	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);	//ʹ��USART2ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	//ʹ��GPIOAʱ��
  	USART_DeInit(USART2);  //��λ����2
 	 //USART2_TX   PA.2
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.2
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
     GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ��PA2
    
     //USART2_RX	  PA.3
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
     GPIO_Init(GPIOA, &GPIO_InitStructure);  //��ʼ��PA3


    //USART ��ʼ������

 	USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
 	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
 	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
 	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
 	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
 	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

     USART_Init(USART2, &USART_InitStructure); //��ʼ������
 #if EN_USART1_RX		  //���ʹ���˽���  
    //Usart1 NVIC ����
     NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
 	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
 	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
 	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
 	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
    
     USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�����ж�
 #endif
     USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ��� 

 }
 
 
 /**************************************************************************************************
Function:   UART3_Init(u32 bound)
Description:��ʼ������3
Input:      ������ bound
Output:     no
Return:     no
**************************************************************************************************/
void UART3_Init(u32 bound)
{
//     //GPIO�˿�����
//   GPIO_InitTypeDef GPIO_InitStructure;
// 	 USART_InitTypeDef USART_InitStructure;
// 	 NVIC_InitTypeDef NVIC_InitStructure;
// 	 
// 	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	//ʹ��USART3ʱ��
// 	 //����ӳ��
// 	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);   
// 	
// 	 //������ӳ��
////  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);    
////  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	//ʹ��USART3ʱ��
////  	GPIO_PinRemapConfig(GPIO_PartialRemap_USART3,ENABLE);
// 	
// 	 //��ȫ��ӳ��
//// 	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);    
//// 	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	//ʹ��USART3ʱ��
//// 	 GPIO_PinRemapConfig(GPIO_FullRemap_USART3,ENABLE);
// 	
//  	USART_DeInit(USART3);  //��λ����3
// 	
// 	/*USART3û����ӳ��  */
// 	 //USART3_TX   PB.10
//     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PB.10
//     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
//     GPIO_Init(GPIOB, &GPIO_InitStructure); //��ʼ��PB10
//     
//     //USART3_RX	  PB.11
//     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
//     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
//     GPIO_Init(GPIOB, &GPIO_InitStructure);  //��ʼ��PB11

// 	
// 	/*������ӳ��*/
// // 	 //USART3_TX   PC.10
// //     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PB.10
// //     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// //     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
// //     GPIO_Init(GPIOC, &GPIO_InitStructure); //��ʼ��PC10
// //    
// //     //USART3_RX	  PC.11
// //     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
// //     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
// //     GPIO_Init(GPIOC, &GPIO_InitStructure);  //��ʼ��PC11
// 	
// 	/*��ȫ��ӳ��*/
// 	  //USART3_TX   PD.8
////       GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //PD.8
// //      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
////       GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
////       GPIO_Init(GPIOD, &GPIO_InitStructure); //��ʼ��PD8
//    
//     //USART3_RX	  PD.9
// //      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
////       GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
// //      GPIO_Init(GPIOD, &GPIO_InitStructure);  //��ʼ��PD9

//    //USART ��ʼ������

// 	USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
// 	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
// 	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
// 	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
// 	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
// 	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

//  USART_Init(USART3, &USART_InitStructure); //��ʼ������
// #if EN_USART1_RX		  //���ʹ���˽���  
//    //Usart1 NVIC ����
//  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
// 	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
// 	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
// 	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
// 	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
//    
//  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�����ж�
// #endif
//     USART_Cmd(USART3, ENABLE);                    //ʹ�ܴ��� 

 }
/**************************************************************************************************
Function:   UART4_Init(u32 bound)
Description:��ʼ������4
Input:      ������ bound
Output:     no
Return:     no
**************************************************************************************************/
 void UART4_Init(u32 bound)
 {
//     //GPIO�˿�����
//     GPIO_InitTypeDef GPIO_InitStructure;
// 	  USART_InitTypeDef USART_InitStructure;
// 	  NVIC_InitTypeDef NVIC_InitStructure;
// 	 
// 	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	//ʹ��GPIOCʱ��
// 	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);
//  	USART_DeInit(UART4);  //��λ����4
// 	 //USART4_TX   PC.10
//     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PC.10
//     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
//     GPIO_Init(GPIOC, &GPIO_InitStructure); //��ʼ��PC10
//    
//     //USART4_RX	  PC.11
//     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
//     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
//     GPIO_Init(GPIOC, &GPIO_InitStructure);  //��ʼ��PC11


//    //USART ��ʼ������

//		USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
//		USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
//		USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
//		USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
//		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
//		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

//     USART_Init(UART4, &USART_InitStructure); //��ʼ������
// #if EN_USART1_RX		  //���ʹ���˽���  
//    //Usart4 NVIC ����
//    NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
//		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
//		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
//		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
//		NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
//    
//    USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//�����ж�
// #endif
//    USART_Cmd(UART4, ENABLE);                    //ʹ�ܴ��� 

 }

/**************************************************************************************************
Function:   UART5_Init(u32 bound)
Description:��ʼ������5
Input:      ������ bound
Output:     no
Return:     no
**************************************************************************************************/
void UART5_Init(u32 bound)
{
//    //GPIO�˿�����
//    GPIO_InitTypeDef GPIO_InitStructure;
//	USART_InitTypeDef USART_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
//	 
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);	//ʹ��GPIOAʱ��
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOC, ENABLE);
// 	USART_DeInit(UART5);  //��λ����1
//	 //USART1_TX   PC12
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; //PC.12
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
//    GPIO_Init(GPIOC, &GPIO_InitStructure); //��ʼ��PD8
//   
//    //USART1_RX	  PD.2
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
//    GPIO_Init(GPIOD, &GPIO_InitStructure);  //��ʼ��PD9


//   //USART ��ʼ������

//	USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
//	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
//	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
//	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
//	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
//	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

//    USART_Init(UART5, &USART_InitStructure); //��ʼ������
//#if EN_USART1_RX		  //���ʹ���˽���  
//   //Usart1 NVIC ����
//    NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
//	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
//   
//    USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);//�����ж�
//#endif
//    USART_Cmd(UART5, ENABLE);                    //ʹ�ܴ��� 

}



/**************************************************************************************************
========================================USART END===============================================
***************************************************************************************************/


/******************* (C)***Program End************�ļ�����*****************************************/

