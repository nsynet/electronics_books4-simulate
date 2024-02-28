//-------------------------- calc.c -------------------------------
// 名称: 电子秤价格输入与金额计算程序
//-----------------------------------------------------------------
#define u8  unsigned char
#define u16 unsigned int
#include "STC15xxx.h"
#include <intrins.h>
#include <intrins.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
//蜂鸣器定义
sbit BEEP = P3^5;
//按键判断及按键键值
#define Key_Pressed	(P0 & (1<<4))	//DA(P1.4)为高电平时有键按下
#define Key_NO		(P0 & 0x0F)		//解码器输出线连接在P0低四位
//键盘字符表(其中注意2,5,8后各保留一个空格)
code char KEY_CHAR_TABLE[] = "012 345 678 9.C";
//液晶显示字符串函数
extern void LCD_ShowString(u8 r, u8 c,char *str);
extern void delay_ms(u8);
//LCD显示输出缓冲(价格/重量/金额)的最大长度
//因为要预留结束标志,实际串长比定义少1位
#define PLEN	7
#define WLEN	6
#define SUMLEN  10
//LCD显示输出缓冲(价格/重量/金额)
char disp_buffer_P[PLEN];
char disp_buffer_W[WLEN];
char disp_buffer_SUM[SUMLEN];
//价格输入缓冲索引
u8 NumberPtr = 0;
//-----------------------------------------------------------------
// 蜂鸣器输出
//-----------------------------------------------------------------
void Sounder() { 

}
//-----------------------------------------------------------------
// 处理运算并显示金额
//-----------------------------------------------------------------
void Compute_and_show_sum() { 

}
//-----------------------------------------------------------------
// 处理键盘操作
//-----------------------------------------------------------------
void KeyBoard_Handle() {
	char  KeyChar;
	//是否已经输入了价格P的小数点
	static u8 havedot = 0;
	//在还没有输入价格中的小数点时可继续输入字符的个数(dtnum初始时默认为7)
	static u8 dtnum = PLEN;
	//如果有键按下则获取按键字符(根据解码器DA引脚是否输出高电平来判断)
	if (Key_Pressed) {
		Sounder();							//每次按键时输出按键提示音
		KeyChar = KEY_CHAR_TABLE[Key_NO];	//根据键值获取按键字符
		//如果输入的是数字字符或小数点(但此前未输入过小数点)
		//----------------------------------------------------------
		if (isdigit(KeyChar) || (KeyChar == '.' && !havedot)) {
			//在目前还未输入小数点,且当前输入的不是小数点,而此时串长已为3时返回
			//(由于输入范围为0~999.99,程序不允许输入3位以上的整数)
			if (strlen(disp_buffer_P)==3 && 
				(KeyChar!='.'&&!havedot)) return;
			//将所输入的字符存入缓冲
			if (NumberPtr < dtnum) {
				//如果输入的第一个字符是'0'或"."则直接处理为"0."
				//这样设计可允许用户在没有非0的价格整数位时直接从小数点开始输入
				//例如要输入"0.86"时可直接输入".86"
				if ( NumberPtr==0 && (KeyChar=='0'||KeyChar=='.')) {
					disp_buffer_P[NumberPtr++] = '0'; KeyChar = '.';
					disp_buffer_P[NumberPtr++] = '.';
				}
				else {
					//否则正常存入新输入字符
					disp_buffer_P[NumberPtr++] = KeyChar;
				}
				disp_buffer_P[NumberPtr] = '\0';	//加字符串结束标志
				LCD_ShowString(2,3,disp_buffer_P);	//刷新显示价格
			}
			//遇到小数点且此前未输入过小数点则开始限定可输入的小数位
			if (KeyChar == '.' && !havedot) {
				dtnum = NumberPtr + 2;	havedot = 1;
			}
		}
		//清除当前所输入的价格
		//----------------------------------------------------------
		else if (KeyChar == 'C') {
			NumberPtr = 0;				//disp_buffer_P数字缓冲指针归0
			havedot = 0;				//小数点输入标志清0
			dtnum = PLEN - 2;			//复位小数点后可输入字符个数
			disp_buffer_P[0]	= '\0'; //清除价格及金额LCD输出缓冲
			disp_buffer_SUM[0] = '\0';
			LCD_ShowString(2,3,(char*)"      ");	//输出6个空格,清除价格
			LCD_ShowString(3,7,(char*)"         ");	//输出9个空格,清除金额
		}
		if (Key_Pressed) Compute_and_show_sum();	//计算并显示总金额
		while (Key_Pressed);						//等待按键释放
	}
}