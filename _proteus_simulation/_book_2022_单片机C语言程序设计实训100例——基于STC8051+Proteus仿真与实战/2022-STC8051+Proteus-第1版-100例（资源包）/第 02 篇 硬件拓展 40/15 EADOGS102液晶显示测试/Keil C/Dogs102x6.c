//------------------------ Dogs102x6.c ----------------------------
//  名称：EADOGS102液晶驱动程序
//-----------------------------------------------------------------
#include "STC15xxx.h"
#include "Dogs102x6.h"
#include <intrins.h>
#ifndef abs
# define abs(n) (((n) < 0) ? -(n) : (n))
#endif
extern void delay_ms(u16);
//EADOGS命令集（CD须置为0）
#define SET_COLUMN_ADDRESS_MSB		0x10	//设置列地址高4位
#define SET_COLUMN_ADDRESS_LSB		0x00	//设置列地址低4位
#define SET_POWER_CONTROL			0x2F	//电源控制（开）
#define SET_SCROLL_LINE				0x40	//图像上滚（0～63）
#define SET_PAGE_ADDRESS			0xB0	//设置页地址（0～7）
#define SET_VLCD_RESISTOR_RATIO		0x27	//设置电阻率调节对比度
#define SET_ELECTRONIC_VOLUME_MSB	0x81	//设置对比度命令(第1字节)
#define SET_ELECTRONIC_VOLUME_LSB	0x0F	//设置对比度参数(第2字节)
#define SET_ALL_PIXEL_ON			0xA4	//禁止所有像素显示（不影响内存）
#define SET_INVERSE_DISPLAY			0xA6	//反相显示
#define SET_DISPLAY_ENABLE			0xAF	//使能显示
#define SET_SEG_DIRECTION 			0xA1	//段镜像显示
#define SET_COM_DIRECTION 			0xC8	//行镜像显示
#define SYSTEM_RESET				0xE2	//复位系统
#define NOP							0xE3	//无操作
#define SET_LCD_BIAS_RATIO			0xA2	//设置电压斜率
#define SET_CURSOR_UPDATE_MODE		0xE0	//列地址递增
#define RESET_CURSOR_UPDATE_MODE	0xEE	//从之前的光标位置移到列地址位置
#define SET_ADV_PROGRAM_CONTROL0_MSB	0xFA	//温度补偿命令(第1字节)
#define SET_ADV_PROGRAM_CONTROL0_LSB	0x90	//温度补偿参数(第2字节)
//-----------------------------------------------------------------
// EADOGS引脚定义
sbit SI	= P0^0;
sbit SCK= P0^1;
sbit CD	= P0^2;
sbit CS	= P0^3;
sbit RST= P0^4;
//-----------------------------------------------------------------
const u8 FONT6x8[] = { //ASCII字符字模
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // space
	0x00, 0x00, 0xFA, 0x00, 0x00, 0x00, // !
	0x00, 0xE0, 0x00, 0xE0, 0x00, 0x00, // "
	0x28, 0xFE, 0x28, 0xFE, 0x28, 0x00, // #
	0x24, 0x54, 0xFE, 0x54, 0x48, 0x00, // $
	0xC4, 0xC8, 0x10, 0x26, 0x46, 0x00, // %
	0x6C, 0x92, 0x6A, 0x04, 0x0A, 0x00, // &
	0x00, 0x10, 0xE0, 0xC0, 0x00, 0x00, // '
	0x00, 0x38, 0x44, 0x82, 0x00, 0x00, // (
	0x00, 0x82, 0x44, 0x38, 0x00, 0x00, // )
	0x54, 0x38, 0xFE, 0x38, 0x54, 0x00, // *
	0x10, 0x10, 0x7C, 0x10, 0x10, 0x00, // +
	0x00, 0x02, 0x1C, 0x18, 0x00, 0x00, // ,
	0x10, 0x10, 0x10, 0x10, 0x10, 0x00, // -
	0x00, 0x00, 0x06, 0x06, 0x00, 0x00, // .
	0x04, 0x08, 0x10, 0x20, 0x40, 0x00, // /
	//96字节
	0x7C, 0x8A, 0x92, 0xA2, 0x7C, 0x00, // 0
	0x00, 0x42, 0xFE, 0x02, 0x00, 0x00, // 1
	0x42, 0x86, 0x8A, 0x92, 0x62, 0x00, // 2
	0x84, 0x82, 0x92, 0xB2, 0xCC, 0x00, // 3
	0x18, 0x28, 0x48, 0xFE, 0x08, 0x00, // 4
	0xE4, 0xA2, 0xA2, 0xA2, 0x9C, 0x00, // 5
	0x3C, 0x52, 0x92, 0x92, 0x0C, 0x00, // 6
	0x82, 0x84, 0x88, 0x90, 0xE0, 0x00, // 7
	0x6C, 0x92, 0x92, 0x92, 0x6C, 0x00, // 8
	0x60, 0x92, 0x92, 0x94, 0x78, 0x00, // 9
	0x00, 0x00, 0x28, 0x00, 0x00, 0x00, // :
	0x00, 0x00, 0x02, 0x2C, 0x00, 0x00, // ;
	0x00, 0x10, 0x28, 0x44, 0x82, 0x00, // <
	0x28, 0x28, 0x28, 0x28, 0x28, 0x00, // =
	0x00, 0x82, 0x44, 0x28, 0x10, 0x00, // >
	0x40, 0x80, 0x8A, 0x90, 0x60, 0x00, // ?
	//96*2=192字节
	0x7C, 0x82, 0xBA, 0x9A, 0x72, 0x00, // @
	0x3E, 0x48, 0x88, 0x48, 0x3E, 0x00, // A
	0xFE, 0x92, 0x92, 0x92, 0x6C, 0x00, // B
	0x7C, 0x82, 0x82, 0x82, 0x44, 0x00, // C
	0xFE, 0x82, 0x82, 0x82, 0x7C, 0x00, // D
	0xFE, 0x92, 0x92, 0x92, 0x82, 0x00, // E
	0xFE, 0x90, 0x90, 0x90, 0x80, 0x00, // F
	0x7C, 0x82, 0x92, 0x92, 0x5E, 0x00, // G
	0xFE, 0x10, 0x10, 0x10, 0xFE, 0x00, // H
	0x00, 0x82, 0xFE, 0x82, 0x00, 0x00, // I
	0x04, 0x02, 0x82, 0xFC, 0x80, 0x00, // J
	0xFE, 0x10, 0x28, 0x44, 0x82, 0x00, // K
	0xFE, 0x02, 0x02, 0x02, 0x02, 0x00, // L
	0xFE, 0x40, 0x38, 0x40, 0xFE, 0x00, // M
	0xFE, 0x20, 0x10, 0x08, 0xFE, 0x00, // N
	0x7C, 0x82, 0x82, 0x82, 0x7C, 0x00, // O
	//96*3=288字节
	0xFE, 0x90, 0x90, 0x90, 0x60, 0x00, // P
	0x7C, 0x82, 0x8A, 0x84, 0x7A, 0x00, // Q
	0xFE, 0x90, 0x98, 0x94, 0x62, 0x00, // R
	0x64, 0x92, 0x92, 0x92, 0x4C, 0x00, // S
	0x80, 0x80, 0xFE, 0x80, 0x80, 0x00, // T
	0xFC, 0x02, 0x02, 0x02, 0xFC, 0x00, // U
	0xF8, 0x04, 0x02, 0x04, 0xF8, 0x00, // V
	0xFC, 0x02, 0x1C, 0x02, 0xFC, 0x00, // W
	0xC6, 0x28, 0x10, 0x28, 0xC6, 0x00, // X
	0xC0, 0x20, 0x1E, 0x20, 0xC0, 0x00, // Y
	0x86, 0x8A, 0x92, 0xA2, 0xC2, 0x00, // Z
	0x00, 0xFE, 0x82, 0x82, 0x82, 0x00, // [
	0x40, 0x20, 0x10, 0x08, 0x04, 0x00, // '\'
	0x00, 0x82, 0x82, 0x82, 0xFE, 0x00, // ]
	0x20, 0x40, 0x80, 0x40, 0x20, 0x00, // ^
	0x01, 0x01, 0x01, 0x01, 0x01, 0x00, // _
	//96*4=384字节
	0x00, 0xC0, 0xE0, 0x10, 0x00, 0x00, // `
	0x04, 0x2A, 0x2A, 0x2A, 0x1E, 0x00, // a
	0xFE, 0x14, 0x22, 0x22, 0x1C, 0x00, // b
	0x1C, 0x22, 0x22, 0x22, 0x14, 0x00, // c
	0x1C, 0x22, 0x22, 0x14, 0xFE, 0x00, // d
	0x1C, 0x2A, 0x2A, 0x2A, 0x18, 0x00, // e
	0x00, 0x10, 0x7E, 0x90, 0x40, 0x00, // f
	0x18, 0x25, 0x25, 0x25, 0x3E, 0x00, // g
	0xFE, 0x10, 0x20, 0x20, 0x1E, 0x00, // h
	0x00, 0x22, 0xBE, 0x02, 0x00, 0x00, // i
	0x00, 0x04, 0x02, 0x02, 0xBC, 0x00, // j
	0x00, 0xFE, 0x08, 0x14, 0x22, 0x00, // k
	0x00, 0x82, 0xFE, 0x02, 0x00, 0x00, // l
	0x3E, 0x20, 0x1E, 0x20, 0x1E, 0x00, // m
	0x3E, 0x10, 0x20, 0x20, 0x1E, 0x00, // n
	0x1C, 0x22, 0x22, 0x22, 0x1C, 0x00, // o
	//96*5=480字节
	0x3F, 0x18, 0x24, 0x24, 0x18, 0x00, // p
	0x18, 0x24, 0x24, 0x18, 0x3F, 0x00, // q
	0x3E, 0x10, 0x20, 0x20, 0x10, 0x00, // r
	0x12, 0x2A, 0x2A, 0x2A, 0x24, 0x00, // s
	0x20, 0x20, 0xFC, 0x22, 0x24, 0x00, // t
	0x3C, 0x02, 0x02, 0x04, 0x3E, 0x00, // u
	0x38, 0x04, 0x02, 0x04, 0x38, 0x00, // v
	0x3C, 0x02, 0x0C, 0x02, 0x3C, 0x00, // w
	0x22, 0x14, 0x08, 0x14, 0x22, 0x00, // x
	0x32, 0x09, 0x09, 0x09, 0x3E, 0x00, // y
	0x22, 0x26, 0x2A, 0x32, 0x22, 0x00, // z
	0x00, 0x10, 0x6C, 0x82, 0x00, 0x00, // {
	0x00, 0x00, 0xEE, 0x00, 0x00, 0x00, // |
	0x00, 0x82, 0x6C, 0x10, 0x00, 0x00, // }
	0x40, 0x80, 0x40, 0x20, 0x40, 0x00, // ~
	0x00, 0x60, 0x90, 0x90, 0x60, 0x00, // degrees symbol
	//96*6=576字节
	//以下为特殊字符，非ASCII字符
	0x00, 0x00, 0xFE, 0x82, 0x82, 0x82, // [
	0x82, 0x82, 0x82, 0xFE, 0x00, 0x00  //  ]
};
u8 dogs102x6Memory[816 + 2];			//液晶内存副本
u8 currentPage = 0, currentColumn = 0;	//当前页，当前列
u8 backlight  = 8;						//背光亮度
u8 contrast = 0x0F;						//对比度
// Dog102-6初始化命令
u8 Dogs102x6_initMacro[] = {
	SET_SCROLL_LINE,
	SET_SEG_DIRECTION,
	SET_COM_DIRECTION,
	SET_ALL_PIXEL_ON,
	SET_INVERSE_DISPLAY,
	SET_LCD_BIAS_RATIO,
	SET_POWER_CONTROL,
	SET_VLCD_RESISTOR_RATIO,
	SET_ELECTRONIC_VOLUME_MSB,
	SET_ELECTRONIC_VOLUME_LSB,
	SET_ADV_PROGRAM_CONTROL0_MSB,
	SET_ADV_PROGRAM_CONTROL0_LSB,
	SET_DISPLAY_ENABLE,
	SET_PAGE_ADDRESS,
	SET_COLUMN_ADDRESS_MSB,
	SET_COLUMN_ADDRESS_LSB
};
//-----------------------------------------------------------------
// 通过SPI接口向当前地址写入一字节数据
//-----------------------------------------------------------------
void WriteByte(u8 dat) {
	u8 i;
	for(i = 0; i < 8; i++) {		//串行写入8位数据
		dat <<= 1;	SI = CY;		//dat左移位,高位被移入CY,发送高位
		SCK = 0;	SCK = 1;		//时钟上升沿向写入数据
	}
}
//-----------------------------------------------------------------
// 液晶初始化
//-----------------------------------------------------------------
void Dogs102x6_init() {
	RST = 0; RST = 1; CS = 0; CD = 0;
	Dogs102x6_writeCommand(Dogs102x6_initMacro, 13); 
	CS = 1;	//禁止片选
	dogs102x6Memory[0] = 102;
	dogs102x6Memory[1] = 8;
}
//-----------------------------------------------------------------
// 禁止显示
//-----------------------------------------------------------------
void Dogs102x6_disable() {
	u8 cmd[1] = { SYSTEM_RESET };
	Dogs102x6_writeCommand(cmd, 1);
	cmd[0] = SET_DISPLAY_ENABLE & 0xFE;
	Dogs102x6_writeCommand(cmd, 1);
}
//-----------------------------------------------------------------
// 写液晶命令
//-----------------------------------------------------------------
void Dogs102x6_writeCommand(u8 *sCmd, u8 i) {
	CS = 0; CD = 0;
	while (i--) { WriteByte(*sCmd++); delay_ms(2); }
	CS = 1;
}
//-----------------------------------------------------------------
// 写液晶数据
//-----------------------------------------------------------------
 void Dogs102x6_writeData(u8 *sData, u8 i) {
	CS = 0; CD = 1;
	while (i) {
		dogs102x6Memory[2+(currentPage*102)+currentColumn]=(u8)*sData;
		currentColumn++;
		if (currentColumn > 101) currentColumn = 101;
		WriteByte(*sData++); 
		i--;
	}
	CS = 1;
}
//-----------------------------------------------------------------
// 设置液晶地址：左上为0,0,pa为0~7页,ca为0-101列
//-----------------------------------------------------------------
void Dogs102x6_setAddress(u8 pa, u8 ca) {
	u8 cmd[1],H = 0x00,L = 0x00;
	u8 ColumnAddress[]={SET_COLUMN_ADDRESS_MSB, SET_COLUMN_ADDRESS_LSB };
	if (pa > 7) 	pa = 7; 					//页边界控制
	if (ca > 101)	ca = 101;					//列边界控制
	//设置页地址命令
	cmd[0] = SET_PAGE_ADDRESS + (7 - pa);
	currentPage 	= pa;
	currentColumn	= ca;
	//分别命令为高字节与低字节
	L = (ca & 0x0F);
	H = (ca & 0xF0);
	H = (H >> 4);
	ColumnAddress[0] = SET_COLUMN_ADDRESS_LSB + L;
	ColumnAddress[1] = SET_COLUMN_ADDRESS_MSB + H; 
	Dogs102x6_writeCommand(cmd, 1);				//设置页地址
	Dogs102x6_writeCommand(ColumnAddress, 2);	//设置列地址
}
//-----------------------------------------------------------------
// 反相显示
//-----------------------------------------------------------------
void Dogs102x6_setInverseDisplay() {
	u8 cmd[] = {SET_INVERSE_DISPLAY + 0x01};
	Dogs102x6_writeCommand(cmd, 1);
}
//-----------------------------------------------------------------
// 清除反相显示
//-----------------------------------------------------------------
void Dogs102x6_clearInverseDisplay() {
	u8 cmd[] = {SET_INVERSE_DISPLAY};
	Dogs102x6_writeCommand(cmd, 1);
}
//-----------------------------------------------------------------
// 滚动控制
//-----------------------------------------------------------------
void Dogs102x6_scrollLine(u8 lines) {
	u8 cmd[] = {SET_SCROLL_LINE}; 
	if (lines > 0x1F) cmd[0] |= 0x1F; else cmd[0] |= lines;
	Dogs102x6_writeCommand(cmd, 1);
}
//-----------------------------------------------------------------
// 所有像素全开
//-----------------------------------------------------------------
void Dogs102x6_setAllPixelsOn() {
	u8 cmd[] = {SET_ALL_PIXEL_ON + 0x01};
	Dogs102x6_writeCommand(cmd, 1);
}
//-----------------------------------------------------------------
// 所有像素清除
//-----------------------------------------------------------------
void Dogs102x6_clearAllPixelsOn() {
	u8 cmd[] = {SET_ALL_PIXEL_ON}; 
	Dogs102x6_writeCommand(cmd, 1);
}
//-----------------------------------------------------------------
// 清屏
//-----------------------------------------------------------------
void Dogs102x6_clearScreen() {
	u8 LcdData[] = {0x00}, p, c;
	for (p = 0; p < 8; p++) {				//8页显示
			Dogs102x6_setAddress(p, 0);
			for (c = 0; c < 102; c++) {		//每页102列
				Dogs102x6_writeData(LcdData, 1);
			}
	}
}
//-----------------------------------------------------------------
// 在指定页/列输出1字符:page为0~7页,col为0~101列,f为编码,style为风格
// 注：每个字符在1页中占6列,8行
//-----------------------------------------------------------------
void Dogs102x6_charDraw(u8 page, u8 col, u16 f, u8 style) {
	u8 b, inverted_char[6];	//反相显示缓冲
	u16 h;
	if (page > 7) 	page	= 7;
	if (col > 101)	col 	= 101; 
	if (f < 32 || f > 129) f = '.';
	h = (f - 32) * 6;		//表中首字符ASCII编码为32,每个字符点阵为6字节
	Dogs102x6_setAddress(page, col);
	if (style == DOGS102x6_DRAW_NORMAL) {	//正常显示
		Dogs102x6_writeData((u8 *)FONT6x8 + h, 6);
	}
	else {
		for (b = 0; b < 6; b++) {			//反相显示
			inverted_char[b] = FONT6x8[h + b] ^ 0xFF;
		}
		Dogs102x6_writeData(inverted_char, 6);
	}
}
//-----------------------------------------------------------------
// 在指定坐标输出1字符:x为0~101页,y为0~63列,f为编码,style为风格
//-----------------------------------------------------------------
void Dogs102x6_charDrawXY(u8 x, u8 y, u16 f, u8 style) {
	u8 b, page, desired_char[12];
	u16 h;
	if (x >= 102) x = 101;
	if (y >= 64) y = 63;
	if (f < 32 || f > 129) f = '.'; 
	h = (f - 32) * 6;
	page = y / 8;	//像素坐标转换为页
	if (style == DOGS102x6_DRAW_NORMAL) {	//正常显示
		for (b = 0; b < 6; b++) {
			desired_char[b] =
				(FONT6x8[h + b] >> (y % 8)) | 
				dogs102x6Memory[2 + (page * 102) + x + b];
			desired_char[b + 6] =
				FONT6x8[h + b] << (8 - y % 8) | 
				dogs102x6Memory[2 + ((page + 1) * 102) + x + b];
		}
	}
	else {									//反相显示
		for (b = 0; b < 6; b++) {
			desired_char[b] = (FONT6x8[h + b] ^ 0xFF) >> (y % 8);
			desired_char[b + 6] = (FONT6x8[h + b] ^ 0xFF) << (8 - y % 8);
		}
	}
	Dogs102x6_setAddress(page, x);
	Dogs102x6_writeData(desired_char, 6);
	Dogs102x6_setAddress(page + 1, x);
	Dogs102x6_writeData(desired_char + 6, 6);
}
//-----------------------------------------------------------------
// 在指定页/列输出字符串（其中row表示页，不要误解为行）
//-----------------------------------------------------------------
void Dogs102x6_stringDraw(u8 row, u8 col, char *word, u8 style) {
	u8 a = 0; 
	if (row > 7) row = 7;
	if (col > 101) col = 101;
	while (word[a] != 0) {
		if (word[a] != 0x0A) {				//非回车换行符
			if (word[a] != 0x0D) {
				Dogs102x6_charDraw(row, col, word[a], style);
				col += 6;
				if (col >= 102) {
					col = 0; if (row < 7) row++; else row = 0;
				}
			}
		}
		else {								//处理回车或换行符
			if (row < 7) row++; else row = 0;
			col = 0;
		}
		a++;
	}
}
//-----------------------------------------------------------------
// 在指定坐标输出字符串
//-----------------------------------------------------------------
void Dogs102x6_stringDrawXY(u8 x, u8 y, char *word, u8 style) {
	u8 a = 0;
	while (word[a] != 0) {
		Dogs102x6_charDrawXY(x, y, word[a], style);
		x += 6;
		if (x >= 102){	//换行处理
			x = 0;
			if (y + 8 < 64)	y += 8; else y = 0;
		}
		a++;
	}
}
//-----------------------------------------------------------------
// 清除指定页
//-----------------------------------------------------------------
void Dogs102x6_clearRow(u8 page){
	u8 cmd[] = {0}, a = 0;
	if (page > 7) page = 7; 
	Dogs102x6_setAddress(page, 0);			//设置到第page页
	for (a = 0; a < 102; a++) {				//在该页102列上全部输出0
		Dogs102x6_writeData(cmd, 1);
		dogs102x6Memory[2 + (page * 102) + a] = 0x00;
	}
}
//-----------------------------------------------------------------
// 在指定坐标绘制像素点
//-----------------------------------------------------------------
void Dogs102x6_pixelDraw(u8 x, u8 y, u8 style) {
	u8 p, temp; 
	if (x > 101) x = 101;
	if (y > 63) y = 63;
	p = y / 8; //转换为页
	temp = 0x80 >> (y % 8);	//确定页内像素高度
	if (style == DOGS102x6_DRAW_NORMAL)	//更新数组
		dogs102x6Memory[2 + (p * 102) + x] |= temp;
	else
		dogs102x6Memory[2 + (p * 102) + x] &= ~temp;
	Dogs102x6_setAddress(p, x);
	//绘制像素点
	Dogs102x6_writeData(dogs102x6Memory + (2 + (p * 102) + x), 1);
}
//-----------------------------------------------------------------
// 绘制水平线
//-----------------------------------------------------------------
void Dogs102x6_horizontalLineDraw(u8 x1, u8 x2, u8 y, u8 style){
	u8 temp = 0, p, a;
	if (x1 > 101) x1 = 101;
	if (x2 > 101) x2 = 101;
	if (y > 63)  y = 63;
	if (x1 > x2) { temp = x1; x1 = x2; x2 = temp; }
	p = y / 8;
	temp = 0x80 >> (y % 8);
	a = x1;
	while (a <= x2) {
		if (style == DOGS102x6_DRAW_NORMAL){	//准备画黑线数据
			dogs102x6Memory[2 + (p * 102) + a] |= temp;
		}
		else 	{								//准备画亮线数据
			dogs102x6Memory[2 + (p * 102) + a] &= ~temp;
		}
		a++;
	}
	//在指定位置输出线条
	Dogs102x6_setAddress(p, x1);
	Dogs102x6_writeData(dogs102x6Memory+(2+(p*102)+x1),x2-x1+1);
}
//-----------------------------------------------------------------
// 绘制垂直线
//-----------------------------------------------------------------
void Dogs102x6_verticalLineDraw(u8 y1, u8 y2, u8 x, u8 style){
	u8 temp1 = 0, temp2 = 0, p1, p2, a; 
	if (y1 > 63) y1 = 63;
	if (y2 > 63) y2 = 63;
	if (x > 101) x = 101;
	if (y1 > y2) { temp1 = y1; y1 = y2;  y2 = temp1; }
	p1 = y1 / 8;
	p2 = y2 / 8;
		temp2 = 8 - (y2 % 8);	//线条掩码
	temp2--;
	temp2 = 0xFF << temp2;
	if (p1 != p2) {
		if (y1 > 0) {
			temp1 = 0xFF00 >> (y1 % 8);
			temp1 = temp1 ^ 0xFF;
		}
		else temp1 = 0xFF;
	}
	else {
		temp1 = 0;
		a = y1 - (p1 * 8);
		a = 0xFF00 >> a;
		temp2 = temp2 ^ a;
	}
	if (style == DOGS102x6_DRAW_NORMAL) {
		dogs102x6Memory[2 + (p1 * 102) + x] |= temp1;
	}
	else {
		dogs102x6Memory[2 + (p1 * 102) + x] &= ~temp1;
	}
	Dogs102x6_setAddress(p1, x);
	Dogs102x6_writeData(dogs102x6Memory + (2 + (p1 * 102) + x), 1);
	a = p1 + 1;
	while (a < p2) {
		if (style == DOGS102x6_DRAW_NORMAL) {
			dogs102x6Memory[2 + (a * 102) + x] = 0xFF;
		}
		else {
			dogs102x6Memory[2 + (a * 102) + x] &= 0x00;
		}
		Dogs102x6_setAddress(a, x);
		Dogs102x6_writeData(dogs102x6Memory + (2 + (a * 102) + x), 1);
		a++;
	}
	if (style == DOGS102x6_DRAW_NORMAL) {
		dogs102x6Memory[2 + (p2 * 102) + x] |= temp2;
	}
	else {
		dogs102x6Memory[2 + (p2 * 102) + x] &= ~temp2;
	}
	Dogs102x6_setAddress(p2, x);
	Dogs102x6_writeData(dogs102x6Memory + (2 + (p2 * 102) + x), 1);
}
//-----------------------------------------------------------------
// 根据坐标(x1,y1)-(x2,y2)绘制直线
//-----------------------------------------------------------------
void Dogs102x6_lineDraw(u8 x1, u8 y1, u8 x2, u8 y2, u8 style){
	i8 x, y, deltay, deltax, d;
	i8 x_dir, y_dir;
	if (y1 > 63)	y1 = 63;
	if (y2 > 63)	y2 = 63;
	if (x1 > 101)	x1 = 101;
	if (x2 > 101)	x2 = 101;
	//指定线段为直线（垂直或水平）
	if (x1 == x2) Dogs102x6_verticalLineDraw(y1, y2, x1, style);
	else if (y1 == y2) Dogs102x6_horizontalLineDraw(x1, x2, y1, style);
	//否则为斜线
	else  {
		if (x1 > x2)	x_dir = -1;	else	x_dir = 1;
		if (y1 > y2)	y_dir = -1;	else	y_dir = 1;
		x = x1; y = y1;
		deltay = abs(y2 - y1);
		deltax = abs(x2 - x1);
		if (deltax >= deltay) {
			d = (deltay << 1) - deltax;
			while (x != x2) {
				Dogs102x6_pixelDraw(x, y,  style);
				if (d < 0) d += (deltay << 1);
				else {
					d += ((deltay - deltax) << 1);
					y += y_dir;
				}
				x += x_dir;
			}
		}
		else {
			d = (deltax << 1) - deltay;
			while (y != y2) {
				Dogs102x6_pixelDraw(x, y, style);
				if (d < 0) d += (deltax << 1);
				else {
					d += ((deltax - deltay) << 1);
					x += x_dir;
				}
				y += y_dir;
			}
		}
	}
}
//-----------------------------------------------------------------
// 绘制圆形
//-----------------------------------------------------------------
void Dogs102x6_circleDraw(u8 x, u8 y, u8 radius, u8 style) {
	i8 xx, yy, ddF_x, ddF_y, f; 
	ddF_x = 0;
	ddF_y = -(2 * radius);
	f = 1 - radius;
	xx = 0;
	yy = radius;
	Dogs102x6_pixelDraw(x + xx, y + yy, style);
	Dogs102x6_pixelDraw(x + xx, y - yy, style);
	Dogs102x6_pixelDraw(x - xx, y + yy, style);
	Dogs102x6_pixelDraw(x - xx, y - yy, style);
	Dogs102x6_pixelDraw(x + yy, y + xx, style);
	Dogs102x6_pixelDraw(x + yy, y - xx, style);
	Dogs102x6_pixelDraw(x - yy, y + xx, style);
	Dogs102x6_pixelDraw(x - yy, y - xx, style);
	while (xx < yy) {
		if (f >= 0) {
			yy--; ddF_y += 2; f += ddF_y;
		}
		xx++;  ddF_x += 2; f += ddF_x + 1;
		Dogs102x6_pixelDraw(x + xx,	y + yy,	style);
		Dogs102x6_pixelDraw(x + xx,	y - yy,	style);
		Dogs102x6_pixelDraw(x - xx,	y + yy,	style);
		Dogs102x6_pixelDraw(x - xx,	y - yy,	style);
		Dogs102x6_pixelDraw(x + yy,	y + xx,	style);
		Dogs102x6_pixelDraw(x + yy,	y - xx,	style);
		Dogs102x6_pixelDraw(x - yy,	y + xx,	style);
		Dogs102x6_pixelDraw(x - yy,	y - xx,	style);
	}
}
//-----------------------------------------------------------------
// 在指定位置输出位图
//-----------------------------------------------------------------
void Dogs102x6_imageDraw(const u8 IMAGE[], u8 row, u8 col) {
	// height in rows (row = 8 pixels), width in columns
	u8 a, height, width;
	width = IMAGE[0]; //图片尺寸保存于图片点阵数据的最前面2字节
	height = IMAGE[1] / 8;
	for (a = 0; a < height; a++) {
		Dogs102x6_setAddress(row + a, col);
		// Draw a row of the image
		Dogs102x6_writeData((u8*)IMAGE + 2 + a * width, width);
	}
}
//-----------------------------------------------------------------
// 清除指定区域的位置
//-----------------------------------------------------------------
void Dogs102x6_clearImage(u8 height, u8 width, u8 row, u8 col) {
	u8 a, b, cmd[] = {0x00};
	for (a = 0; a < height; a++) {
		Dogs102x6_setAddress(row + a, col);
		for (b = 0; b < width; b++) {
			// clear a byte
			Dogs102x6_writeData(cmd, 1);
		}
	}
}