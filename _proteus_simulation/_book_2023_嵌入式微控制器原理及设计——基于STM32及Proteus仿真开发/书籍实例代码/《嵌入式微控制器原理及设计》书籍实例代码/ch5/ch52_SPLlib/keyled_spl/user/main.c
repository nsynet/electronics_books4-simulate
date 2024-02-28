/*
@file	main.c
@brief	按钮S1控制LED1灯的亮灭
@author	Zev
*/

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "led.h"
#include "key.h"

/*
@brief	检测按钮S1是否按下，如果按下则点亮LED1；否则熄灭LED1
@params	None
@retval 0 程序正常结束
*/
int main(void){
	led_init();	//初始化LED1
	key_init();	//初始化按键S1
	
	while(1){
		if(key_press()){	//按钮按下
			led_light();	//点亮LED1
		}else{				//按钮松开
			led_dark();		//熄灭LED1
		}
	}
	//return 0;
}
