//------------------------ T6963C.h -------------------------
//  名称: PG160128显示驱动程序头文件
//-----------------------------------------------------------
#ifndef __T6963C__
#define __T6963C__
//-----------------------------------------------------------
#define u8 	unsigned char
#define u16	unsigned int
#include "STC15xxx.h"
#define  MAIN_Fosc  12000000L   	//定义主时钟
#include <stdio.h>
#include <math.h>
#include <string.h>
void delay_ms(u8);
void Delay10us();
void Delay20us();
//-----------------------------------------------------------
// T6963C 命令定义
//-----------------------------------------------------------
#define LCD_CUR_POS		0x21		//设置光标位置(在屏幕上的位置)
#define LCD_CGR_POS		0x22		//设置CGRAM偏置地址
#define LCD_ADD_POS		0x24		//设置DDRAM地址
#define LCD_TXT_STP		0x40		//文本区首址
#define LCD_TXT_WID		0x41		//文本区宽度
#define LCD_GRH_STP		0x42		//图形区首址
#define LCD_GRH_WID		0x43		//图形区宽度
#define LCD_MOD_OR		0x80		//显示方式:逻辑或
#define LCD_MOD_XOR		0x81		//显示方式:逻辑异或
#define LCD_MOD_AND		0x82		//显示方式:逻辑与
#define LCD_MOD_TCH		0x83		//显示方式:文本特征
#define LCD_DIS_SW		0x90		//显示开关
//D0=1/0:光标闪烁启用/禁用;D1=1/0:光标显示启用/禁用；
//D2=1/0:文本显示启用/禁用;D3=1/0:图形显示启用/禁用；
#define LCD_CUR_SHP		0xA0		//光标形状选择(1线,2线,...8线[块状]光标)
#define LCD_AUT_WR		0xB0		//自动写设置
#define LCD_AUT_RD		0xB1		//自动读设置
#define LCD_AUT_OVR		0xB2		//自动读/写结束
#define LCD_INC_WR		0xC0		//数据写,地址加1
#define LCD_INC_RD		0xC1		//数据读,地址加1
#define LCD_DEC_WR		0xC2		//数据写,地址减1
#define LCD_DEC_RD		0xC3		//数据读,地址减1
#define LCD_NOC_WR		0xC4		//数据写,地址不变
#define LCD_NOC_RD		0xC5		//数据读,地址不变
#define LCD_SCN_RD		0xE0		//读屏幕
#define LCD_SCN_CP		0xE8		//屏幕拷贝
#define LCD_BIT_OP		0xF0		//位操作
//-----------------------------------------------------------
// 变更LCD与MCU的连接时,只需修改以下数据、控制端口及控制引脚定义
//-----------------------------------------------------------
//LCD数据(命令)端口定义
#define LCD_DATA_PORT		P2
//LCD控制引脚定义(读,写,命令/数据寄存选择,使能)
sbit WR = P3^0;			//写使能
sbit RD = P3^1;			//读使能
sbit CD = P3^2;			//命令/数据寄存器选择线 (Command/Data)
sbit CE = P3^3;			//LCD使能
//-----------------------------------------------------------
// LCD控制相关函数
//-----------------------------------------------------------
u8 Status_BIT_01();//状态位STA1,STA0判断（写指令就绪和读写数据就绪）
u8 Status_BIT_3(); //状态位ST3判断（数据自动写状态）
u8 LCD_Write_Command(u8);								//写无参数指令
u8 LCD_Write_Command_P1(u8,u8);					//写单参数指令
u8 LCD_Write_Command_P2(u8,u8,u8);			//写双参数指令
u8 LCD_Write_Data(u8 dat);							//写数据
u8 LCD_Read_Data();											//读数据
void Display_Str_at_xy(u8,u8,char [],u8);	//在指定位置显示字符串
void LCD_Initialise();									//LCD初始化
void Clear_Screen();										//清屏
void Set_LCD_POS(u8, u8);								//设置当前地址
void OutToLCD(u8,u8,u8);								//输出到液晶
void Line(u8, u8, u8, u8, u8);					//绘制直线
void Pixel(u8,u8, u8);									//绘点 
void Draw_Image(u8*, u8, u8);						//绘制位图 
//-----------------------------------------------------------
#endif