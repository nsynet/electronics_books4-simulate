//-----------------------------------------------------------------
//  名称: LM044L液晶4位模式驱动程序
//-----------------------------------------------------------------
#ifndef __LM044_4bit__
#define __LM044_4bit__
#include "STC15xxx.h"
#include <intrins.h>
#define u8  unsigned char
#define u16 unsigned int
//LCD引脚定义
sbit RS = P2^0;									//LCD寄存器选择
sbit RW = P2^1;									//LCD读写控制
sbit EN = P2^2;									//LCD使能控制
//液晶端口定义
#define LCD_PORT P2							//液晶端口(P2高4位)
//LCD相关函数
void delay_ms(u8 x);						//延时函数
void Initialize_LCD();					//LCD初始化
void LCD_Busy_Wait();						//忙等待
void Write_LCD_Dat(u8 dat);			//写LCD数据
void Write_LCD_Cmd(u8 cmd);			//写LCD指令
void LCD_ShowString(u8,u8,char*);//LCD显示字符串
#endif