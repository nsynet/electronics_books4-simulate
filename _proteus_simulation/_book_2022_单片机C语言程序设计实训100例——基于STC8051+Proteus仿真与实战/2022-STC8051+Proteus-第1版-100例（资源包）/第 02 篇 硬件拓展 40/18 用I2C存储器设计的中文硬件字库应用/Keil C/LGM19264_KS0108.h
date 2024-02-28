//-----------------------------------------------------------------
//  名称: LGM19264(KS0109)液晶头文件
//-----------------------------------------------------------------
#ifndef ___LGM19264_KS0108___
#define ___LGM19264_KS0108___
#define u8   unsigned char
#define u16  unsigned int
//LCD起始行/页/列指令定义
#define LCD_PAGE			0xB8		//页指令(X)
#define LCD_START_ROW	0xC0		//起始行(XF)
#define LCD_COL				0x40		//列指令(Y)
//液晶控制引脚
sbit D_I = P3^0;							//数据/指令选择线
sbit R_W = P3^1;							//读写控制线
sbit E 	=  P3^2;							//使能控制线
sbit CS1 = P3^3;							//与屏选择
sbit CS2 = P3^4;							//中屏选择
sbit CS3 = P3^5;							//右屏选择
sbit RST = P3^6;							//复位
//忙标志位
sbit BUSY_STATUS =	P0^7;			//忙标志位
//液晶端口
#define LCD_PORT  	P0				//液晶数据端口
//-----------------------------------------------------------------
// 函数声明
//-----------------------------------------------------------------
void LCD_Initialize();
void Wait_LCD_Ready();
void ClearScreen();
void LCD_Write_Comm(u8 cmd);
void LCD_Write_Data(u8 dat);
void Common_Show(u8 P,u8 L,u8 W,u8 *r);
void Disp_A_Char_8X16(u8 P,u8 L,u8 *M);
void Disp_A_WORD(u8 P,u8 L,u8 *M);
void Disp_CHN_String(u8 P,u8 L,u8 C,u8 *M);
void Disp_Image(u8 P,u8 L,u8 W,u8 H,u8* G); 
#endif