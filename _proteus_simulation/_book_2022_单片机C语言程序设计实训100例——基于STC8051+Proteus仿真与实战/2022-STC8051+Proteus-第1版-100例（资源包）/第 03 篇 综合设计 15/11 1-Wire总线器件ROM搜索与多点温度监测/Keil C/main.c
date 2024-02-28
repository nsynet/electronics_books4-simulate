//--------------------------- main.c ------------------------------
//  名称: 1-Wire总线器件ROM搜索程序及多点DS18B20监测
//-----------------------------------------------------------------
//  说明: 本例自动搜索所有1-Wire总线器件,遇到温度传感器时显示其温度值
//        否则仅显示其ROMCODE编码及当前搜索到的器件总数.
//
//-----------------------------------------------------------------
#define u8  unsigned char
#define u16 unsigned int
#include "STC15xxx.h"
#include "1-Wire.h"
#include <intrins.h>
#include <stdio.h>
extern void LCD_Initialize();
extern void LCD_ShowString(u8 r, u8 c,u8 *str);
extern void Search_ALL_ROM();
//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------
void main() {
	P0M1 = 0; P0M0 = 0;			//配置为准双向口
	P1M1 = 0; P1M0 = 0;
	P2M1 = 0; P2M0 = 0;
	P3M1 = 0; P3M0 = 0;
	LCD_Initialize();			//液晶初始化
	LCD_ShowString(0,0,(char*)"1-Wire Device Search");	//显示标题文字
	while(1) Search_ALL_ROM();	//搜索所有器件,遇到DS18B20时读取并显示温度
}