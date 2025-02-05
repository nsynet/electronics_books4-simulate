//-------------------------- main.c -------------------------------
//	名称: 用兼容I2C接口的MAX6955驱动16段数码管显示
//-----------------------------------------------------------------
//	说明: 本例运行时,8只16段数码滚动显示数字0~9,字母A~Z
//		  本例使MAX6955工作于全解码模式,因此只需要向MAX6955输出
//		  待显示字符ASCII码即可,不需要编写并发送各字符的段码.
//
//----------Proteus中单只16段数码管上下排引脚名称------------------
// NO.	1	2	3	4	5	6	7	8	9
//******************************************
// 上:	A1	A2	B	C	D2	D1	E	F	位控制
// 下:	H	I	J	G2	K	L	M	G1	DP
//-----------------------------------------------------------------
#define u8  unsigned char
#define u16 unsigned int
#define u32 unsigned long
#define MAIN_Fosc	12000000L	//系统时钟频率12MHz
#include "STC15xxx.h"
#include <intrins.h>
#include <stdio.h>
#include <string.h>
sbit SDA = P1^4;				//数据线
sbit SCL = P1^5;				//时钟线
#include "I2C.h"				//IIC总线通用宏及函数
#define MAX6955R 0xC1			//1 = READ 
#define MAX6955W 0xC0			//0 = WRITE
//16段数码管滚动显示的字符串
char SEG_LED_String[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
//-----------------------------------------------------------------
// 延时子程序
//-----------------------------------------------------------------
void Delay1ms() {				//@12.000MHz
	u8 i = 12, j = 169;
	do {
		while (--j);
	} while (--i);
}
//-----------------------------------------------------------------
void delay_ms(u16 x) { while (x--) Delay1ms(); }
//-----------------------------------------------------------------
// 写MAX6955子程序
//-----------------------------------------------------------------
void MAX6955_Write(u8 addr, u8 dat) {

}
//-----------------------------------------------------------------
// MAX6955初始化
//-----------------------------------------------------------------
void MAX6955_INIT() {
	MAX6955_Write(0x01, 0xFF);	//解码模式设置(全解码)
	MAX6955_Write(0x02, 0x03);	//亮度设置
	MAX6955_Write(0x03, 0x07);	//设置扫描范围0-7
	MAX6955_Write(0x04, 0x01);	//控制寄存器设置(非关断模式)
								//将0x01改为0x0D可使数码管以0.5s周期闪烁
	MAX6955_Write(0x06, 0x00);	//GPIO设置为输出
	MAX6955_Write(0x0C, 0x00);	//显示数字类型设置(数位0-7为16段或7段)
	MAX6955_Write(0x07, 0x01);	//显示测试(各数码管16段全部点亮)
	delay_ms(1000);				//延时(全屏点亮1s)
	MAX6955_Write(0x07, 0x00);	//关闭测试
}
//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------
void main() {
	u8 i,j,Len = strlen(SEG_LED_String);
	P1M1 = 0x00; P1M0 = 0x00;	//P1置为准双向口
	MAX6955_INIT();				//MAX6955初始化设置	
	while (1) {

	}
}