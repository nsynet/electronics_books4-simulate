//-----------------------------------------------------------------
//	名称: SPI接口温度传感器TC72驱动程序
//-----------------------------------------------------------------
#include "STC15xxx.h"
#include <intrins.h>
#include <stdio.h>
#include <math.h>
#define u8	unsigned char
#define u16	unsigned int
//TC72寄存器地址定义
#define TC72_CTRL			0x80	//控制寄存器
#define TC72_TEMP_LSB	0x01	//温度低字节
#define TC72_TEMP_MSB	0x02	//温度高字节
#define TC72_MANU_ID	0x03	//制造商ID
//SPI接口引脚定义(模拟方式)
sbit SCK = P3^4;				//串行时钟控制脚
sbit CE  = P3^5;				//片选
sbit SDI  = P3^6;				//串行数据输入
sbit SDO  = P3^7;				//串行数据输出
u8 Temp_Value[2];				//两字节温度值原始数据
extern void delay_ms(u16 x);
//-----------------------------------------------------------------
// 从当前地址读取一字节数据(模拟方式)
//-----------------------------------------------------------------
u8 _ReadByte() {
	u8 i	,d = 0x00;
	for(i = 0; i < 8; i++)		//串行读取8位数据	
	{	//SCK下降沿读取数据,读取的位保存到左移以后的d的低位
		SCK = 1; SCK = 0; d = (d << 1) | SDO;
	}
	return d; 					//返回读取的字节
}
//-----------------------------------------------------------------
// 向当前地址写入一字节数据(模拟方式)
//-----------------------------------------------------------------
void _WriteByte(u8 dat) {
	u8 i;
	for(i = 0; i < 8; i++) {	//串行写入8位数据
		dat <<= 1; SDI = CY;		//dat左移位,高位被移入CY,发送高位
		SCK = 0; SCK = 1;				//时钟上升沿向存储器写入数据
	}
}
//-----------------------------------------------------------------
// 向TC72写入两字节(地址,数据)(模拟方式)
//-----------------------------------------------------------------
void Write_TC72(u8 addr, u8 dat) {
	CE = 1;									//SPI_EN();
	_WriteByte(addr);				//SPI_SendData(addr);
	_WriteByte(dat); 				//SPI_SendData(dat);
	CE = 0;									//SPI_DI();
}
//-----------------------------------------------------------------
// 写TC72配置数据
//-----------------------------------------------------------------
void Config_TC72() {
	Write_TC72(TC72_CTRL,0x15);	//配置为单次转换与关断模式
}
//-----------------------------------------------------------------
// 从TC72读取两字节温度数据并转换为浮点温度值
//-----------------------------------------------------------------
float Read_TC72_Temperature() {
	Config_TC72();
	delay_ms(50);
	CE = 1;						//SPI_EN();
	//发送读温度高字节命令
	_WriteByte(TC72_TEMP_MSB);	//SPI_SendData(TC72_TEMP_MSB);
	//连续读取两字节(连续读取时先得到的是高字节,后得到的是低字节)
	Temp_Value[1] = _ReadByte();	//SPI_SendData(0xFF);//读高字节
	Temp_Value[0] = _ReadByte();	//SPI_SendData(0xFF);//读低字节
	CE = 0;						//SPI_DI();
	//还可以使用以下单字节读取的方法
	//SPI_EN();
	//SPI_SendData(TC72_TEMP_LSB);	//发送读温度低字节命令
	//T[0] = SPI_SendData(0xFF);	//读LSB
	//SPI_DI();
	//SPI_EN();
	//SPI_SendData(TC72_TEMP_MSB);	//发送读温度高字节命令
	//T[1] = SPI_SendData(0xFF);	//读MSB
	//SPI_DI();
	return (int)(((int)((Temp_Value[1]<<8)|Temp_Value[0]))>>6) * 0.25;
}
