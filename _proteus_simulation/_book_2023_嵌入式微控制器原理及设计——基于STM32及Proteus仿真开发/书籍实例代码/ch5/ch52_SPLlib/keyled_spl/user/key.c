/*
@file	key.c
@brief	实现与按钮检测相关的接口
@author	Zev
*/
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

static void rcc_init(void);
static void gpio_init(void);

/*
@brief	初始化与按钮检测相关的时钟和GPIO
@params	None
@retval	None
*/
void key_init(void){
	rcc_init();
	gpio_init();
}
/*
@brief	初始化与按钮检测相关的时钟和GPIO
@params	None
@retval	1 按钮按下；0 按钮松开
*/
char key_press(void){
	return !GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0);
}
/*
@brief	初始化与按钮检测相关的时钟
@params	None
@retval	None
@note	这是一个私有函数
*/
static void rcc_init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	
}
/*
@brief	初始化与按钮检测相关的GPIO
@params	None
@retval	None
@note	这是一个私有函数
*/
static void gpio_init(void){
	GPIO_InitTypeDef gpio_init;
	//设置PA0为上拉输入
	gpio_init.GPIO_Mode=GPIO_Mode_IPU;
	gpio_init.GPIO_Pin=GPIO_Pin_0;
	GPIO_Init(GPIOA,&gpio_init);
}

