/*
@file	led.c
@brief	实现控制LED相关的接口
@author	Zev
*/
/*
@file	《嵌入式微控制器原理及设计》书籍（作者:毕盛等 Email:picy@scut.edu.cn  电子工业出版社）配套实例ch5.2
*/

#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

static void rcc_init(void);
static void gpio_init(void);

/*
@brief	初始化与LED控制相关的时钟和GPIO
@params	None
@retval	None
*/
void led_init(void){
	rcc_init();
	gpio_init();
}
/*
@brief	通过置低电平点亮LED灯
@params	None
@retval	None
*/
void led_light(void){
	GPIO_ResetBits(GPIOB,GPIO_Pin_0);
}
/*
@brief	通过置高电平熄灭LED灯
@params	None
@retval	None
*/
void led_dark(void){
	GPIO_SetBits(GPIOB,GPIO_Pin_0);
}
/*
@brief	初始化LED控制相关的时钟
@params	None
@retval	None
@note	这是一个私有函数
*/
static void rcc_init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
}
/*
@brief	初始化LED控制相关的GPIO
@params	None
@retval	None
@note	这是一个私有函数
*/
static void gpio_init(void){
	GPIO_InitTypeDef gpio_init;

	//将PB0设置为推挽输出
	gpio_init.GPIO_Mode=GPIO_Mode_Out_PP;
	gpio_init.GPIO_Pin=GPIO_Pin_0;
	gpio_init.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&gpio_init);
}
