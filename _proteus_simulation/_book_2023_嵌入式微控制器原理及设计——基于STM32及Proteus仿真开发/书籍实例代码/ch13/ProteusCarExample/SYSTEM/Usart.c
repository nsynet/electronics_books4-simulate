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
* 名称：USART1_Printf()
* 功能：向串口发送一字符串 用法同Printf()函数
* 入口参数：format 要发送的字符串的指针 ... 为参数
* 出口参数：发送的字符串的字符个数
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
Description:单字节串口发送数据
Input:      no
Output:     no
Return:     no
**************************************************************************************************/
void Uart1_Send_Byte(u8 Byte)     //串口1发送
{
	USART1->SR &= (~FLAG_TC);
	USART1->DR =Byte;
	while((USART1->SR&FLAG_TC)==0); //等待一个发送完一个数据
}

void Uart2_Send_Byte(u8 Byte) //串口2发送
{
	
	USART2->SR &= (~FLAG_TC);
	USART2->DR =Byte;
	while((USART2->SR&FLAG_TC)==0); //等待一个发送完一个数据
}

void Uart3_Send_Byte(u8 Byte) //串口3发送
{
	USART3->SR &= (~FLAG_TC);
	USART3->DR =Byte;
	while((USART3->SR&FLAG_TC)==0); //等待一个发送完一个数据
}


void Uart4_Send_Byte(u8 Byte) //串口4发送
{
	UART4->SR &= (~FLAG_TC);
	UART4->DR =Byte;
	while((UART4->SR&FLAG_TC)==0); //等待一个发送完一个数据
}

void Uart5_Send_Byte(u8 Byte) //串口5发送
{
	UART5->SR &= (~FLAG_TC);
	UART5->DR =Byte;
	while((UART5->SR&FLAG_TC)==0); //等待一个发送完一个数据
}

/**************************************************************************************************
Function:   uartx_send
Description:多字节串口发送数据
Input:      no
Output:     no
Return:     no
**************************************************************************************************/
void Uart1_Send(uint8_t *Data, uint8_t Len)     //串口1发送
{
     uint8_t i;
	   for(i=0;i<Len;i++)
	   {
			  Uart1_Send_Byte(*Data++);
		 }
}

void Uart2_Send(uint8_t *Data, uint8_t Len)     //串口2发送
{
     uint8_t i;
	   for(i=0;i<Len;i++)
	   {
			  Uart2_Send_Byte(*Data++);
		 }
}

void Uart3_Send(uint8_t *Data, uint8_t Len)     //串口3发送
{
     uint8_t i;
	   for(i=0;i<Len;i++)
	   {
			  Uart3_Send_Byte(*Data++);
		 }
}

void Uart4_Send(uint8_t *Data, uint8_t Len)     //串口4发送
{
     uint8_t i;
	   for(i=0;i<Len;i++)
	   {
			  Uart4_Send_Byte(*Data++);
		 }
}

void Uart5_Send(uint8_t *Data, uint8_t Len)     //串口5发送
{
     uint8_t i;
	   for(i=0;i<Len;i++)
	   {
			  Uart5_Send_Byte(*Data++);
		 }
}
/**************************************************************************************************
Function:   uartx_send
Description:字符串发送
Input:      no
Output:     no
Return:     no
**************************************************************************************************/
void UART1_String_Send(char *SendData)//字符串发送函数
{
	   u8 i=0;
	   while(1)
	   {
			 if(SendData[i]!=0)
				{
					USART_SendData(USART1,SendData[i]);  //发送一个字节
					while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET){};//等待发送结束
					i++;
				}
			 else 
			 return ;
		}
}

void UART2_String_Send(char *SendData)//字符串发送函数
{
	   u8 i=0;
	   while(1)
	   {
			 if(SendData[i]!=0)
				{
					USART_SendData(USART2,SendData[i]);  //发送一个字节
					while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET){};//等待发送结束
					i++;
				}
			 else 
			 return ;
		}
}

void UART3_String_Send(char *SendData)//字符串发送函数
{
	   u8 i=0;
	   while(1)
	   {
			 if(SendData[i]!=0)
				{
					USART_SendData(USART3,SendData[i]);  //发送一个字节
					while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)==RESET){};//等待发送结束
					i++;
				}
			 else 
			 return ;
		}
}



