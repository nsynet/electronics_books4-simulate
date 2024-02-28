//------------------------- BMP180.h ------------------------------
// 名称：BMP180驱动程序头文件
//-----------------------------------------------------------------
#ifndef __BMP180__
#define __BMP180__
#define u8  unsigned char
#define u16 unsigned int
#define u32 unsigned long
#include "STC15xxx.h"
#include <intrins.h>
#include <stdio.h>
#define	BMP180_SlaveAddress		0xEE	//器件IIC从机地址
#define	OSS						0		//过采样设置
void Init_BMP180();
void BMP180_Start();
void BMP180_Stop();
void BMP180_SendACK(bit ack);
bit  BMP180_RecvACK();
void BMP180_SendByte(u8 dat);
u8 BMP180_RecvByte();
void BMP180Convert();
void conversion(long);
extern void DisplayOneChar(u8 r, u8 c, char d);
#endif