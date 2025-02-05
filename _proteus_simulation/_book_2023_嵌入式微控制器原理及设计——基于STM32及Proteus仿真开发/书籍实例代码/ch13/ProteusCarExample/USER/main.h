

#ifndef  __MAIN_H__
#define  __MAIN_H__
/******************************************************************************************************
========================================include head==================================================
******************************************************************************************************/
#include "stm32f10x.h"


/******************************************************************************************************
========================================I/O设置定义数==================================================
 参数描述 ：GPIO_Speed描述
GPIO_Speed
GPIO_Speed_ 2MHzMHz        最高输出速率 2MHz
GPIO_Speed_ 10 MHz MHz     最高输出速率 10MHz
GPIO_Speed_50MHz           最高输出速率 50MHz

 参数描述 ：GPIO_Mode      设置选中管脚的速率

GPIO_Mode_AIN              模拟输入
GPIO_Mode_IN_FLOATING      浮空输入 
GPIO_Mode_IPD              下拉输入
GPIO_Mode_IPU              上拉输入
GPIO_Mode_Out_OD           开漏输出
GPIO_Mode_Out_PP           推挽输出
GPIO_Mode_AF_OD            复用开漏输出
GPIO_Mode_AF_PP            复用推挽输出
******************************************************************************************************/




/******************************************************************************************************
========================================Define I/O==================================================
******************************************************************************************************/



/******************************************************************************************************
========================================Define Data==================================================
******************************************************************************************************/


/******************************************************************************************************
========================================变量定义==================================================
******************************************************************************************************/

uint16_t TimingDelay;


/******************************************************************************************************
========================================子函数声明==================================================
******************************************************************************************************/
//void RCC_Configuration(void);
void RCC_Configuration(void);
void Init_IO(void);
void TIM_Configuration(u16 p,u16 psc);
void NVIC_Configuration(void);
void DelayMs(uint16_t DelayData);

uint8_t KeyScan(void);
void LED_ON_OFF(uint8_t ON_OFF);
/******************************************************************************************************
========================================其他调用子函数声明=============================================
******************************************************************************************************/



/******************************************************************************************************
========================================Head END==================================================
******************************************************************************************************/

#endif
