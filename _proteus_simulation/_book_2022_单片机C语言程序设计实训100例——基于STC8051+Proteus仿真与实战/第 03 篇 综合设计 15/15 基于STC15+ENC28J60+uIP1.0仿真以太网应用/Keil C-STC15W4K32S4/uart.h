//-----------------------------------------------------------------
// 名称: 串口驱动程序头文件
//-----------------------------------------------------------------
#ifndef __UART_H__
#define __UART_H__

#include "My_Macro.h"
void UartInit();					//串口初始化
void Printf_Char(u8 ascii);
void Printf_String(u8  *string);
#endif