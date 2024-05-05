//---------------------------- 接收端程序 -------------------------------
//  名称: 红外遥控器接收程序
//---------------------------------------------------------------------
//  说明: 程序运行时,根据NEC红外协议接收数据并解码,然后将其以16进制数形式
//        显示LCD上.
//  
//---------------------------------------------------------------------
#include "STC15xxx.h"
#include <string.h>
#include <intrins.h>
#include <stdio.h>
#define u8  unsigned char
#define u16 unsigned int
extern void Initialize_LCD();
extern void LCD_ShowString(u8,u8,u8 *);
#define MAIN_Fosc 12000000L		//系统时钟频率
#define T0Ticks	 10000			//T0中断频率,10000次/秒,取值4000~16000
//#define T0Value	 (65536UL-((MAIN_Fosc+T0Ticks/2)/T0Ticks))
#define T0Value	 (65536UL-MAIN_Fosc/T0Ticks)	//定时初值
sbit IrPin = P2^0;				//红外接收引脚
volatile u8 F_IR_Sync_OK;		//IR头部同步信号接收成功
volatile u8 F_IR_RecOK;			//IR编码接收成功
volatile u8 F_T01ms;			//1ms标志
u8 Disp_Buffer[17];				//LCD显示缓冲
u8 IR_Data_Temp;				//数据临时存储
//正在接收的4字节红外编码
u8 IR_Bytes_Temp[] = {0x00,0x00,0x00,0x00}; 
//放入显示缓冲的4字节红外编码
u8 IR_Bytes_Disp[] = {0x00,0x00,0x00,0x00}; 
u8 _IrPin;						//前次IR采样电平
u8 T0Cnt_1ms;					//T0定时器1ms计时计数值
u8 IR_SampleCnt;				//采样计数
u8 IR_BitCnt;					//编码位数
//---------------------------------------------------------------------
// T0定时器初始配置:1T/16位/自动重装模式@12M
//---------------------------------------------------------------------
void Timer0Init() {


}
//---------------------------------------------------------------------
// 主程序
//---------------------------------------------------------------------
void main() {
	P0M1 = 0; P0M0 = 0;			//设置为准双向口
	P1M1 = 0; P1M0 = 0;
	P2M1 = 0; P2M0 = 0;
	T0Cnt_1ms = T0Ticks / 1000;//1ms计时变量
	Timer0Init();				//定时器初始化
	EA = 1;						//使能总中断
	Initialize_LCD();			//LCD初始化
	LCD_ShowString(0,0,"IR RemoteControl");
	LCD_ShowString(1,0,"--->CODE:");
	//本例定义的发射端发送来的编码为下列之一:
	//0x509A,0x3341,0x55A6,0x7378,0xB9AA,0xFDCC,0xDE1E,0xA1AC
	while (1) {

	
	}
}
//---------------------------------------------------------------------
// 单帧:同步,地址字节,地址反码,命令字节,命令反码(共32位)
// 同步:低9ms高4.5ms 1:560us载波+低电平=2.25ms,0:560us载波+低电平=1.12ms
// 1:L=0.5626ms,H=1.6879ms(共2.25ms) 0:L=0.5626ms,H=0.5626ms,(共1.12ms)
// 其中:38KHz载波(包括560us/0.5625ms载波)都将被接收头解析为低电平,载波
// 后的各低电平区均会被接收端解调为高电平
//---------------------------------------------------------------------
// IR相关定义
//---------------------------------------------------------------------
//定义采样时间, 红外接收要求在60us~250us之间
#define IR_SAMPLE_TIME  (1000000UL/T0Ticks) 
#if ((IR_SAMPLE_TIME <= 250) && (IR_SAMPLE_TIME >= 60))
  #define D_IR_sample IR_SAMPLE_TIME 
#endif
//---------------------------------------------------------------------
#define D_IR_SYNC_MIN	(9000 /D_IR_sample)	//头部同步时间最小值
#define D_IR_SYNC_MID	(11250/D_IR_sample)	//头部同步时间中间值
#define D_IR_SYNC_MAX	(13500/D_IR_sample)	//头部同步时间最大值
//---------------------------------------------------------------------
#define D_IR_DATA_MIN	(600  /D_IR_sample)	//数据时间最小值
#define D_IR_DATA_MID	(1500 /D_IR_sample)	//数据时间中间值
#define D_IR_DATA_MAX	(2400 /D_IR_sample)	//数据时间最大值
//---------------------------------------------------------------------
#define D_IR_BIT_NUMBER	32			//待接收数据位数
//---------------------------------------------------------------------
void IR_RX_NEC() {
	u8 SampleTime;					//相邻下降沿间的采样计数（计时）变量
	IR_SampleCnt++;					//采样计数变量累加（每次表示100us）
	F0 = _IrPin;					//保存前次采样状态
	_IrPin = IrPin;					//读取当前红外接收引脚电平状态
	if(F0 && !_IrPin) {				//遇下降沿，表示一次采样完成，开始解析
		SampleTime = IR_SampleCnt;	//保存采样计数值
		IR_SampleCnt = 0;			//采样计数值清0
		//1.采样时间超过最大头部同步时间,不作任何处理
		if(SampleTime > D_IR_SYNC_MAX) F_IR_Sync_OK = 0; //同步错误
		//2.采样时间超过最小头部同步时间
		else if(SampleTime >= D_IR_SYNC_MIN) {
			if(SampleTime >= D_IR_SYNC_MID) {	//采样时间超过中间区分值
				F_IR_Sync_OK = 1;	//正常接收到同步
				IR_BitCnt = D_IR_BIT_NUMBER;	//后续待接收总位数初值(32)
			}
		}
		//3.头部同步正常,进入IR编码比特位解析部分
		else if(F_IR_Sync_OK){
			if(SampleTime > D_IR_DATA_MAX) F_IR_Sync_OK=0;//超时同步错误
			else {								//否则开始处理逻辑1、0
				--IR_BitCnt;					//待接收位数递减
				IR_Data_Temp >>= 1;				//数据暂存变量右移1位
				//数据采样时间超过中间值表示接收到1,低位优先,否则不或1(默认或0)
				if(SampleTime >= D_IR_DATA_MID) IR_Data_Temp |= 0x80;
				//接收到8位(1字节)
				if((IR_BitCnt & 0x07) == 0x00) {
					//将新接收到的8位(1字节)保存到IR_Bytes_Temp[0]~[3]
					IR_Bytes_Temp[3-(IR_BitCnt>>3)] = IR_Data_Temp;
				}
				if(IR_BitCnt == 0) {	//IR_BitCnt为0表示32位全部完成
					F_IR_Sync_OK = 0;			//清除同步OK标志
					if (F_IR_RecOK == 0) {		//IR数据复制到待显示数组
						IR_Bytes_Disp[0] = IR_Bytes_Temp[0];
						IR_Bytes_Disp[1] = IR_Bytes_Temp[1];
						IR_Bytes_Disp[2] = IR_Bytes_Temp[2];
						IR_Bytes_Disp[3] = IR_Bytes_Temp[3];
						F_IR_RecOK = 1;			//置数据有效标志
					}
				}
			}
		}
	}
}
//---------------------------------------------------------------------
// T0中断处理红外接收与解码操作(在1T下运行,触发周期为100us)
//---------------------------------------------------------------------
void timer0() interrupt 1 {
	IR_RX_NEC();			//对红外解调后的信号进行解码
	if(--T0Cnt_1ms == 0) {	//计时达1ms则刷新一次显示（由主程序控制）
		T0Cnt_1ms = T0Ticks / 1000;
		F_T01ms = 1;		//1ms标志
	}
}