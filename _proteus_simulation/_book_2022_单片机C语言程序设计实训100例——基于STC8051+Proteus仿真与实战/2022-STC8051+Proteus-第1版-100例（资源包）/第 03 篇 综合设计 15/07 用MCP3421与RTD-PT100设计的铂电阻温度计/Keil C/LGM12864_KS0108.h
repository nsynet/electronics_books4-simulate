//-----------------------------------------------------------------
//  名称: LGM12864液晶头文件
//-----------------------------------------------------------------
#define u8   unsigned char
#define u16  unsigned int
//LCD起始行/页/列指令定义
#define LCD_START_ROW	0xC0		//起始行
#define LCD_PAGE			0xB8		//页指令
#define LCD_COL				0x40		//列指令
//液晶控制引脚
sbit E 	=  P3^0;							//使能控制线
sbit R_W = P3^1;							//读写控制线
sbit D_I = P3^2;							//数据/指令选择线
sbit CS1 = P3^3;							//右半屏选择
sbit CS2 = P3^4;							//右半屏选择
sbit RST = P3^5;							//复位
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
void LCD_Write_Command(u8 cmd);
void LCD_Write_Data(u8 dat);
void Common_Show(u8 P,u8 L,u8 W,u8 *r);
void Display_A_Char_8X16(u8 P,u8 L,u8 *M);
void Display_A_WORD(u8 P,u8 L,u8 *M);
void Display_A_WORD_String(u8 P,u8 L,u8 C,u8 *M);