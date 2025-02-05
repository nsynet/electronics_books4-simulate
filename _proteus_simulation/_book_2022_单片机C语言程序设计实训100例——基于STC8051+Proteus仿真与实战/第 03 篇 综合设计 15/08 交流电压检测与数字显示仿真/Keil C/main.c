//-----------------------------------------------------------------
//  名称: 交流电压检测系统仿真
//-----------------------------------------------------------------
//  说明: 本例运行时,0~222V的交流电压将显示在数码管上，调整外部“被测”
//		交流电压时，数码管将实时刷新显示当前交流电压。
//
//-----------------------------------------------------------------
#define u8  unsigned char
#define u16 unsigned int
#include "STC15xxx.h"
#include <intrins.h>
#include <stdio.h>
#include <math.h>
//-----------------------------------------------------------------
//A/D转换器LTC1864引脚定义
sbit SDO 	= P0^0;	//串行数据输出引脚
sbit SCK 	= P0^1;	//串行时钟引脚
sbit CONV 	= P0^2;	//转换控制引脚
//595引脚定义
sbit SH_CP	= P3^5;	//移位时钟脉冲
sbit DS 	= P3^6;	//串行数据输入
sbit ST_CP	= P3^7;	//输出锁存器控制脉冲
//-----------------------------------------------------------------
double AC_Volt,avg_AC_Volt,ui;
u8 digit[4];
volatile u8 i_Count = 0;
const u8 SEG_CODE[] = {//共阴数码管段码表,最后一位为黑屏的段码
 0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0xFF};
//-----------------------------------------------------------------
// 延时函数 10us@12M
//-----------------------------------------------------------------
void Delay10us() {


}
//-----------------------------------------------------------------
// 串行输入子程序
//-----------------------------------------------------------------
void Serial_Input_595(u8 dat) {


}
//-----------------------------------------------------------------
// 并行输出子程序
//-----------------------------------------------------------------
void Parallel_Output_595() {


}
//-----------------------------------------------------------------
// 读取LTC1864模数转换值(16位,2字节)
//-----------------------------------------------------------------
u16 Read_LTC1864_ADC_Output() {


}
//-----------------------------------------------------------------
// 将4位整数分解位为4个数位
// 该函数仅使用加/减运算符,这比使用/与%分解的效率要高
//-----------------------------------------------------------------
void DEC_TO_4DIGIT(int x, u8 d[]) {


}
//-----------------------------------------------------------------
// 交流电压检测
//-----------------------------------------------------------------
void get_AC_Voltage() {
	u8 i,j; 	avg_AC_Volt = 0;
	for ( i = 0; i < 20; i++)	{		//共进行20趟计算
		i_Count = 0; AC_Volt = 0;		//相关变量清0
		//40次A/D转换采样并累加电压值
		for (j = 0; j < 40; j++) {
			//读取LTC864 A/D转换输出值并转换为电压值(减去提升的2V电压)
			ui = Read_LTC1864_ADC_Output() * 5.0 / 65536 - 2.0;
			AC_Volt += ((double)ui * (double)ui); //平方值累加
		}
		//将采样的平方和除以40,开方,然后乘以系数,再放大10倍
		//将xxx.x转换为xxxx,以便发送数据管显示
		//下面公式中:314.0/2.0(或222.0/1.41)为被测电压与送往LM258的电压比值
		AC_Volt = sqrt( AC_Volt / 40.0) * 314.0 / 2.0 * 10; 
		avg_AC_Volt += AC_Volt;			//取得20趟交流电压值的和
	}
	avg_AC_Volt /= 20.0;				//计算20趟转换的平均交流电压值
}
//-----------------------------------------------------------------
// 串行输出到595驱动数码管显示
//-----------------------------------------------------------------
void Output_To_595_Display() {
	//将数字段码字节串行输入595
	Serial_Input_595(SEG_CODE[digit[3]]);
	Serial_Input_595(SEG_CODE[digit[2]] & 0x7F);
	Serial_Input_595(SEG_CODE[digit[1]]);
	Serial_Input_595(SEG_CODE[digit[0]]);
	//595移位寄存数据传输到存储寄存器并出现在输出端
	Parallel_Output_595();
}
//------------------------------------------------------------------
// 主程序
//------------------------------------------------------------------
void main() {
	P0M1 = 0x00; P0M0 = 0x00;			//配置为准双向口
	P3M1 = 0x00; P3M0 = 0x00;
	while (1) {
		get_AC_Voltage();				//检测交流电压
		DEC_TO_4DIGIT(avg_AC_Volt,digit);//分解为4个数位存入缓冲
		Output_To_595_Display();		//串行输出到595驱动数码管显示
	}
}