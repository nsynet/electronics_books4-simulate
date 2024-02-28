/**
@file	exti.c
@brief	实现与外部中断有关的函数
@author	Zev
*/

#include <stm32f10x.h>

static void rcc_config(void);
static void gpio_config(void);
static void nvic_config(void);

/**
@brief	配置外部中断以及相关的时钟和GPIO口
@param	None
@retval	None
@note	这里使用的是PA8和EXTI_Line8
*/
void exti_config(void){
	EXTI_InitTypeDef exti_init;
	
	rcc_config();
	gpio_config();
	
	exti_init.EXTI_Line=EXTI_Line2;
	exti_init.EXTI_LineCmd=ENABLE;
	exti_init.EXTI_Mode=EXTI_Mode_Interrupt;
	exti_init.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Init(&exti_init);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource2);
	nvic_config();
}
/**
@brief	配置外部中断相关的时钟
@param	None
@retval	None
@note	这是一个私有函数
*/
static void rcc_config(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_AFIO,ENABLE);
}
/**
@brief	配置外部中断相关的GPIO口
@param	None
@retval	None
@note	这是一个私有函数
*/
static void gpio_config(void){
	GPIO_InitTypeDef gpio_init;
	
	gpio_init.GPIO_Mode=GPIO_Mode_IPU;
	gpio_init.GPIO_Pin=GPIO_Pin_2;
	gpio_init.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&gpio_init);
}
/**
@brief	配置外部中断相关的中断
@param	None
@retval	None
@note	这是一个私有函数
*/
static void nvic_config(void){
	NVIC_InitTypeDef nvic_init;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	nvic_init.NVIC_IRQChannel=EXTI2_IRQn;
	nvic_init.NVIC_IRQChannelCmd=ENABLE;
	nvic_init.NVIC_IRQChannelPreemptionPriority=1;
	nvic_init.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&nvic_init);
}
