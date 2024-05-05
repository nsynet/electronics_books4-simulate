//------------------------- main.c --------------------------------
//	名称: GSM模块应用测试
//-----------------------------------------------------------------
//	说明：本例运行时,STC15向GSM模块发送AT测试命令，模板返回系列状态
//        信息在OLED屏刷新显示.
//-----------------------------------------------------------------
#include "STC15xxx.h"
#include "stdlib.h"
#include "stdio.h"
#include "math.h"
#include "string.h"
#include "oled.h"
#include "delay.h"
#include "gsm_uart.h"
//-----------------------------------------------------------------
extern xdata u8 Uart_Buffer[]; char s[20];
//-----------------------------------------------------------------
// 函数声明
//-----------------------------------------------------------------
void Timer0Init();						//定时器0初始化
void CheckGSMComm();					//检查GSM串口是否连接
void ClearUartBuffer();					//清除串口2接收缓存
char* FindATCommand(u8 *);				//查找字符串
u8 Send_ATCommand(u8 *,u8 *,u8,u8);	//发送AT指令函数
int ReadCSQ();							//读取信息强度
//-----------------------------------------------------------------
// Timer0定时器初始化
//-----------------------------------------------------------------
void Timer0Init() {


}
//-----------------------------------------------------------------
// 主循环
//-----------------------------------------------------------------
void main() {
	char *ps;
	P0M1 = 0x00; P0M0 = 0x00;			//P0,P2,P3配置为准双向口
	P2M1 = 0x00; P2M0 = 0x00;
	P3M1 = 0x00; P3M0 = 0x00;
	OLED_Init();						//初始化OLED
	OLED_Clear();						//清屏
	Uart1Init();						//串口初始化
	Uart2Init();						//串口初始化
	Timer0Init();						//T0初始化
	EA = 1;								//开总中断
	OLED_Clear();
	//OLED_ShowStr参数1:起始列,参数2:起始页,参数3:字体/字号（相对值）
	OLED_ShowStr( 6,0,"GSM MODULE TEST",16);
	OLED_ShowStr( 5,2,"---------------",12);
	OLED_ShowStr( 6,3,"Connect COM ...",12);
	//---------------------------------------------------------------
	//1.发送AT命令检查GSM模块串口是否连接正常 
	if (Send_ATCommand("AT","OK",3,10)) {

	
	}
	else OLED_ShowStr( 6,3,"GSM COM ERR!   ",12);
	//---------------------------------------------------------------
	OLED_ShowStr( 6,4,"AT+CSQ :",12);
	//2.发送AT命令检查GSM模块信号质量
	if (Send_ATCommand("AT+CSQ","\x0A",3,10)) {

	
	}
	else OLED_ShowStr( 68,5,"ERR!          ",12);
	//---------------------------------------------------------------
	//3.发送AT命令读取GSM模块IMEI序列号
	OLED_ShowStr( 6,5,"AT+CGSN:",12);
	if (Send_ATCommand("AT+CGSN","+CGSN",3,10)) {

	
	}
	else OLED_ShowStr( 68,5,"ERR!   ",12);
	//---------------------------------------------------------------
	//4.发送AT命令读取GSM模块标识
	OLED_ShowStr( 6,6,"AT+CGMM:",12);
	if (Send_ATCommand("AT+CGMM","\x0A",3,10)) {

	
	}
	else OLED_ShowStr( 68,6,"ERR!   ",12);
	//---------------------------------------------------------------
	//5.发送AT命令读取GSM模块状态
	OLED_ShowStr( 6,7,"AT+CPIN:",12);
	if (Send_ATCommand("AT+CPIN?","\x0A",3,10)) {

	
	}
	else OLED_ShowStr( 68,7,"ERR!   ",12);
	while(1);
}
//-----------------------------------------------------------------
// 读取信号强度(格式: +CSQ:**,## )
//-----------------------------------------------------------------
int ReadCSQ() {
	char *p_char1 = strchr((char *)(Uart_Buffer),':');
	char *p_char2 = strchr((char *)(Uart_Buffer),',');
	if (p_char1 != NULL && p_char2 != NULL) {
		*p_char2 = '\0';
		return atoi(p_char1+1);
	} else return 0;
}
