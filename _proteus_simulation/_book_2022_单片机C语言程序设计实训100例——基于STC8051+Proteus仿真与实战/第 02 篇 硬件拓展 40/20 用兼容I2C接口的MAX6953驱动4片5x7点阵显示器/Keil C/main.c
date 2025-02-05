//------------------------- main.c --------------------------------
//  名称: 用兼容I2C接口的MAX6953驱动4片5x7点阵显示器
//-----------------------------------------------------------------
//  说明: 本例运行时,四块点阵屏将滚动显示一组信息串,信息串中的字符
//		点阵信息由MAX6953提供,本例不需要为各字符单独提供字模点阵.
//		运行过程中通过按键命令可随时关断或开启6953.
//
//-----------------------------------------------------------------
#define u8  unsigned char
#define u16 unsigned int
#define u32 unsigned long
#define MAIN_Fosc	12000000L		//系统时钟频率12MHz
#include "STC15xxx.h"
#include <intrins.h>
#include <stdio.h>
#include <string.h>
sbit SDA = P3^0;					//数据线
sbit SCL = P3^1;					//时钟线
#include "I2C.h"					//I2C总线通用宏及函数
//子器件地址
#define MAX6953R 0xA1				//1 = READ
#define MAX6953W 0xA0				//0 = WRITE
//四块点阵屏滚动显示的信息串
char LED_String[] = "5*7LED TEST : <----0123456789";
//-----------------------------------------------------------------
// 延时子程序（x=1~255ms,自适应时钟）
//-----------------------------------------------------------------
void delay_ms(u8 x) {
	u16 i;
	do{
		i = MAIN_Fosc / 13000;
		while(--i);
	}while(--x);
}
//-----------------------------------------------------------------
// 写MAX6953子程序
//-----------------------------------------------------------------
void MAX6953_Write(u8 addr, u8 dat) {

}
//-----------------------------------------------------------------
// MAX6953初始化
//-----------------------------------------------------------------
void MAX6953_INIT() {

}
//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------
void main() {
	u8 i,j;
	P3M1 = 0x00; P3M0 = 0x00;	//P3置为准双向口
	IE = 0x81;					//允许INT0中断
	IT0 = 1;					//下降沿触发
	MAX6953_INIT();				//MAX6953初始化设置
	while(1) {

	}
}
//-----------------------------------------------------------------
// INT0中断函数控制点阵屏关断或开启
//-----------------------------------------------------------------
void EX_INT0() interrupt 0 {

}