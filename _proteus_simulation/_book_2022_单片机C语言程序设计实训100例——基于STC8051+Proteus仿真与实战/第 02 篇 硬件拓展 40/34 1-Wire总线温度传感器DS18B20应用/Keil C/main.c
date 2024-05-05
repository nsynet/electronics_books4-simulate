//-------------------------- main.c -------------------------------
//  名称: 1-Wire总线温度传感器DS18B20应用测试
//-----------------------------------------------------------------
//  说明: 运行本例时,外界温度将实时刷新显示在1602LCD上.
//
//-----------------------------------------------------------------
#include "STC15xxx.h"
#include <intrins.h>
#include <stdio.h>
#define u8  unsigned char
#define u16 unsigned int
u8 Temp_Disp_Buff[17];
extern u8 Temp_Value[];
extern void LCD_Initialise();
extern void LCD_ShowString(u8 r, u8 c,u8 *str);
extern void delay_ms(u16);
extern u8 Read_Temperature();
//-----------------------------------------------------------------
// 主函数
//-----------------------------------------------------------------
void main() {
	float temp = 0.0;						//浮点温度
	P0M1 = 0; P0M0 = 0;
	P1M1 = 0; P1M0 = 0;
	P2M1 = 0; P2M0 = 0;						//配置为准双向口
	P3M1 = 0; P3M0 = 0;
	LCD_Initialise(); 						//液晶初始化
	LCD_ShowString(0,0,"  DS18B20 Test  ");	//显示标题
	LCD_ShowString(1,0,"  Waiting.....  ");	//显示等待信息
	while(1) {								//循环读取温度并显示

	}
}