void UART4_String_Send(char *SendData)//字符串发送函数
{
	   u8 i=0;
	   while(1)
	   {
			 if(SendData[i]!=0)
				{
					USART_SendData(UART4,SendData[i]);  //发送一个字节
					while(USART_GetFlagStatus(UART4,USART_FLAG_TXE)==RESET){};//等待发送结束
					i++;
				}
			 else 
			 return ;
		}
}

void UART5_String_Send(char *SendData)//字符串发送函数
{
	   u8 i=0;
	   while(1)
	   {
			 if(SendData[i]!=0)
				{
					USART_SendData(UART5,SendData[i]);  //发送一个字节
					while(USART_GetFlagStatus(UART5,USART_FLAG_TXE)==RESET){};//等待发送结束
					i++;
				}
			 else 
			 return ;
		}
}
/**************************************************************************************************
Function:   Printf
Description:通过串口2字符串发送
Input:      no
Output:     no
Return:     no
**************************************************************************************************/
void Printf(char *SendData)//字符串发送函数
{
	   u8 i=0;
	   while(1)
	   {
			 if(SendData[i]!=0)
				{
					USART_SendData(USART2,SendData[i]);  //发送一个字节
					while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET){};//等待发送结束
					i++;
				}
			 else 
			 return ;
		}
}

/**************************************************************************************************
Function:   USARTx_IRQHandler
Description:4串口中断接收数据
Input:      no
Output:     no
Return:     no
**************************************************************************************************/
//void USART1_IRQHandler(void)  //中断接收函数
//{
//if((USART1->SR)&0x0020) //是否接收中断 (接收寄存器非空)     
//{
//
//  //写入执行动作
// }
//
//USART1->SR = 0xFFDF;
//
//}


void USART1_IRQHandler(void)// 串口1接收中断
{
    //UartData  Uart_Data;
	
	  if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET) 
		{  
			USART_ClearITPendingBit(USART1,USART_IT_RXNE);//
			Uart_Data.Buff[0][Uart_Data.Ind[0]] = (USART1->DR&0x1ff);//数据存储
			Uart_Data.Time[0]=0;
			Uart_Data.Ind[0]++;
		}
		USART_ClearFlag(USART1,USART_FLAG_TC);//清除中断标志
}

void USART2_IRQHandler(void)// 串口2接收中断
{
	  //UartData  Uart_Data;
	  if(USART_GetITStatus(USART2,USART_IT_RXNE)==SET) 
		{  
			USART_ClearITPendingBit(USART2,USART_IT_RXNE);//
      Uart_Data.Buff[1][Uart_Data.Ind[1]] = (USART2->DR&0x1ff);//数据存储
			Uart_Data.Time[1]=0;
			Uart_Data.Ind[1]++;
			
						
		}
		USART_ClearFlag(USART2,USART_FLAG_TC);//清除中断标志 
}
//门口机数据接收
void USART3_IRQHandler(void)	       // 串口3接收中断
{
	  //UartData  Uart_Data; 
	  if(USART_GetITStatus(USART3,USART_IT_RXNE)==SET) 
		{  
			USART_ClearITPendingBit(USART3,USART_IT_RXNE);//
      Uart_Data.Buff[2][Uart_Data.Ind[2]] = (USART3->DR&0x1ff);//数据存储			
			Uart_Data.Time[2]=0;
			Uart_Data.Ind[2]++;
	 	  
		}
		USART_ClearFlag(USART3,USART_FLAG_TC);//清除中断标志 
}


 void UART4_IRQHandler(void)                	//串口4中断服务程序
 	{
 	//u8 Res;

 	  if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
 		{
			USART_ClearITPendingBit(UART4,USART_IT_RXNE);//
 		//Res =USART_ReceiveData(UART4);//(USART1->DR);	//读取接收到的数据
			Uart_Data.Buff[3][Uart_Data.Ind[3]] = (UART4->DR&0x1ff);//数据存储
			Uart_Data.Time[3]=0;
			Uart_Data.Ind[3]++;
 			 
    } 
    USART_ClearFlag(UART4,USART_FLAG_TC);//清除中断标志 
  } 


