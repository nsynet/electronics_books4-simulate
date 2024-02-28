//-------------------------- main.c -------------------------------
//  名称: 数字气压传感器BMP180应用
//-----------------------------------------------------------------
//  说明: 本例运行时,1602液晶将持续刷新显示BMP180当前温度与气压数据。
//
//-----------------------------------------------------------------
#define u8  unsigned char
#define u16 unsigned int
#define u32 unsigned long
#define MAIN_Fosc	12000000L	//系统时钟频率12MHz
#include "STC15xxx.h"
#include <intrins.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
extern Init_BMP180();
extern BMP180Convert();
extern Initialize_LCD();
extern void delay_ms(u8);
extern void LCD_ShowString(u8, u8,char*);
extern void DisplayOneChar(u8 r, u8 c, char d);
//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------
void main() { 
	P1M1 = 0; P1M0 = 0;			//配置为准双向口
	P2M1 = 0; P2M0 = 0;
	P3M1 = 0; P3M0 = 0;
	delay_ms(50);				//上电延时
	Initialize_LCD();			//液晶初始化
	Init_BMP180();				//初始化BMP180 
	while(1){					//循环

	
	}
}
