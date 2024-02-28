//----------------------------- main.c --------------------------------
//  名称: 用STC15+1601LCD设计的整型计算器
//---------------------------------------------------------------------
//  说明: 本案例程序根据LABCENTER ELECTRONICS提供的由C语言与汇编语言混合编写
//	      的原始程序改编。本案例作了简化设计并将原始程序代码全部改为C语言程序代码
//	      
//---------------------------------------------------------------------
#define u8  unsigned char
#define u16 unsigned int
#include "STC15xxx.h"
#include <intrins.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "calc.h"
static long a,b;			//当前运算符的前后两个操作数
static char CurrKeyChar;	//当前按键字符
static char Last_OP;		//最近输入的操作符
static char Last_Char;		//所输入的前一个字符
static char result;			//当前运算的结果状态
//显示缓冲区、数据输入缓冲区及数据输入缓冲区索引定义
static char xdata outputbuffer[MAX_DISPLAY_CHAR+1];
static char xdata NumberStr[MAX_DISPLAY_CHAR+1];
static char xdata NumberIdx;
extern void Initialize_LCD();
extern void LCD_Disp_String(char*);
extern void delay_ms(u8);
//---------------------------------------------------------------------
// 检查待显示数据是否越界
//---------------------------------------------------------------------
int calc_chkerror(long num) { return labs(num) <= 9999999? OK : ERROR;}
//---------------------------------------------------------------------
// 主程序
//---------------------------------------------------------------------
void main() { 
	P0M1 = 0x00; P0M0 = 0x00;		//P0,P1配置为准双向口
	P1M1 = 0x00; P1M0 = 0x00;
	a = 0; b = 0;					//两个操作数初始为0
	CurrKeyChar = '='; Last_OP = '0';	//初始化当前按键字符及最近的操作符
	NumberStr[0] = '\0'; NumberIdx = 0; //清空数据输入缓冲区,其索引归零
	Initialize_LCD();				//初始化LCD
	LCD_Disp_String("0");			//初始时显示0
	while(1) {						//循环扫描键盘并进行运算处理与显示
		//调用矩阵键盘扫描程序,有按键被按下时返回按键字符,无按键被按下时循环扫描
		do { CurrKeyChar = GetKeyChar();} while (!CurrKeyChar);
		if ( isdigit(CurrKeyChar) ) {	//如果是数字键

		
		}
		else {//处理非数字按键(包括+,-,*,/,=,C)

		
		}
		//完成当前输入数字或非数字字符处理后,Last_Char变量保存最近输入的字符
		Last_Char = CurrKeyChar;
	}
}
//---------------------------------------------------------------------
// 根据运算符按键进行运算处理
//---------------------------------------------------------------------
void Operator_Process(char OP) { 
	switch(OP) { 
		//处理+,-,*,/
		case '+' : if ( CurrKeyChar == '=' || isdigit(Last_Char)){
						a += b;	result = calc_chkerror(a); 
					}	else result = SLEEP; 	break;
		case '-' : if ( CurrKeyChar == '=' || isdigit(Last_Char)){
						a -= b; result = calc_chkerror(a);
					}	else result = SLEEP; 	break;
		case '*' : if ( CurrKeyChar == '=' || isdigit(Last_Char)){
						a *= b; result =  calc_chkerror(a);
					}	else result = SLEEP; 	break;
		case '/' : if ( CurrKeyChar == '=' || isdigit(Last_Char)){
						if (b) {
							a /= b;	result = calc_chkerror(a);
						}	else result = SLEEP;
					}	else result = SLEEP; 	break;
		//取消,将相关变量清零或置为'0',状态置为OK,以便显示结果0
 		case 'C' :	a = b = 0; CurrKeyChar = Last_OP = '0';
					result = OK; break;
		default :	result = SLEEP;  
	}
	//输出显示结果
	switch (result) {
		//将合法的长整数结果转换为字符串并输出显示
		case OK	:	sprintf(outputbuffer,"%ld",a);
					LCD_Disp_String(outputbuffer);	break;
		//当前尚不能执行一次运算,故不刷新显示
		case SLEEP :								break;
		//其余情况均显示异常“Exception”
		case ERROR: default: a = b = 0; CurrKeyChar = Last_OP = '0';
					LCD_Disp_String("Exception ");	break;
	}
}