void UART5_IRQHandler(void)                	//串口5中断服务程序
	{
	//u8 Res;

	   if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
		{
			USART_ClearITPendingBit(UART5,USART_IT_RXNE);//
		//Res =USART_ReceiveData(UART5);//(USART1->DR);	//读取接收到的数据
			Uart_Data.Buff[4][Uart_Data.Ind[4]] = (UART5->DR&0x1ff);//数据存储
			Uart_Data.Time[4]=0;
			Uart_Data.Ind[4]++;
			
		
			 
  		 
    } 
		USART_ClearFlag(UART4,USART_FLAG_TC);//清除中断标志 

}
/**************************************************************************************************
========================================USART =====================================================
***************************************************************************************************/


/**************************************************************************************************
Function:   UART1_Init(u32 bound)
Description:初始化串口1
Input:      波特率 bound
Output:     no
Return:     no
**************************************************************************************************/
//初始化IO 串口1 

 void UART1_Init(u32 bound)
 {
     //GPIO端口设置
     GPIO_InitTypeDef GPIO_InitStructure;
 	  USART_InitTypeDef USART_InitStructure;
 	  NVIC_InitTypeDef NVIC_InitStructure;
 	 
 	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
  	USART_DeInit(USART1);  //复位串口1
 	 //USART1_TX   PA.9
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
     GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化PA9
    
     //USART1_RX	  PA.10
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
     GPIO_Init(GPIOA, &GPIO_InitStructure);  //初始化PA10


    //USART 初始化设置

 	  USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
 	  USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
 	  USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
 	  USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
 	  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
 	  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

     USART_Init(USART1, &USART_InitStructure); //初始化串口
 #if EN_USART1_RX		  //如果使能了接收  
    //Usart1 NVIC 配置
     NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
 	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
 	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
 	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
 	  NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
    
     USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启中断
 #endif
     USART_Cmd(USART1, ENABLE);                    //使能串口 

 }
 
/**************************************************************************************************
Function:   UART2_Init(u32 bound)
Description:初始化串口2
Input:      波特率 bound
Output:     no
Return:     no
**************************************************************************************************/
 
void UART2_Init(u32 bound)
{
     //GPIO端口设置
     GPIO_InitTypeDef GPIO_InitStructure;
 	USART_InitTypeDef USART_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;
 	 
 	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);	//使能USART2时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	//使能GPIOA时钟
  	USART_DeInit(USART2);  //复位串口2
 	 //USART2_TX   PA.2
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.2
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
     GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化PA2
    
     //USART2_RX	  PA.3
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
     GPIO_Init(GPIOA, &GPIO_InitStructure);  //初始化PA3


    //USART 初始化设置

 	USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
 	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
 	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
 	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
 	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
 	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

     USART_Init(USART2, &USART_InitStructure); //初始化串口
 #if EN_USART1_RX		  //如果使能了接收  
    //Usart1 NVIC 配置
     NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
 	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
 	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
 	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
 	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
    
     USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启中断
 #endif
     USART_Cmd(USART2, ENABLE);                    //使能串口 

 }
 
 
 /**************************************************************************************************
Function:   UART3_Init(u32 bound)
Description:初始化串口3
Input:      波特率 bound
Output:     no
Return:     no
**************************************************************************************************/
void UART3_Init(u32 bound)
{
//     //GPIO端口设置
//   GPIO_InitTypeDef GPIO_InitStructure;
// 	 USART_InitTypeDef USART_InitStructure;
// 	 NVIC_InitTypeDef NVIC_InitStructure;
// 	 
// 	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	//使能USART3时钟
// 	 //无重映射
// 	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);   
// 	
// 	 //部分重映射
////  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);    
////  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	//使能USART3时钟
////  	GPIO_PinRemapConfig(GPIO_PartialRemap_USART3,ENABLE);
// 	
// 	 //完全重映射
//// 	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);    
//// 	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	//使能USART3时钟
//// 	 GPIO_PinRemapConfig(GPIO_FullRemap_USART3,ENABLE);
// 	
//  	USART_DeInit(USART3);  //复位串口3
// 	
// 	/*USART3没有重映射  */
// 	 //USART3_TX   PB.10
//     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PB.10
//     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
//     GPIO_Init(GPIOB, &GPIO_InitStructure); //初始化PB10
//     
//     //USART3_RX	  PB.11
//     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
//     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
//     GPIO_Init(GPIOB, &GPIO_InitStructure);  //初始化PB11

// 	
// 	/*部分重映射*/
// // 	 //USART3_TX   PC.10
// //     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PB.10
// //     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// //     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
// //     GPIO_Init(GPIOC, &GPIO_InitStructure); //初始化PC10
// //    
// //     //USART3_RX	  PC.11
// //     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
// //     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
// //     GPIO_Init(GPIOC, &GPIO_InitStructure);  //初始化PC11
// 	
// 	/*完全重映射*/
// 	  //USART3_TX   PD.8
////       GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //PD.8
// //      GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
////       GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
////       GPIO_Init(GPIOD, &GPIO_InitStructure); //初始化PD8
//    
//     //USART3_RX	  PD.9
// //      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
////       GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
// //      GPIO_Init(GPIOD, &GPIO_InitStructure);  //初始化PD9

//    //USART 初始化设置

// 	USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
// 	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
// 	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
// 	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
// 	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
// 	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

//  USART_Init(USART3, &USART_InitStructure); //初始化串口
// #if EN_USART1_RX		  //如果使能了接收  
//    //Usart1 NVIC 配置
//  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
// 	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
// 	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
// 	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
// 	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
//    
//  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启中断
// #endif
//     USART_Cmd(USART3, ENABLE);                    //使能串口 

 }
