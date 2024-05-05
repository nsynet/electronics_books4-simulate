//---------------------------- main.c -----------------------------
//  名称: SD卡FAT32文件系统读写测试 (基于znFAT)
//-----------------------------------------------------------------
//  说明: 程序运行时，读取1路按键输入状态和1路AD输入采样值，然后分别
//        写入2个不同文件，其中按键输入采样保存于/mycount.txt，AD转换
//        值保存于/data/myadc.txt。按下K1，K2时将分别显示两个
//        文件所保存的内容。
// 编译说明：Memory Model：Large 64K Model
//-----------------------------------------------------------------
#include <stdio.h>
#include <string.h>
#include "fat/FAT.h"
#include "sd.h"
#include "uart.h"
#include "ds1302.h"
//-----------------------------------------------------------------
#define ADC_POWER 		0x80			//ADC电源控制位
#define ADC_FLAG 			0x10			//ADC完成标志
#define ADC_START 		0x08			//ADC起始控制位
#define ADC_SPEEDLL		0x00			//540个时钟
#define ADC_SPEEDL 		0x20			//360个时钟
#define ADC_SPEEDH 		0x40			//180个时钟
#define ADC_SPEEDHH		0x60			//90个时钟
//-----------------------------------------------------------------
struct FATInfo	idata SDInfo;			//初始化参数集合
struct DateTime	idata dt;				//日期与时间
struct FileInfo	idata file1;			//文件信息
struct FileInfo	idata file2;			//文件信息
//-----------------------------------------------------------------
sbit S1 = P3^4;							//启动时删除原始文件切控制开关
sbit K1 = P3^6;							//读取SD卡ADC数据并显示
sbit K2 = P3^7;							//读取SD卡按键计数数据并显示
sbit LED0 = P2^0;						//AD输入转换指示灯
sbit LED1 = P2^3;						//按键计数输入指示灯
sbit LED2 = P2^6;						//SD卡读写访问指示灯
volatile bit sLED0 = 0,sLED1 = 0,sLED2 = 0;//三个指示灯显示控制标识
u16 res,res1,res2;						//SD卡及文件操作返回码
//-----------------------------------------------------------------
void InitADC();
u16 GetADCResult(u8 ch);
void Timer0Init();
u32 WriteTextString(struct FileInfo *pf,char *s);
extern void delay_ms(u8);
extern void GetDateTime() ;
extern u8 DateTime[7];
//-----------------------------------------------------------------
int	preKeyCount = 0,KeyCount = 0;		//计数变量初始值
char	KeyStrBuff[10];					//按键计数字符串转换缓冲
u16		ADC_Value = 0x0000;
u8		ADCStrBuff[20];					//AD值字符串转换缓冲
int		ADC_Voltage;					//放大100倍的电压值（以便分解）
u8		ReadBuff[513];
//-----------------------------------------------------------------
// STC端口、定时器、串口、ADC等初始化
//-----------------------------------------------------------------
void InitSTC() {
	
	
	
	
}
//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------
void main() {
	u32 i = 0, j = 0, k = 0, len = 0;
	InitSTC();
	UART_Send_Str("串口初始化完成.\r\a");
	sLED2 = 1;
	FAT_Device_Init();					//存储设备初始化
	UART_Send_Str("SD卡初始化完成.\r\a");
	FAT_Select_Device(0, &SDInfo);		//选择设备
	UART_Send_Str("开始初始化文件系统...\r\a");
	res = FAT_Init();					//文件系统初始化
	if (!res){							//文件系统初始化成功
		UART_Send_Str("文件系统初始化成功.\r\n");
		UART_Send_StrNum("BPB扇区号:\t",	SDInfo.BPB_Sector_No);
		UART_Send_StrNum("SD卡总容量:\t",	SDInfo.Total_SizeKB);
		UART_Send_StrNum("每扇区字节:\t",	SDInfo.BytesPerSector);
		UART_Send_StrNum("FAT占用扇区:\t",	SDInfo.FATsectors);
		UART_Send_StrNum("每簇扇区数:\t",	SDInfo.SectorsPerClust);
		UART_Send_StrNum("FAT所在扇区:\t",	SDInfo.FirstFATSector);
		UART_Send_StrNum("第一个目录所在扇区:\t",SDInfo.FirstDirSector);
		UART_Send_StrNum("文件系统扇区号:\t",SDInfo.FSINFO_Sec);
		UART_Send_StrNum("下一可簇号:\t",	SDInfo.Next_Free_Cluster);
		UART_Send_StrNum("可用簇个数:\t",	SDInfo.Free_nCluster);
	}
	else {	//文件系统初始化失败
		UART_Send_StrNum("文件系统初始化失败，返回码:\t", res);
	}
	//-------------------------------------------------------------
	//如果S1合上则删除两个初始文件并重建文件
	if (S1 == 0) {
		FAT_Delete_File("/mycount.txt");	//删除按键计数文件
		FAT_Delete_File("/data/myadc.txt");//删除AD转换数据文件
		GetDateTime();						//获取DS1302日期时间
		//设置文件日期时间属性
		dt.date.year	= 2000+DateTime[6];
		dt.date.month	= DateTime[4];
		dt.date.day 	= DateTime[3];
		dt.time.hour	= DateTime[2];
		dt.time.min		= DateTime[1];
		dt.time.sec		= DateTime[0];
		//创建目录（用于确保/data存在,data后面的斜杠不可省略）
		res = FAT_Create_Dir("/data/", &dt);
		//创建文件夹及相关文件
		res1 = FAT_Create_File(&file1, "/mycount.txt",		&dt);
		P6 = res1;
		res2 = FAT_Create_File(&file2, "/data/myadc.txt",	&dt);
		if (res1 || res2) goto Err;		//如果出错则直接退出
		KeyCount = 0;					//按键计数变量初值设为0
		//计数初值写入文本文件
		if (!WriteTextString(&file1,"0000")) goto Err;
	}
	//-------------------------------------------------------------
	//如果S1未合上则打开两个文件，并先从按键文件中读取计数初值
	else {
		res1 = FAT_Open_File(&file1, "/mycount.txt",	0, 1);
		res2 = FAT_Open_File(&file2, "/data/myadc.txt",0, 1);
		//从按键计数文件中读取按键计数初值
		len = FAT_ReadData(&file1,0,4,KeyStrBuff);
		//如果文件长度不是4字节，则表示文件被异常修改或已损坏
		//为规范化该文件，下面的代码先删除该文件，然后重建并写入"0000"
		if (len != 4) {
			FAT_Delete_File("/mycount.txt");
			res1 = FAT_Create_File(&file1, "/mycount.txt", &dt);
			if (res1 || !WriteTextString(&file1,"0000")) goto Err;
		} else {
			for (i = 0; i < 4 && i < len; i++) {
				if (KeyStrBuff[i] >= '0' && KeyStrBuff[i] <= '9') 
					KeyCount = KeyCount * 10 + KeyStrBuff[i] - '0';
				else break;
			}
		}
		FAT_Close_File(&file1);	//关闭文件
	}
	if (!res1) EX0 = 1;		//允许INT0中断，使能按键计数并写SD卡文件
	//-------------------------------------------------------
	if (res2) goto Err;		//file2异常则退出，否则开始AD转换与保存
	else {
		len = file2.File_Size;
		if (len >= 2) {
			//取文件最末尾两字节进行判断
			len = FAT_ReadData(&file2,len-2,2,ADCStrBuff);
			if (len == 2	&& ADCStrBuff[0] != 0x0D 
							&& ADCStrBuff[1] != 0x0A) {
				//在初始文件或上次文件末尾添加换行符与分隔线
				if (!WriteTextString(&file2,
					"\x0D\x0A-------------\x0D\x0A")) goto Err;
			}
		}
	}
	while (1) {
		//-------------------------------------------------------
		// 1.获取AD值（10位精度）并写SD卡文件
		//-------------------------------------------------------

		
		
		
		//-------------------------------------------------------
		// 2.写入按键输入计数值（输入与计数在INT0中断中完成）
		//-------------------------------------------------------

		
		
		
		//-------------------------------------------------------
		// 3.读取历史数据记录
		//-------------------------------------------------------

		
		
		
		
		//-------------------------------------------------------
		delay_ms(10);			//加快采集可调小延时，减慢采集可加在延时
		//-------------------------------------------------------
	}
	Err:
	sLED0 = 0; sLED1 = 0; sLED2 = 0; UART_Send_Str("文件访问失败!：");
	FAT_Flush_FS();				//刷新文件系统
	while (1) ;
}
//-----------------------------------------------------------------
// 写字符串到文本文件
//-----------------------------------------------------------------
u32 WriteTextString(struct FileInfo *pf,char *s) {
	u32 len = FAT_WriteData(pf, strlen(s), s); 
	if (len == ERR_OVER_FILE_MAX_SIZE || len == ERR_OVER_DISK_SPACE) {
		UART_Send_Str("AD转换值写SD卡文件出错!");
		return 0;
	} else return len;
}
//-----------------------------------------------------------------
// 初始化ADC
//-----------------------------------------------------------------
void InitADC() {
	P1ASF = 1<<1; 				//P1.1设为AD口
	ADC_RES = 0; 				//清除结果寄存器
	ADC_CONTR = ADC_POWER | ADC_SPEEDLL;
	delay_ms(2); 				//ADC上电并延时
}
//-----------------------------------------------------------------
// 读取指定通道ADC结果
//-----------------------------------------------------------------
u16 GetADCResult(u8 ch) {
	ADC_CONTR = ADC_POWER | ADC_SPEEDLL | ADC_START | ch;
	delay_ms(1);
	while (!(ADC_CONTR & ADC_FLAG));	//等待ADC转换完成
	ADC_CONTR &= ~ADC_FLAG; 			//关闭ADC
	return (ADC_RES<<2) | ADC_RESL;		//返回结果
}
//-----------------------------------------------------------------
// T0初始化(16位12T模式,20毫秒@22.1184MHz)
//-----------------------------------------------------------------
void Timer0Init() {
	AUXR &= 0x7F;				//定时器时钟12T模式
	TMOD &= 0xF0;				//设置定时器模式
	TL0 = 0x00;					//设置定时初值
	TH0 = 0x70;					//设置定时初值
	TF0 = 0;					//清除TF0标志
	TR0 = 1;					//定时器0开始计时
}
//-----------------------------------------------------------------
// T0中断函数(控制LED闪烁)
//-----------------------------------------------------------------
void LED_Flash() interrupt 1 {
	static u8 T0_Count = 0,T1_Count = 0,T2_Count = 0, Tx = 0;
	//2*20=40ms控制AD转换指示灯闪烁
	if (sLED0 && ++T0_Count == 2) {	
		LED0 ^= 1; 
		T0_Count = 0;
	} else LED0 = 1;
	//2*20=40ms控制按键指示灯闪烁
	if (sLED1 && ++T1_Count == 2) {
			LED1 ^= 1; 
			if (++Tx == 6) { sLED1 = 0; LED1 = 1; Tx = 0; }
			T1_Count = 0;
	} else LED1 = 1;
	//4*20=80ms控制SD读写访问指示灯闪烁
	if (sLED2 && ++T2_Count == 4) {	
		LED2 ^= 1; ;
		T2_Count = 0;
	} else LED2 = 1;
}
//-----------------------------------------------------------------
// INT0中断函数
//-----------------------------------------------------------------
void EX_INT0() interrupt 0 {
	if ((P3 & (1<<2)) == 0x00) {
		sLED1 = 1;				//按键输入指示允许闪烁
		//计数值递增(限制为0000~9999)
		if (++KeyCount > 9999) KeyCount = 0;
	}
}