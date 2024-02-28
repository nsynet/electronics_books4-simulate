//-----------------------------------------------------------------
// 名称: 1602液晶驱动程序
//-----------------------------------------------------------------
#ifndef ___LCD1602___
#define ___LCD1602___
#define u8  unsigned char
#define u16 unsigned int
#include "STC15xxx.h"
#include <intrins.h>
sbit RS = P2^0;			//寄存器选择线
sbit RW = P2^1;			//读/写控制线
sbit EN = P2^2;			//使能控制线
void Write_LCD_Command(u8);
void Write_LCD_Data(u8);
void Initialize_LCD();
void LCD_ShowString(u8,u8,char*);
void DisplayOneChar(u8 r, u8 c, char d);
#endif