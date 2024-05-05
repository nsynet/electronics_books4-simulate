//-------------------------- main.c -------------------------------
//  名称: 基于HX711与称重传感器的电子秤仿真设计
//-----------------------------------------------------------------
//  说明: 本例运行时,通过键盘可输入单价,调节LoadCell（称重传感器）
//        上下箭头可模拟加减重量,LCD持续刷新显示当前单价与重量,
//        所输入的单价与重量的乘积（即金额）,将刷新显示LCD屏上.
//
//-----------------------------------------------------------------
#define u8  unsigned char
#define u16 unsigned int
#define u32 unsigned long
#include "STC15xxx.h"
#include "HX711.h"
#include <stdio.h>
#define MAIN_Fosc 12000000L				//时钟频率定义
//校准：其中0x3FBCB5为LoadCell调为100%时Proteus显示的诊断信息,
//形如：[HX711 SAMPLING] Converted A input = 0x3FBCB5, 
//      Voltage = 9.959 mV, Rate = 0.1000s [HXADC1_U1]
#define GapValue (((long)(0x3FBCB5))/200.0) //即：20885.385
extern void delay_ms(u8);
extern void KeyBoard_Handle();			//键盘处理及金额计算与显示函数
extern void Compute_and_show_sum();	//计算并显示结果
//液晶相关函数
extern void Initialize_LCD();
extern void LCD_ShowString(u8 r, u8 c, u8 *str);
extern char disp_buffer_W[];			//液晶显示缓冲(定义在calc.c)
//毛重、静重、前次结果值
long Tare = 0, NetWeight = 0, PreResult = 0;
bit Flag_Error = 0;						//错误标识变量
//-----------------------------------------------------------------
// 读取重量值
//-----------------------------------------------------------------
void Get_Weight() {


}
//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------
void main() {
	P0M1 = 0xFF; P0M0 = 0x00;		//P0配置为输入,其余为准双向口
	P1M1 = 0x00; P1M0 = 0x00;
	P2M1 = 0x00; P3M0 = 0x00;
	P3M1 = 0x00; P3M0 = 0x00; P3 = 0x00;
	Initialize_LCD();				//初始化LCD
	//显示初始信息
	LCD_ShowString(0,0,(char*)"  HX711 Scale Test  ");
	LCD_ShowString(1,0,(char*)"--------------------");
	LCD_ShowString(2,0,(char*)"P:        W:");	//第2行显示单价与重量
	LCD_ShowString(3,0,(char*)"SUM($):");		//第3行显示SUM标志(金额)
//	Tare = HX711_Read();						//读取未开始称重前的毛皮重量
	while(1) {

	
	}
}