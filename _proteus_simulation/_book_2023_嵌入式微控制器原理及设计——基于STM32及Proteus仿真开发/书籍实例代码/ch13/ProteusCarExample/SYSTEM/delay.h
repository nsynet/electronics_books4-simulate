/*****************************************************************************************************
Title: 				delay header file
Current 			version: v1.0
Function:			Define variables,Statement subfunction.
processor: 	                STM32F10
Clock:				8-72M  Hz
Author:				
Company:			
Contact:			
E-MAIL:				
Data:				  
*******************************************************************************************************/ 
#ifndef __DELAY_H
#define __DELAY_H 			   
#include "stm32f10x.h"

void delay_init(u8 SYSCLK);
void delay_ms(u16 nms);
void delay_us(u32 nus);

#endif





























