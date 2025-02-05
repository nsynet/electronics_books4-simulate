/*****************************************************************************************************
Title: 				main header file
Current 			version: v1.0
Function:			Define variables,Statement subfunction.
processor: 	                STM32F10
Clock:				8-72M  Hz
Author:				huanghuajian
Company:			
Contact:			
E-MAIL:				huajian11@qq.com
Data:				  2017-3-21
*******************************************************************************************************/ 

#ifndef  __OLED_H__
#define  __OLED_H__
/******************************************************************************************************
========================================include head==================================================
******************************************************************************************************/
#include "stm32f10x.h"
#include "sys.h"
#include "delay.h" 
#define    uchar    unsigned char
#define    uint    unsigned int
	
   
#define  LCD_SCL   PBout(6)
#define  LCD_SI    PBout(7)
#define  LCD_A0    PBout(8)

extern uchar  BMP[];


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

void LCD_write(uchar data_command,uchar dc) ;
void LCD_Init(void) ;
void clrscr(uchar page_f, //显示一个字或多个字函数
uchar page_sum,uchar column_f,uchar column_sum );//x*8
void Draw_word(uint d_where,uchar page_f, //显示一个字或多个字函数
uchar page_sum,uchar column_f,uchar column_sum );//x*8

/******************************************************************************************************
========================================Define I/O==================================================
******************************************************************************************************/



/******************************************************************************************************
========================================Define Data==================================================
******************************************************************************************************/


/******************************************************************************************************
========================================变量定义==================================================
******************************************************************************************************/


/*********************************************************************
//定时器计时
*********************************************************************/
////typedef struct Timer_
////{
////	 uint16_t MSec;
////	 uint8_t  Sec;
////	
////}TimerCount;
////struct Timer_ Timer_Count;


//uint16_t TimingDelay;


/******************************************************************************************************
========================================子函数声明==================================================
******************************************************************************************************/
////////void RCC_Configuration(void);
//////void RCC_Configuration(void);
//////void Init_IO(void);
//////void TIM_Configuration(u16 p,u16 psc);
//////void NVIC_Configuration(void);
//////void DelayMs(uint16_t DelayData);

//////uint8_t KeyScan(void);
//////void LED_ON_OFF(uint8_t ON_OFF);
/******************************************************************************************************
========================================其他调用子函数声明=============================================
******************************************************************************************************/



/******************************************************************************************************
========================================Head END==================================================
******************************************************************************************************/

#endif
