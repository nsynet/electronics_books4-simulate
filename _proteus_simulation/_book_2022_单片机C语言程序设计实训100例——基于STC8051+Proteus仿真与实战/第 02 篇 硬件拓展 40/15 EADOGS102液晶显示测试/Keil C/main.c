//-------------------------- main.c -------------------------------
//	名称: EADOGS102液晶显示测试
//-----------------------------------------------------------------
//	说明: 程序运行时，EADOGS102液晶将分别显示英文字符及二维码图片.
//
//-----------------------------------------------------------------
#include "STC15xxx.h"
#include "Dogs102x6.h"
#include "bitmap.h"
#include <intrins.h>
#include <stdio.h>
#define u8  unsigned char
#define u16 unsigned int
#define u32 unsigned long
#define MAIN_Fosc		12000000L
//-----------------------------------------------------------------
// 延时函数(取值1~65535)
//-----------------------------------------------------------------
void delay_ms(u16 x) { 
	u8 i = 12, j = 169;
	while(x--) {
		do {
			while (--j);
		} while (--i);
	}
}
//-----------------------------------------------------------------
// 主函数
//-----------------------------------------------------------------
void main() {
	u8 i, c = 0, AscCode;
	P0M1 = 0x00; P0M0 = 0x00;				//配置为准双向口
	Dogs102x6_init();						//EADogs初始化
	while(1) { 
		Dogs102x6_clearScreen();			//EADogs清屏
		//输出标题与横线
		Dogs102x6_stringDraw(0,0," EADOGS LCD Test ",0);
		Dogs102x6_stringDraw(1,0,"UC1701SIZE:102x64",0);
		Dogs102x6_horizontalLineDraw(0,101,20,0);

		
		
		
		
		
	}
}