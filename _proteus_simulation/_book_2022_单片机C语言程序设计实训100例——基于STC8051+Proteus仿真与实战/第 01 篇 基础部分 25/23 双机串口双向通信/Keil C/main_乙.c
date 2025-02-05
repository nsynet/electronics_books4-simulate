//---------------------------	乙机代码	----------------------------
//	名称: 乙机程序接收甲机发送的字符并完成相应动作
//-----------------------------------------------------------------
//	说明: 乙机接收到甲机发送的信号后,根据相应信号控制完成不同的LED点亮动作.
//	 
//-----------------------------------------------------------------
#include "STC15xxx.h"
#include <intrins.h>
#define u8 	unsigned char
#define u16	unsigned int
#define MAIN_Fosc 11059200L		//系统时钟
sbit LED1	= P0^0;				//两个LED定义
sbit LED2	= P0^3;
sbit K1 	= P0^7;				//按键定义
u8 NumX = 0xFF;					//待发送数字（0~10）
volatile u8 recv_byte = 0x00;	//接收到的字节
bit B_TX1_Busy;					//串口1发送忙标志
//-----------------------------------------------------------------
// 延时函数（x = 1~255ms,自适应时钟）
//-----------------------------------------------------------------
void delay_ms(u8 x) {
	u16 i;
	do{
		i = MAIN_Fosc / 13000;
		while(--i);
	}while(--x);
}
//-----------------------------------------------------------------
// 初始化串口(9600bps@11.0592MHz)
//-----------------------------------------------------------------
void UartInit() {


}
//-----------------------------------------------------------------
// 主程序 
//-----------------------------------------------------------------
void main() {
	P0M1 = 0x80; P0M0 = 0x00;	//P0.7为输入,P0其余为准双向口
	P3M1 = 0x00; P3M0 = 0x00;	//P3配置为准双向口

	
	
}
//-----------------------------------------------------------------
// 乙机串口接收中断函数 
//-----------------------------------------------------------------
void Serial_INT() interrupt 4 {
	if (RI) {	//如果收到命令字符则完成不同的LED点亮动作 

	
	
	}
	if (TI) {	//发送中断标记位被硬件置位

	
	
	}
}