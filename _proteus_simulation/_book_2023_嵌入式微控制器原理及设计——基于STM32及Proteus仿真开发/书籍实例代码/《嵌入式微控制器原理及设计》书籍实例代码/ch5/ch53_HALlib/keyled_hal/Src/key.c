/*
@file	key.c
@brief	实现与按钮检测相关的接口
@author	bisheng picy@scut.edu.cn
*/
#include "key.h"

/*
@brief	KEY按键读取
@params	None
@retval	1 按钮按下；0 按钮松开
*/
char key_press(void){
	return !HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0);     //KEY按键读取
}