/**************************************************************************************************
Function:   UART4_Init(u32 bound)
Description:初始化串口4
Input:      波特率 bound
Output:     no
Return:     no
**************************************************************************************************/
 void UART4_Init(u32 bound)
 {
//     //GPIO端口设置
//     GPIO_InitTypeDef GPIO_InitStructure;
// 	  USART_InitTypeDef USART_InitStructure;
// 	  NVIC_InitTypeDef NVIC_InitStructure;
// 	 
// 	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	//使能GPIOC时钟
// 	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);
//  	USART_DeInit(UART4);  //复位串口4
// 	 //USART4_TX   PC.10
//     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PC.10
//     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
//     GPIO_Init(GPIOC, &GPIO_InitStructure); //初始化PC10
//    
//     //USART4_RX	  PC.11
//     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
//     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
//     GPIO_Init(GPIOC, &GPIO_InitStructure);  //初始化PC11


//    //USART 初始化设置

//		USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
//		USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
//		USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
//		USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
//		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
//		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

//     USART_Init(UART4, &USART_InitStructure); //初始化串口
// #if EN_USART1_RX		  //如果使能了接收  
//    //Usart4 NVIC 配置
//    NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
//		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
//		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
//		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
//		NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
//    
//    USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//开启中断
// #endif
//    USART_Cmd(UART4, ENABLE);                    //使能串口 

 }

/**************************************************************************************************
Function:   UART5_Init(u32 bound)
Description:初始化串口5
Input:      波特率 bound
Output:     no
Return:     no
**************************************************************************************************/
void UART5_Init(u32 bound)
{
//    //GPIO端口设置
//    GPIO_InitTypeDef GPIO_InitStructure;
//	USART_InitTypeDef USART_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
//	 
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);	//使能GPIOA时钟
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOC, ENABLE);
// 	USART_DeInit(UART5);  //复位串口1
//	 //USART1_TX   PC12
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; //PC.12
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
//    GPIO_Init(GPIOC, &GPIO_InitStructure); //初始化PD8
//   
//    //USART1_RX	  PD.2
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
//    GPIO_Init(GPIOD, &GPIO_InitStructure);  //初始化PD9


//   //USART 初始化设置

//	USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
//	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
//	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
//	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
//	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
//	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

//    USART_Init(UART5, &USART_InitStructure); //初始化串口
//#if EN_USART1_RX		  //如果使能了接收  
//   //Usart1 NVIC 配置
//    NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
//	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
//   
//    USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);//开启中断
//#endif
//    USART_Cmd(UART5, ENABLE);                    //使能串口 

}



/**************************************************************************************************
========================================USART END===============================================
***************************************************************************************************/


/******************* (C)***Program End************文件结束*****************************************/

