//------------------------- HX711.h -------------------------------
//  名称: HX711驱动程序头文件
//-----------------------------------------------------------------
#ifndef __HX711_H__
#define __HX711_H__

#define u8  unsigned char
#define u16 unsigned int
#define u32 unsigned long
#include "STC15xxx.h"
#include <intrins.h>
//HX711引脚配置 
sbit HX711_DOUT = P2^0;	//HX711数据输出引脚
sbit HX711_SCK  = P2^1;	//HX711时钟引脚
//相关函数声明
extern void delay_ms(u8);
extern long HX711_Read();

#endif