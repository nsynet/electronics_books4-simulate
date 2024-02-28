/**
@file	usart.c
@brief	实现与串口有关的函数
@author	Zev
*/

#include <stm32f10x.h>

static void rcc_config(void);
static void gpio_config(void);

/**
@brief	配置USART1以及开启所需的时钟和使能GPIO口
@param	None
@retval	None
*/
void usart_config(void){
	USART_InitTypeDef usart_init;
	
	rcc_config();
	gpio_config();
	
	usart_init.USART_BaudRate = 115200;
	usart_init.USART_WordLength = USART_WordLength_8b;
	usart_init.USART_StopBits = USART_StopBits_1;
	usart_init.USART_Parity = USART_Parity_No;
	usart_init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usart_init.USART_Mode = USART_Mode_Tx;
	USART_Init(USART1,&usart_init);
	USART_Cmd(USART1, ENABLE);
}
/**
@brief	通过串口发送一个字符
@param	None
@retval	None
*/
void usart_send_char(char c){
	USART_SendData(USART1,(uint8_t)c);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);	//等待发送完成
}
/**
@brief	配置串口所需的时钟
@param	None
@retval	None
@note	这是一个私有函数
*/
static void rcc_config(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOA,ENABLE);
}
/**
@brief	配置串口所需的GPIO口
@param	None
@retval	None
@note	这是一个私有函数
*/
static void gpio_config(void){
	GPIO_InitTypeDef gpio_init;
	
	gpio_init.GPIO_Pin=GPIO_Pin_9;
	gpio_init.GPIO_Mode=GPIO_Mode_AF_PP;
	gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gpio_init);
}
