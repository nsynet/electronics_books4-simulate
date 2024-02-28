//---------------------------- PCF8583.h --------------------------
// 名称: PCF8583实时时钟程序头文件
//-----------------------------------------------------------------
#ifndef __PCF8583_H__	//条件编译语句,防止此头文件被重复包含
#define __PCF8583_H__
//PCF8583器件读/写操作地址
#define PCF8583_ADDR_RD 0xA1
#define PCF8583_ADDR_WR 0xA0
//函数声明
void Read_PCF8583(u8 addr,u8 *buf,u8 n);
void GetDateTime();	
#endif