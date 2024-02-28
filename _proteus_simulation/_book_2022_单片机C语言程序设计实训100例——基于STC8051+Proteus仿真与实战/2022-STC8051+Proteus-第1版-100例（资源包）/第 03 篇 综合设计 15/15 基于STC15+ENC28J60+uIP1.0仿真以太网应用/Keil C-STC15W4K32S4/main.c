//------------------------- main.c ---------------------------------
//  名称: 基于STC+ENC28J60+uIP 1.0的仿真以太网应用
//-----------------------------------------------------------------
//  说明: 仿真电路基于STC14W4K32S4与以太网接口芯片ENC28J60设计，移植了
//        uIP 1.0协议栈，系统运行时，C#客户端程序可通过以太网与STC仿真
//        电路交互，读取A/D转换结果并在窗体中以图形方式显示，同时还将
//        读取并显示仿真电路中SW_PORT_4开关位置,在C#程序中点击鼠标还可
//        远程控制仿真电路中的继电器开关、LED显示切换等。
//
//-----------------------------------------------------------------
#include "STC15xxx.h"
#include "My_Macro.h"				//宏定义头文件
#include "delay.h"					//延时函数头文件
#include "uip.h"					//uIP TCP/IP 
#include "uip_arp.h"				//ARP模块宏定义
#include "timer.h"					//定时器头文件
#include "uart.h"					//串口头文件
#include "enc28j60.h"				//enc28j60驱动程序头文件
#include "app_server.h"				//应用服务头文件
#include "myopt.h"					//自定义选项头文件
#include "spi.h"					//SPI接口头文件
#include <intrins.h>
#include <stdio.h>
#include <stdlib.h>
//IP包缓冲定义，将通用缓冲强制转换为以太网包头uip_eth_hdr以便解析IP
#define BUF ((struct uip_eth_hdr *)&uip_buf[0])
#ifndef NULL
#define NULL (void *)0
#endif /* NULL */
clock_time_t tick_cnt;				//TICK计时变量（处理TCP连接和ARP更新）
u16 clock_j = 0;
clock_time_t clock_time(void) {		//返回TICK计时变量值
	return tick_cnt;
}
extern void Timer0Init();			//T0定时器初始化函数
//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------
void main() {
/******************************************************
	
	
	
	
	
	
	
	
	*****************************************************/
}
