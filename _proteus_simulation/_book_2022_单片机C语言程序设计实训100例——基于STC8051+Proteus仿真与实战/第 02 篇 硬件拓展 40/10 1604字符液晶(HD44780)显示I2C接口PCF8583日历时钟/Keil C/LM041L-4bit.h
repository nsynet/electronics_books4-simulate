//-----------------------------------------------------------------
//  名称: LM041L-4bit液晶驱动程序头文件（4位模式）
//-----------------------------------------------------------------
#ifndef __LM041L_4BIT__
#define __LM041L_4BIT__
#include "STC15xxx.h"
#include <intrins.h>
#define u8  unsigned char
#define u16 unsigned int
//LCD引脚定义
sbit RS = P0^0;  			//寄存器选择线
sbit RW = P0^1;	 			//读/写控制线
sbit EN = P0^2;	 			//使能控制线
//液晶端口定义
#define LCD_PORT P0							//液晶端口(P0高4位)
//LCD相关函数
void delay_ms(u8 x);						//延时函数
void Initialize_LCD();					//LCD初始化
void LCD_Busy_Wait();						//忙等待
void Write_LCD_Dat(u8 dat);			//写LCD数据
void Write_LCD_Cmd(u8 cmd);			//写LCD指令
void LCD_ShowString(u8,u8,char*);//LCD显示字符串
#endif