/*
@file	led.c
@brief	实现控制LED相关的接口
@author bisheng picy@scut.edu.cn
*/
#include "led.h"



/*
@brief	通过置低电平点亮LED灯
@params	None
@retval	None
*/
void led_light(void){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
}
/*
@brief	通过置高电平熄灭LED灯
@params	None
@retval	None
*/
void led_dark(void){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
}

