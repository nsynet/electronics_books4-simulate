//---------------------------- main.c -----------------------------
//  名称: PCF8583实时时钟显示程序
//-----------------------------------------------------------------
//  说明: 从PCF8583中读取日历时钟数据并刷新显示于LCD.
//
//-----------------------------------------------------------------
#define u8 	unsigned char
#define u16	unsigned int
#include "STC15xxx.h" 
#include "PCF8583.h"
#include <intrins.h>
#include <stdio.h>
#include <string.h> 
extern void LCD_ShowString(u8 r, u8 c,u8 *str);
extern void Initialize_LCD();
extern void delay_ms(u8 ms);
extern u8 DateTime[7];
extern char WEEK[][4];
char buf1[12] = "DATE: 00/00";
char buf2[16] = "TIME: 00:00:00";
char disp_buff[10];
//-----------------------------------------------------------------
// 日期与时间值转换为数字字符
//-----------------------------------------------------------------
void Format_DateTime(u8 d, u8 *a) { 


}
//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------
void main() {  
	P0M1 = 0; P0M0 = 0;			//配置为准双向口
	P2M1 = 0; P2M0 = 0;
	Initialize_LCD();
	LCD_ShowString(0,0,(char *)"*PCF8583 Clock**");
	while (1) {

	
	}
}