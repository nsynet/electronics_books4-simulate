//-----------------------------------------------------------------
//  名称: SPI接口数字电位器MCP41010应用
//-----------------------------------------------------------------
//  说明: 使用两路兼容SPI接口的数字电位器MCP41010，通过K1,K2分别
//        对通道0电位进行递增/递减调节，K3,K4分别对通道1电位进行
//        递增/递减调节.
//
//-----------------------------------------------------------------
#define u8 	unsigned char
#define u16	unsigned int
#define u32	unsigned long
#include "STC15xxx.h"
#include <intrins.h>
#include <string.h>
#include <stdio.h>
//器件SPI接口引脚定义
sbit SCK = P0^0;			//SPI时钟线
sbit MOSI = P0^1;			//SPI数据线(主机输出从机输入)
sbit CS0 = P0^2;			//SPI使能0
sbit CS1 = P0^3;			//SPI使能1
//-----------------------------------------------------------------
sbit K1 = P2^0;				//通道0递增
sbit K2 = P2^2;				//通道0递减
sbit K3 = P2^4;				//通道1递增
sbit K4 = P2^6;				//通道1递减
//-----------------------------------------------------------------
// 延时子程序（x=1~255ms,自适应时钟）
//-----------------------------------------------------------------
#define MAIN_Fosc 11059200L
void delay_ms(u8 x) {
	u16 i;
	do{
		i = MAIN_Fosc / 13000; while(--i);
	} while(--x);
}
//-----------------------------------------------------------------
// 向SPI总线写字节 
//-----------------------------------------------------------------
void WriteByte(u8 d) {
 
}
//-----------------------------------------------------------------
// 向SPI总线发送数据(指定通道与待输出字节) 
//-----------------------------------------------------------------
void SendData(u8 ch, u8 d) {

}
//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------
void main(){
	u8 i = 0; 
	u8 CH0_Dat = 0x00, CH1_Dat = 0x00;		//两个通道初值
	P0M1 = 0x00; P0M0 = 0x00;				//P0配置为准双向口
	P2M1 = 0xFF; P2M0 = 0x00;				//P2配置为高阻输入
	SCK = 1;									//初始空闲时置时钟线为高电平
	SendData(0,0x00); SendData(1,0x00);	//两通道初始时均设为0V
	while (1) {
		if (K1 == 0) {						//通道0递增调节

		}
		if (K2 == 0) {						//通道0递减调节

		}
		if (K3 == 0) {						//通道1递增调节

		}
		if (K4 == 0) {						//通道1递减调节

		}
	}
}