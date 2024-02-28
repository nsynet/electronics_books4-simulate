/*
@file	led.c
@brief	实现控制LED相关的接口
@author	bisheng picy@scut.edu.cn
*/
#include "led.h"



/*
@brief	通过置低电平点亮LED灯
@params	None
@retval	None
*/
void led_light(void){
	LL_GPIO_ResetOutputPin(GPIOB,LL_GPIO_PIN_0);
}
/*
@brief	通过置高电平熄灭LED灯
@params	None
@retval	None
*/
void led_dark(void){
	LL_GPIO_SetOutputPin(GPIOB,LL_GPIO_PIN_0);
}

