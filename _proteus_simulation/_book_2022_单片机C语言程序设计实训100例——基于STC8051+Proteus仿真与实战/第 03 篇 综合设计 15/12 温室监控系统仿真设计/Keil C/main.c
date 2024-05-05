//--------------------------- main.c ------------------------------
//  名称: 温室控制系统仿真设计
//-----------------------------------------------------------------
//  说明: K1~K3按键分别控制通风、采光及水泵电机开关,LCD显示当前温度值.
//        上位机按钮可分别实现K1~K3的控制功能,系统运行时,下位机温度值
//        将刷新显示在上位机C#窗体中.
//
//-----------------------------------------------------------------
#include "STC15xxx.h"
#include <intrins.h>
#include <string.h>
#include <stdio.h>
#define u8	unsigned char
#define u16	unsigned int
#define MAX_CHAR 11					//允许接收并保存的最大字符个数
volatile u8 recv_buff[MAX_CHAR+1];	//串口接收缓冲
volatile u8 Buf_Index = 0;			//缓冲索引
extern u8 Read_Temperature();		//读传感器温度函数
extern void LCD_Initialize();		//LCD初始化函数
extern void LCD_ShowString(u8 ,u8,u8 *);//在指定行/列显示字符串函数
extern u8 Temp_Value[];				//从DS18B20读取的数据
extern void delay_ms(u8 x);			//延时函数
char Disp_Buffer[21];				//LCD显示缓冲
volatile u8 recv_OK = 0;			//上位机命令串接收成功标识
//相关按键、控制引脚等定义
sbit K1 = P3^4;						//通风电机开关控制按键
sbit K2 = P3^5;						//采光电机开关控制按键
sbit K3 = P3^6;						//水泵开关控制按键
sbit LED_1 = P0^0;					//通风电机开关指示灯
sbit LED_2 = P0^1;					//采光电机开关指示灯
sbit LED_3 = P0^2;					//水泵指示灯
sbit RELAY = P0^3;					//水泵控制继电器
sbit F_IN1 = P0^4;					//通风电机控制端
sbit F_IN2 = P0^5;
sbit F_IN3 = P0^6;					//采光电机控制端
sbit F_IN4 = P0^7;
bit TX1_Busy; 						//发送忙标志
//-----------------------------------------------------------------
// 向串口输出一个字符
//-----------------------------------------------------------------
void PutChar(u8 c) {
	TX1_Busy = 1; SBUF = c; while(TX1_Busy) delay_ms(1);
}
//-----------------------------------------------------------------
// 串口输出字符串
//-----------------------------------------------------------------
void PutStr(char *s) { while(*s) PutChar(*s++); }
//-----------------------------------------------------------------
// 串口配置
//-----------------------------------------------------------------
void UartInit() {		//9600bps@12.000MHz


}
void Refresh_LCD() {
	if (LED_1 == 1)	LCD_ShowString(3,3,		(char*)"->>");
	else			LCD_ShowString(3,3,		(char*)" X ");
	if (LED_2 == 1)	LCD_ShowString(3,10,	(char*)"->>");
	else			LCD_ShowString(3,10,	(char*)" X ");
	if (LED_3 == 1)	LCD_ShowString(3,17,	(char*)"->>");
	else			LCD_ShowString(3,17,	(char*)" X ");
}
//-----------------------------------------------------------------
// 主函数
//-----------------------------------------------------------------
void main() {
	float temp = 0.0;				//浮点型温度变量
	P0M1 = 0x00; P0M0 = 0x00;		//配置为准双向口
	P1M1 = 0x00; P1M0 = 0x00;
	P2M1 = 0x00; P2M0 = 0x00;
	P3M1 = 0x00; P3M0 = 0x00;
	LED_1 = LED_2 = LED_3 = 0;		//初始时关闭三只LED
	UartInit();						//串口配置（9600bps)
	IT0 = 1;						//INT0下降沿触发
	IE = 0x91;						//允许串口中断与INT0中断
	LCD_Initialize(); 				//液晶初始化
	LCD_ShowString(0,0,"   Greenhouse Test  ");//显示标题
	LCD_ShowString(1,0,"--------------------");//显示分隔线
	LCD_ShowString(2,0,"TEMP: ");
	LCD_ShowString(3,0,"PU:    WD:    LT:    ");
	Read_Temperature();				//读取温度
	delay_ms(800);					//延时
	while(1) {						//循环读取温度并显示
		if (Read_Temperature()){	//读取温度正常则转换并显示

		
		}
		if (recv_OK) {				//串口命令完整接收则进行处理

		
		}
		Refresh_LCD();
		delay_ms(200);				//延时(过快读传感器将导致错误)
	}
}
//-----------------------------------------------------------------
// INT0中断函数
//-----------------------------------------------------------------
void INT0_ISR() interrupt 0 {
	if (K1 == 0) {					//通风电机开关控制
		delay_ms(10);
		if (K1 == 0) {
			if (LED_1 == 1) {	F_IN1 = 1; F_IN2 = 1; LED_1 = 0; }
			else 			{	F_IN1 = 1; F_IN2 = 0; LED_1 = 1; }
		}
	}
	if (K2 == 0) {					//采光电机开关控制
		delay_ms(10);
		if (K2 == 0) {
			if (LED_2 == 1) {	F_IN3 = 1; F_IN4 = 1; LED_2 = 0; }
			else 			{	F_IN3 = 1; F_IN4 = 0; LED_2 = 1; }
		}
	}
	if (K3 == 0) {					//水泵开关控制
		delay_ms(10);
		if (K3 == 0) {
			if (LED_3 == 1) {	RELAY = 1;  LED_3 = 0; } 
			else 			{	RELAY = 0;  LED_3 = 1; }
		}
	}
}
//-----------------------------------------------------------------
// 串口接收中断函数
//-----------------------------------------------------------------
void Serial_INT_ISR() interrupt 4 {
	static u8 i = 0; u8 c;
	if (RI) {						//接收中断标志位判断
		RI = 0;	c = SBUF;			//清串口接收标志,读取一字节
		if (c == '$') { i = 0; return; }//首字符判断($)
		if (c == 0x0D) return;		//忽略0x0D
		if (c == 0x0A){ i = 0; recv_OK = 1;}	//结束字符处理
		else {						//正常接收
			recv_buff[i] = c; recv_buff[++i] = '\0';
			if (i == MAX_CHAR) i = 0;	//接收字符长度异常时i归0
		}
	}
	if (TI) {						//发送中断标志位判断
		TI = 0; TX1_Busy = 0;		//清除TX1发送忙状态
	}
}