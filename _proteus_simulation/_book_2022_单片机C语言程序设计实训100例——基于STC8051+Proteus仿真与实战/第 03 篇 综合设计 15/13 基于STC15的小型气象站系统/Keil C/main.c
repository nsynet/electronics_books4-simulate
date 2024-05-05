//----------------------------- main.c --------------------------------
//  名称: 基于STC15的小型气象站系统
//---------------------------------------------------------------------
//  说明: 当程序运行时，当前温湿度、气压、雨量、风速、风向、光照强度等信息将刷新
//        显示在20×4 LCD上（相关代码基于Arduino库改编）
//
//---------------------------------------------------------------------
#define u8	unsigned char
#define u16	unsigned int
#define u32	unsigned long
#define MAIN_Fosc		11059200L	//系统时钟频率11.0592MHz
//---------------------------------------------------------------------
#include "STC15xxx.h"
#include <intrins.h>
#include <stdio.h>
#include "LM044L-4bit.h"
//---------------------------------------------------------------------
code char* Prompts[21] = {
	"  Weather  Station  ",
	"********************",
	"    TEST PROGRAM    ",
	"********************",
};
volatile u32 Millis = 0;
extern float getRH();
extern float getTemp();
extern float readAltitude();
extern float readPressure();
extern float readMPL3115A2_Temp();
extern void delay_ms(u8);
extern void setModeBarometer();
extern void setOversampleRate(u8);
extern void enableEventFlags();
extern void setModeAltimeter();
extern void setModeActive();
extern void InitADC();
float GetADCResult(u8 ch);

extern void poll();
extern float getRainHour();
extern float getRainDay();
extern float getWindSpeed();
extern float getWindDirection();
extern float rawWindDirection();
extern float rawWindSpeed();
extern float getGustSpeed();
extern float getGustDirection();
extern float getDaylight();
extern void reset_WSx();
//---------------------------------------------------------------------
// T0初始化(在12T模式下运行)
//---------------------------------------------------------------------
void Timer0Init() {		//1毫秒@11.0592MHz


}
//---------------------------------------------------------------------
// T0中断函数(用于毫秒级计时,获取NOW)
//---------------------------------------------------------------------
void Timer0_INT () interrupt 1 {                      }
//---------------------------------------------------------------------
// 主程序
//---------------------------------------------------------------------
void main() {
	u8 i; char s[30];
	float Rh,T1,Pr,T2,Ra,Ws,Wd,Ld;
	P0M1 = 0x00; P0M0 = 0x00;	//P0-P3配置为准双向口
	P1M1 = 0x00; P1M0 = 0x00;
	P2M1 = 0x00; P2M0 = 0x00;
	P3M1 = 0x00; P3M0 = 0x00;
	reset_WSx();				//复位相关参数（变量）
	setModeBarometer();			//测量气压（从20~110kPa）
	setOversampleRate(7);		//将过采样设置为128-----
	enableEventFlags();			//使能所有三个气压与温度事件标记-----
	Timer0Init();				//T0初始化
	InitADC();					//ADC模块初始化 
	Initialize_LCD();			//LCD初始化
	//输出系统封面文字(4行)
	for (i = 0; i < 4; i++) {
		LCD_ShowString(i,0,(char*)Prompts[i]);
	}
	IT0 = 1;					//INT0下降沿触发
	IT1 = 1;					//INT1下降沿触发
	PX0 = 1;					//设置优先级
	IE |= 0x05;					//INT0,INT1开中断
	EA = 1;
	while (1) {

	}
}