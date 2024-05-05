//-----------------------------------------------------------------
//  名称: 带日历时钟及温度显示的电子万年历
//-----------------------------------------------------------------
//  说明: 本例使用了DS1302读取日期时间,用TC72获取温度数据
//        通过74HC595驱动数码管显示.
//
//-----------------------------------------------------------------
#include "STC15xxx.h"
#include <intrins.h>
#include <stdio.h>
#include <string.h>
#define u8  unsigned char
#define u16 unsigned int
const u8 SEG_CODE[] = {	//0~9的段码,摄氏度(2字节),黑屏及”-”的段码
 0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,
 0xF8,0x80,0x90,0xC6,0x9C,0xFF,0xBF };
sbit DS		= P3^0;		//串行数据输入
sbit SH_CP	= P3^1;		//移位时钟脉冲
sbit ST_CP	= P3^2;		//输出锁存器控制脉冲
extern void Init_DS1302();
extern void GetDateTime();
extern void SetDateTime();
extern u8 CurrDateTime[];
extern void Config_TC72();
extern float Read_TC72_Temperature();
//所有数码管的显示缓冲(年有高2位固定为20),最后2位固定为摄氏度段码索引
u8 disp_buff[21] = {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,11,10};
#define MAIN_Fosc 11059200L			//时钟频率定义
//-----------------------------------------------------------------
// 延时函数(参数取值限于1~255)
//-----------------------------------------------------------------
void delay_ms(u8 ms) {
	u16 i;
	do{
		i = MAIN_Fosc / 13000;
		while(--i);
	}while(--ms);
}
//-----------------------------------------------------------------
// 1字节数据串行输入595子程序
//-----------------------------------------------------------------
void Serial_Input_595(u8 d) {

}
//-----------------------------------------------------------------
// 595并行输出子程序
//-----------------------------------------------------------------
void Parallel_Output_595() {

}
//------------------------------------------------------------------
// T0初始化配置（12T/16位自动重装模式，50毫秒@11.0592MHz）
//------------------------------------------------------------------
void Timer0Init() {

}
//------------------------------------------------------------------
// 主程序
//------------------------------------------------------------------
void main() { 
	u8 i,j, len; char t_buff[6],c; u8 curr_second = 0xFF;
	P0M1 = 0x00; P0M0 = 0x00;		//配置为准双向口
	P2M1 = 0x00; P2M0 = 0x00;
	P3M1 = 0x00; P3M0 = 0x00;
	Timer0Init();					//T0初始化配置
	IE = 0x82;						//允许T0中断
	Init_DS1302();
	while(1) {						//循环读取温度并显示
		//---------------------------------------------------------
		GetDateTime();				//从DS1302读取日期时间数据
		//分解到显示数据缓冲区
		disp_buff[2]	= CurrDateTime[6]>>4;	//年的后2位
		disp_buff[3]	= CurrDateTime[6]&0x0F;	
		disp_buff[4]	= CurrDateTime[4]>>4;	//月
		disp_buff[5]	= CurrDateTime[4]&0x0F;
		disp_buff[6]	= CurrDateTime[3]>>4;	//日
		disp_buff[7]	= CurrDateTime[3]&0x0F;
		disp_buff[8]	= CurrDateTime[2]>>4;	//时
		disp_buff[9]	= CurrDateTime[2]&0x0F;
		disp_buff[10]	= CurrDateTime[1]>>4;	//分
		disp_buff[11]	= CurrDateTime[1]&0x0F;
		disp_buff[12]	= CurrDateTime[0]>>4;	//秒
		disp_buff[13]	= CurrDateTime[0]&0x0F;
		disp_buff[14]	= CurrDateTime[5] - 1;	//星期
		//---------------------------------------------------------
		//清空温度数据显示缓冲(设为黑屏)
		for (i = 15; i < 18; i++) disp_buff[i] = 12;
		Config_TC72();							//配置TC72
		//读取温度浮点值并转换为浮点字符串
		sprintf(t_buff, "%5.1f", Read_TC72_Temperature());
		i = j = 0; len = strlen(t_buff);
		for (i = len - 1; i != 0xFF; i--) {	//逆序处理浮点温度字符
			//如果遇到小数点则跳过,因为小数点附加在个位数数码管上
			c = t_buff[i]; if (c == '.') continue;
			//处理数字字符及符号位(其中13为"-"的段码索引)
			if (c >= '0' && c <= '9')	disp_buff[18 - j] = c - '0';
			else if (c == '-')			disp_buff[18 - j] = 13 ;
			j++;
		}
		//发送所有待显示数据（第17位附加小数点）
		for (i = 20; i != 0xFF; i--) {
			if (i != 17) Serial_Input_595(SEG_CODE[disp_buff[i]]);
			else Serial_Input_595(SEG_CODE[disp_buff[i]] & 0x7F);
		}
		//595移位寄存器数据传输到存储寄存器并出现在输出端
		Parallel_Output_595();
		//控制秒闪功能(读取秒变化则开LED并启动定时,500ms后由溢出中断关LED)
		if (curr_second != CurrDateTime[0]) {
			curr_second = CurrDateTime[0];
			if (TR0 == 0) P2 &= 0xFC; TR0 = 1;
		}
	}
}
//-----------------------------------------------------------------
// T0中断函数(控制秒闪烁,每隔500ms关闭LED,开LED由主程序控制)
//-----------------------------------------------------------------
void LED_Flash() interrupt 1 {

}