/*
@file	led.h
@brief	定义控制LED灯相关的接口
@author	picy
*/
#ifndef __LED_H
#define __LED_H
#include "stm32f1xx_hal.h"
#include "gpio.h"
void led_light(void);
void led_dark(void);

#endif
