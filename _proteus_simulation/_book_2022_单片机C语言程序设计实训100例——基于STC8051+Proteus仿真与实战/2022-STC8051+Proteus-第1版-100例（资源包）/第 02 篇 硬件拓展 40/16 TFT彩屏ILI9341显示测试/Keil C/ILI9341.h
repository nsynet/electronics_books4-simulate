//-------------------------- ILI9341.h ----------------------------
//  名称: TFT彩屏ILI9341驱动程序头文件
//-----------------------------------------------------------------
#ifndef		__ILI9341__
#define		__ILI9341__
#include "STC15xxx.h"
#include "ILI9341.h"
#include <intrins.h>
#define u8 	unsigned char
#define u16	unsigned int
//-----------------------------------------------------------------
// ILI9341引脚定义(SPI模式)
//-----------------------------------------------------------------
sbit LCD_CS		= P0^0;					//片选（使能）
sbit LCD_SCL	= P0^1;					//时钟线
sbit LCD_DC		= P0^2;					//数据命令（data/command）
sbit LCD_SDI	= P0^3;					//主机输出从机（LCD）输入
sbit LCD_SDO	= P0^4;					//主机输入从机（LCD）输出
sbit LCD_RST	= P0^5;					//复位线
//-----------------------------------------------------------------
#define ILI9341_TFTWIDTH		240		//TFT宽度
#define ILI9341_TFTHEIGHT		320		//TFT高度
//-----------------------------------------------------------------
#define ILI9341_NOP				0x00	//NOP命令
#define ILI9341_SWRESET			0x01	//软件复位
#define ILI9341_RDDID			0x04	//读显示ID
#define ILI9341_RDDST			0x09	//读显示状态
//-----------------------------------------------------------------
#define ILI9341_SLPIN 			0x10	//进入睡眠模式
#define ILI9341_SLPOUT			0x11	//退出睡眠模式
#define ILI9341_PTLON 			0x12	//局部模式开
#define ILI9341_NORON 			0x13	//打开正常显示模式
//-----------------------------------------------------------------
#define ILI9341_RDMODE  		0x0A	//读显示(电源)功耗模式
#define ILI9341_RDMADCTL		0x0B	//读显示MADCTL
#define ILI9341_RDPIXFMT		0x0C	//读显示像素格式
#define ILI9341_RDIMGFMT		0x0D	//读显示图像格式
#define ILI9341_RDSELFDIAG		0x0F	//读显示自诊断结果
//-----------------------------------------------------------------
#define ILI9341_INVOFF  		0x20	//关闭反转显示
#define ILI9341_INVON   		0x21	//开反转模式
#define ILI9341_GAMMASET		0x26	//伽马设置
#define ILI9341_DISPOFF 		0x28	//关显示
#define ILI9341_DISPON  		0x29	//开显示
//-----------------------------------------------------------------
#define ILI9341_CASET  			0x2A	//列地址设置
#define ILI9341_PASET  			0x2B	//页地址设置
#define ILI9341_RAMWR  			0x2C	//存储器写
#define ILI9341_RAMRD  			0x2E	//读存储器
//-----------------------------------------------------------------
#define ILI9341_PTLAR  			0x30	//局部区域
#define ILI9341_MADCTL 			0x36	//存储器访问控制
#define ILI9341_PIXFMT 			0x3A	//COLMOD：像素格式设置
//-----------------------------------------------------------------
#define ILI9341_FRMCTR1			0xB1	//帧速率控制1(正常/全色)
#define ILI9341_FRMCTR2			0xB2	//帧速率控制2(空闲/8色)
#define ILI9341_FRMCTR3			0xB3	//帧速率控制3(局部/全色)
#define ILI9341_INVCTR 			0xB4	//显示反转控制
#define ILI9341_DFUNCTR			0xB6	//显示功能控制
//-----------------------------------------------------------------
#define ILI9341_PWCTR1 			0xC0	//功耗控制1
#define ILI9341_PWCTR2 			0xC1	//功耗控制2
#define ILI9341_PWCTR3 			0xC2	//功耗控制3
#define ILI9341_PWCTR4 			0xC3	//功耗控制4
#define ILI9341_PWCTR5 			0xC4	//功耗控制5
#define ILI9341_VMCTR1 			0xC5	//VCOM控制1
#define ILI9341_VMCTR2 			0xC7	//VCOM控制2
//-----------------------------------------------------------------
#define ILI9341_RDID1  			0xDA	//读ID1
#define ILI9341_RDID2  			0xDB	//读ID2
#define ILI9341_RDID3  			0xDC	//读ID3
#define ILI9341_RDID4  			0xDD	//读ID4
//-----------------------------------------------------------------
#define ILI9341_GMCTRP1			0xE0	//正极伽马校准
#define ILI9341_GMCTRN1			0xE1	//负极伽马校准
//-----------------------------------------------------------------
// 颜色符号常量定义
#define ILI9341_BLACK     		0x0000	/*   0,   0,   0 */
#define ILI9341_NAVY      		0x000F	/*   0,   0, 128 */
#define ILI9341_DARKGREEN 		0x03E0	/*   0, 128,   0 */
#define ILI9341_DARKCYAN  		0x03EF	/*   0, 128, 128 */
#define ILI9341_MAROON    		0x7800	/* 128,   0,   0 */
#define ILI9341_PURPLE    		0x780F	/* 128,   0, 128 */
#define ILI9341_OLIVE     		0x7BE0	/* 128, 128,   0 */
#define ILI9341_LIGHTGREY 		0xC618	/* 192, 192, 192 */
#define ILI9341_DARKGREY  		0x7BEF	/* 128, 128, 128 */
#define ILI9341_BLUE      		0x001F	/*   0,   0, 255 */
#define ILI9341_GREEN     		0x07E0	/*   0, 255,   0 */
#define ILI9341_CYAN      		0x07FF	/*   0, 255, 255 */
#define ILI9341_RED       		0xF800	/* 255,   0,   0 */
#define ILI9341_MAGENTA   		0xF81F	/* 255,   0, 255 */
#define ILI9341_YELLOW    		0xFFE0	/* 255, 255,   0 */
#define ILI9341_WHITE     		0xFFFF	/* 255, 255, 255 */
#define ILI9341_ORANGE    		0xFD20	/* 255, 165,   0 */
#define ILI9341_GREENYELLOW		0xAFE5	/* 173, 255,  47 */
#define ILI9341_PINK			0xF81F
//-----------------------------------------------------------------
void delay_ms(u8 ms);
u8 SPI_WR(u8 dat);
void LCD_WR_DATA(u8 val);
void LCD_WR_REG(u8 reg);
void LCD_Init();
void LCD_Clear(u16 color);
void LCD_SetArea(u16 x0, u16 y0, u16 x1, u16 y1);
void drawPixel(int x, int y, u16 color);
void drawLine(int x0, int y0, int x1, int y1,u16 color);
void drawFastVLine(int x, int y,int h, u16 color);
void drawCircle(int x0, int y0, int r,u16 color);
void drawCircleHelper( int x0, int y0, int r, u8 cname, u16 color);
void fillCircle(int x0, int y0, int r, u16 color) ;
void fillCircleHelper(int x0, int y0, int r, u8 cname, int delt, u16 color);
void drawRect(int x, int y, int w, int h, u16 color);
void fillRect(int x, int y, int w, int h, u16 color);
void drawRoundRect(int x, int y, int w, int h, int r, u16 color);
void fillRoundRect(int x, int y, int w, int h, int r, u16 color);
void drawTriangle(int x0, int y0,int x1, int y1, int x2, int y2, u16 color) ;
void fillTriangle(int x0, int y0,int x1, int y1, int x2, int y2, u16 color);
void drawBitmap(int x, int y, const u8 *bitmap, int w, int h, u16 color);
void drawRGBBitmap(int x, int y, u16 *bitmap, int w, int h);
void drawChar(int x, int y, u8 c, u16 color, u16 bg, u8 sz);
void write(u8 c, u16 color, u16 bg, u8 sz);
void setCursor(int x, int y);
void DrawChineseString(u16 x, u16 y, u16 color, u16 bg, u8 *s, u16 count);
#endif