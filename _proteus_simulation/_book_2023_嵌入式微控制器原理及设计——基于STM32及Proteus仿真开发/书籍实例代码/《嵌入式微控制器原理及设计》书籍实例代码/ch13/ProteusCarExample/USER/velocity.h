#ifndef __VELOCITY_H__
#define __VELOCITY_H__ 
#include "stm32f10x.h"

typedef struct  Timer_
{
	 uint16_t MSec;
	 uint8_t  Sec;
	
} TimerCount;


void EXTIX_Init(void);
void TIM2_Configuration(void);
void TIM2_1_Configuration(u16 p,u16 psc);

#endif



