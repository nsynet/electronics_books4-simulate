//-------------------------- ILI9341.c ----------------------------
//  名称: TFT彩屏ILI9341驱动程序
//-----------------------------------------------------------------
#include "ILI9341.h"
#define u8 unsigned char
struct typFNT_HZ16 {				//汉字16x16点阵结构
	u8 inner_CODE[2];				//汉字内码
	u8 Msk[32];						//32字节点阵(掩码),16行/每行2字节
};
int cursor_x, cursor_y = 0;			//光标位置变量
#define MAIN_Fosc 24000000L			//时钟频率定义
//-----------------------------------------------------------------
// 延时函数(参数取值限于1~255)
//-----------------------------------------------------------------
void delay_ms(u8 ms) {
	u16 i;
	do{
		i = MAIN_Fosc / 13000;
		while(--i);
	}while(--ms);
}
//-----------------------------------------------------------------
// 宏定义:分别为绝对值，最小值，交换
//-----------------------------------------------------------------
int temp;
#ifndef abs
# define abs(n) (((n) < 0) ? -(n) : (n))
#endif
#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif
#ifndef swap
#define swap(a, b) { temp = a; a = b; b = temp; }
#endif
//-----------------------------------------------------------------
// SPI写函数
//-----------------------------------------------------------------
u8 SPI_WR(u8 dat) {
	u8 i;
	for(i = 0; i < 8; i++) {// 输出1字节（8位）
		dat <<= 1;		LCD_SDI = CY;	//数据放到线上
		LCD_SCL = 1;	LCD_SCL = 0;	//串行时钟输出
	}
	return 0xFF;
}
//-----------------------------------------------------------------
// 写液晶数据
//-----------------------------------------------------------------
void LCD_WR_DATA(u8 val) {
	LCD_CS = 0;	LCD_DC = 1;	SPI_WR(val);	LCD_CS = 1;
}
//-----------------------------------------------------------------
// 写液晶命令
//-----------------------------------------------------------------
void LCD_WR_REG(u8 reg) {
	LCD_CS = 0;	LCD_DC = 0;	SPI_WR(reg);	LCD_CS = 1;
}
//-----------------------------------------------------------------
// 液晶初始化
//-----------------------------------------------------------------
void LCD_Init() {
	P0 = 0x00; LCD_RST = 0;	delay_ms(10); LCD_RST = 1; delay_ms(120);
	LCD_WR_REG(0xCF);	//功耗控制命令（3字节参数） 
	LCD_WR_DATA(0x00);	LCD_WR_DATA(0xC1);	LCD_WR_DATA(0x30);
	LCD_WR_REG(0xED);	//电源序列控制（4字节参数） 
	LCD_WR_DATA(0x64);	LCD_WR_DATA(0x03);	LCD_WR_DATA(0x12);
	LCD_WR_DATA(0x81);
	LCD_WR_REG(0xE8);	//驱动时序控制A（3字节参数）
	LCD_WR_DATA(0x85);	LCD_WR_DATA(0x10);	LCD_WR_DATA(0x7A);
	LCD_WR_REG(0xCB);	//功耗控制A（5字节参数） 
	LCD_WR_DATA(0x39);	LCD_WR_DATA(0x2C);	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x34);	LCD_WR_DATA(0x02); 
	LCD_WR_REG(0xF7);	//泵比控制（1字节参数）
	LCD_WR_DATA(0x20); 
	LCD_WR_REG(0xEA);	//驱动时序控制B（2字节参数） 
	LCD_WR_DATA(0x00); 	LCD_WR_DATA(0x00);
	LCD_WR_REG(0xC0);	//功耗控制1（1字节参数）
	LCD_WR_DATA(0x1B);	//VRH[5:0] 
	LCD_WR_REG(0xC1); 	//功耗控制2（1字节参数）
	LCD_WR_DATA(0x01);	//SAP[2:0];BT[3:0] 
	LCD_WR_REG(0xC5); 	//VCOM控制1（1字节参数）
	LCD_WR_DATA(0x30);	LCD_WR_DATA(0x30);
	LCD_WR_REG(0xC7); 	//VCOM控制2（1字节参数）
	LCD_WR_DATA(0XB7);
	LCD_WR_REG(0x36); 	//存储器访问控制（1字节参数）
	LCD_WR_DATA(0x48); 
	LCD_WR_REG(0x3A); 	//COLMOD像素格式设置（1字节参数）
	LCD_WR_DATA(0x55);	//默认为18位(0x66),此处配置为16位(0x55)
	LCD_WR_REG(0xB1);	//帧速率控制（2字节参数）
	LCD_WR_DATA(0x00);	LCD_WR_DATA(0x1A); 
	LCD_WR_REG(0xB6); 	//显示功能控制（2字节参数）
	LCD_WR_DATA(0x0A);	LCD_WR_DATA(0xA2);
	LCD_WR_REG(0xF2); 	//3伽马控制（1字节参数）
	LCD_WR_DATA(0x00);
	LCD_WR_REG(0x26); 	//伽马设置（1字节参数）
	LCD_WR_DATA(0x01);	
	LCD_WR_REG(0xE0); 	//正极伽马校准（15字节参数）
	LCD_WR_DATA(0x0F);	LCD_WR_DATA(0x2A); 	LCD_WR_DATA(0x28);
	LCD_WR_DATA(0x08);	LCD_WR_DATA(0x0E);	LCD_WR_DATA(0x08);
	LCD_WR_DATA(0x54);	LCD_WR_DATA(0XA9);	LCD_WR_DATA(0x43);
	LCD_WR_DATA(0x0A);	LCD_WR_DATA(0x0F);	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);	LCD_WR_DATA(0x00);	LCD_WR_DATA(0x00);
	LCD_WR_REG(0xE1);	//负极伽马校准（15字节参数）
	LCD_WR_DATA(0x00);	LCD_WR_DATA(0x15);	LCD_WR_DATA(0x17);
	LCD_WR_DATA(0x07);	LCD_WR_DATA(0x11);	LCD_WR_DATA(0x06);
	LCD_WR_DATA(0x2B);	LCD_WR_DATA(0x56);	LCD_WR_DATA(0x3C);
	LCD_WR_DATA(0x05);	LCD_WR_DATA(0x10);	LCD_WR_DATA(0x0F);
	LCD_WR_DATA(0x3F);	LCD_WR_DATA(0x3F);	LCD_WR_DATA(0x0F);
	LCD_WR_REG(0x2B);	//页地址设置（4字节参数）
	LCD_WR_DATA(0x00);	LCD_WR_DATA(0x00);	LCD_WR_DATA(0x01);
	LCD_WR_DATA(0x3F);	LCD_WR_REG(0x2A); 	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);	LCD_WR_DATA(0x00);	LCD_WR_DATA(0xef); 
	LCD_WR_REG(0x11);	//退出睡眠模式（无参数）
	delay_ms(120);
	LCD_WR_REG(0x29);	//开显示（无参数）
}
//-----------------------------------------------------------------
// 清屏
//-----------------------------------------------------------------
void LCD_Clear(u16 color) {  





}
//-----------------------------------------------------------------
// 设置待添加显示内容的窗口
//-----------------------------------------------------------------
void LCD_SetArea(u16 x0, u16 y0, u16 x1, u16 y1) {
	LCD_WR_REG(ILI9341_CASET);	//列地址设置2A
	LCD_WR_DATA(x0 >> 8);	LCD_WR_DATA(x0 & 0xFF);
	LCD_WR_DATA(x1 >> 8);	LCD_WR_DATA(x1 & 0xFF);
	LCD_WR_REG(ILI9341_PASET);	//页地址设置2B
	LCD_WR_DATA(y0>>8);		LCD_WR_DATA(y0);
	LCD_WR_DATA(y1>>8);		LCD_WR_DATA(y1);
	LCD_WR_REG(ILI9341_RAMWR);	//写RAM
}
//-----------------------------------------------------------------
// 绘制像素点
//-----------------------------------------------------------------
void drawPixel(int x, int y, u16 color) {
	//越界返回
	if(	(x < 0) ||( x >= ILI9341_TFTWIDTH) || 
		(y < 0) || (y >= ILI9341_TFTHEIGHT)) return;
	LCD_SetArea(x,y,x+1,y+1);			//设置显示区域
	LCD_DC = 1; LCD_CS = 0;
	SPI_WR(color >> 8); SPI_WR(color);	//SPI输出像素颜色（16位双字节）
	LCD_CS = 1;
}
//-----------------------------------------------------------------
// 绘制线条
//-----------------------------------------------------------------
void drawLine(int x0, int y0, int x1, int y1,u16 color) {
	int t, dx, dy, err,ystep;
	int steep = abs(y1 - y0) > abs(x1 - x0);
	if (steep) {
		t = x0; x0 = y0; y0 = t;
		t = x1; x1 = y1; y1 = t;
	}
	if (x0 > x1) {
		t = x0; x0 = x1; x1 = t;
		t = y0; y0 = y1; y1 = t;
	}
	dx = x1 - x0;	dy = abs(y1 - y0);
	err = dx / 2;
	if (y0 < y1) ystep = 1; else ystep = -1;
	for (; x0<=x1; x0++) {				//通过绘制像素点函数绘制直线
		if (steep) 	drawPixel(y0, x0, color);
		else 				drawPixel(x0, y0, color);
		err -= dy;
		if (err < 0) { y0 += ystep; err += dx; }
	}
}
//-----------------------------------------------------------------
// 绘制垂直线
//-----------------------------------------------------------------
void drawFastVLine(int x, int y,int h, u16 color) {
	drawLine(x, y, x, y+h-1, color);
}
//-----------------------------------------------------------------
// 绘制水平线
//-----------------------------------------------------------------
void drawFastHLine(int x, int y, int w, u16 color) {
	drawLine(x, y, x+w-1, y, color);
}
//-----------------------------------------------------------------
// 绘制圆形
//-----------------------------------------------------------------
void drawCircle(int x0, int y0, int r,u16 color) {
	int f = 1 - r;
	int ddF_x = 1;
	int ddF_y = -2 * r;
	int x = 0, y = r;
	drawPixel(x0  , y0+r, color);
	drawPixel(x0  , y0-r, color);
	drawPixel(x0+r, y0  , color);
	drawPixel(x0-r, y0  , color);
	while (x<y) {
		if (f >= 0) {	y--;	ddF_y += 2; f += ddF_y;	}
		x++;	ddF_x += 2; 	f += ddF_x; 
		drawPixel(x0 + x, y0 + y, color);
		drawPixel(x0 - x, y0 + y, color);
		drawPixel(x0 + x, y0 - y, color);
		drawPixel(x0 - x, y0 - y, color);
		drawPixel(x0 + y, y0 + x, color);
		drawPixel(x0 - y, y0 + x, color);
		drawPixel(x0 + y, y0 - x, color);
		drawPixel(x0 - y, y0 - x, color);
	}
}
//-----------------------------------------------------------------
// 绘制圆形辅助函数
//-----------------------------------------------------------------
void drawCircleHelper(int x0,int y0,int r,u8 cname,u16 color){
	int f      = 1 - r;
	int ddF_x = 1;
	int ddF_y = -2 * r;
	int x = 0, y = r;
	while (x<y) {
		if (f >= 0) {
			y--; ddF_y += 2; f += ddF_y;
		}
		x++; ddF_x += 2; f += ddF_x;
		if (cname & 0x4) {
			drawPixel(x0 + x, y0 + y, color);
			drawPixel(x0 + y, y0 + x, color);
		}
		if (cname & 0x2) {
			drawPixel(x0 + x, y0 - y, color);
			drawPixel(x0 + y, y0 - x, color);
		}
		if (cname & 0x8) {
			drawPixel(x0 - y, y0 + x, color);
			drawPixel(x0 - x, y0 + y, color);
		}
		if (cname & 0x1) {
			drawPixel(x0 - y, y0 - x, color);
			drawPixel(x0 - x, y0 - y, color);
		}
	}
}
//-----------------------------------------------------------------
// 绘制实心圆形
//-----------------------------------------------------------------
void fillCircle(int x0, int y0, int r, u16 color) {
	drawFastVLine(x0, y0-r, 2*r+1, color);
	fillCircleHelper(x0, y0, r, 3, 0, color);
}
//-----------------------------------------------------------------
// 绘制实心圆形辅助函数
//-----------------------------------------------------------------
void fillCircleHelper(int x0,int y0,int r,u8 cname,int delt,u16 color) {
	int f     = 1 - r;
	int ddF_x = 1;
	int ddF_y = -2 * r;
	int x = 0, y = r;
	while (x < y) {
		if (f >= 0) {
			y--; ddF_y += 2; f += ddF_y; 
		}
		x++; ddF_x += 2; f += ddF_x;
		if (cname & 0x1) {
			drawFastVLine(x0+x, y0-y, 2*y+1+ delt, color);
			drawFastVLine(x0+y, y0-x, 2*x+1+ delt, color);
		}
		if (cname & 0x2) {
			drawFastVLine(x0-x, y0-y, 2*y+1+ delt, color);
			drawFastVLine(x0-y, y0-x, 2*x+1+ delt, color);
		}
	}
}
//-----------------------------------------------------------------
// 绘制矩形
//-----------------------------------------------------------------
void drawRect(int x, int y, int w, int h, u16 color) {
	drawFastHLine(x, y, w, color);
	drawFastHLine(x, y+h-1, w, color);
	drawFastVLine(x, y, h, color);
	drawFastVLine(x+w-1, y, h, color);
}
//-----------------------------------------------------------------
// 绘制实心矩形
//-----------------------------------------------------------------
void fillRect(int x, int y, int w, int h, u16 color) {
	int i;
	for (i = x; i<x+w; i++) {
		drawFastVLine(i, y, h, color);
	}
}
//-----------------------------------------------------------------
// 绘制圆角矩形
//-----------------------------------------------------------------
void drawRoundRect(int x, int y, int w, int h, int r, u16 color) {
	drawFastHLine(x+r  , y    , w-2*r, color);	//上边
	drawFastHLine(x+r  , y+h-1, w-2*r, color);	//下边
	drawFastVLine(x    , y+r  , h-2*r, color);	//左边
	drawFastVLine(x+w-1, y+r  , h-2*r, color);	//右边
	// 绘制四个圆角
	drawCircleHelper(x+r    , y+r    , r, 1, color);
	drawCircleHelper(x+w-r-1, y+r    , r, 2, color);
	drawCircleHelper(x+w-r-1, y+h-r-1, r, 4, color);
	drawCircleHelper(x+r    , y+h-r-1, r, 8, color);
}
//-----------------------------------------------------------------
// 绘制实心圆角矩形
//-----------------------------------------------------------------
void fillRoundRect(int x, int y, int w, int h, int r, u16 color) {
	fillRect(x+r, y, w-2*r, h, color);
	fillCircleHelper(x+w-r-1, y+r, r, 1, h-2*r-1, color);
	fillCircleHelper(x+r    , y+r, r, 2, h-2*r-1, color);
}
//-----------------------------------------------------------------
// 绘制三角形
//-----------------------------------------------------------------
void drawTriangle(int x0,int y0,int x1,int y1,int x2,int y2,u16 color){
	drawLine(x0, y0, x1, y1, color);
	drawLine(x1, y1, x2, y2, color);
	drawLine(x2, y2, x0, y0, color);
}
//-----------------------------------------------------------------
// 绘制实心三角形
//-----------------------------------------------------------------
void fillTriangle(int x0,int y0,int x1,int y1,int x2,int y2,u16 color){
	int a, b, y, last;
	int dx01,dx02,dy01,dy02,dx12,dy12;
	long sa,sb;
	//对Y坐标进行排序(y2-y1-y0)
	if (y0 > y1) { swap(y0, y1); swap(x0, x1); }
	if (y1 > y2) { swap(y2, y1); swap(x2, x1); }
	if (y0 > y1) { swap(y0, y1); swap(x0, x1); }
	if(y0 == y2) { //纵坐标点出现在一条水平线上
		a = b = x0;
		if(x1 < a) a = x1;	else if(x1 > b) b = x1;
		if(x2 < a) a = x2;	else if(x2 > b) b = x2;
		drawFastHLine(a, y0, b-a+1, color);
		return;
	}
	dx01 = x1 - x0;	dy01 = y1 - y0;
	dx02 = x2 - x0;	dy02 = y2 - y0;
	dx12 = x2 - x1;	dy12 = y2 - y1;
	sa   = 0;	sb   = 0;
	if(y1 == y2) last = y1;
	else         last = y1-1;
	for(y=y0; y<=last; y++) {
		a = x0 + sa / dy01; b = x0 + sb / dy02;
		sa += dx01;	sb += dx02;
		if(a > b) swap(a,b);
		drawFastHLine(a, y, b-a+1, color);
	}
	sa = dx12 * (y - y1);
	sb = dx02 * (y - y0);
	for(; y<=y2; y++) {
		a = x1 + sa / dy12; b = x0 + sb / dy02;
		sa += dx12;	sb += dx02;
		if(a > b) swap(a,b);
		drawFastHLine(a, y, b-a+1, color);
	}
}
//-----------------------------------------------------------------
// 绘制单色位图
//-----------------------------------------------------------------
void drawBitmap(int x,int y,const u8 *bitmap,int w,int h,u16 color){
	int i,j,byteWidth = (w + 7) / 8;
	u8 byte = 0;
	for( j = 0; j < h; j++, y++) {
		for(i = 0; i < w; i++ ) {
			if(i & 7)	byte	<<= 1;
			else		byte	= bitmap[j * byteWidth + i / 8];
			if(byte & 0x80) drawPixel(x + i, y, color);
		}
	}
}
//-----------------------------------------------------------------
// 绘制16位彩图
//-----------------------------------------------------------------
void drawRGBBitmap(int x, int y, u16 *bitmap, int w, int h) {
	int i,j;
	for(j = 0; j < h; j++, y++) {
		for(i = 0; i < w; i++ ) {
			drawPixel(x+i, y, bitmap[j * w + i]);
		}
	}
}
extern code u8 font[];
extern code struct typFNT_HZ16 hz16[];
//-----------------------------------------------------------------
// 设置当前光标位置
//-----------------------------------------------------------------
void setCursor(int x, int y) {
	cursor_x = x; cursor_y = y;//更新光标位置
	LCD_SetArea(x,y,x,y);
}
//-----------------------------------------------------------------
// 绘制一个字符
//-----------------------------------------------------------------
void drawChar(int x, int y, u8 c, u16 color, u16 bg, u8 sz) {
	char i,j;	u8 line;
	if((x >= ILI9341_TFTWIDTH)		||	//处理右、下、左、上越界问题
		 (y >= ILI9341_TFTHEIGHT)	||
		 ((x + 6 * sz - 1) < 0)		||
		 ((y + 8 * sz - 1) < 0))
			return;
	for(i = 0; i < 5; i++ ) { //每个字符由5列点阵字节构成(5*8)
		line = font[c * 5 + i];	//取第i列点阵字节
		for(j = 0; j < 8; j++, line >>= 1) { //绘制第i列8个像素点
			if(line & 1) {			//为1则按color色绘制
				if(sz == 1)	drawPixel(x+i, y+j, color);//正常绘制
				else fillRect(x+i*sz, y+j*sz, sz, sz, color);//放大绘制
			} else 	
			if(bg != color) {		//如果为0且不透明，则按背景色绘制
				if(sz == 1)	drawPixel(x+i, y+j, bg);//正常绘制
				else	fillRect(x+i*sz, y+j*sz, sz, sz, bg);//放大绘制
			}
		}
	}
	//如果为非透明色彩则最后1列按背景色补1条垂直线,用于形成字符间隙
	if(bg != color) {
		if(sz == 1)	drawFastVLine(x+5, y, 8, bg);//正常绘制
		else		fillRect(x+5*sz, y, sz, 8*sz, bg);//放大绘制
	}
}
//-----------------------------------------------------------------
// 在当前光标位置写一个字符
//-----------------------------------------------------------------
void write(u8 c, u16 color, u16 bg, u8 sz) {
	if(c == '\n') {
		cursor_x  = 0; cursor_y += sz * 8;		//更新光标位置
	} 
	else if(c != '\r') {
		if((cursor_x + sz * 6) > ILI9341_TFTWIDTH) {
			cursor_x  = 0; cursor_y += sz * 8;	//更新光标位置
		}
		drawChar(cursor_x, cursor_y, c, color, bg, sz);
		cursor_x += sz * 6;						//更新光标位置
	}
}
//-----------------------------------------------------------------
// 显示中文字符串
//-----------------------------------------------------------------
void DrawChineseString(u16 x,u16 y,u16 color,u16 bg,u8 *s,u16 count) {
	u8 i,j,k;
	while(*s) {
		if((*s) >= 128) {	//编码>=128，表示汉字内码
			for (k = 0; k < count; k++) {
				//根据内码在字库点阵数组中查找点阵数据
				if(	(hz16[k].inner_CODE[0] == *(s))&&	
					(hz16[k].inner_CODE[1] == *(s+1))) { 
					for(i = 0; i < 16; i++){	//共16行
						for(j = 0; j < 8; j++) { //显示当前行左半部分像素
							if(hz16[k].Msk[i*2]&(0x80>>j))	
								drawPixel(x+j,y+i,color);
							else { if (color != bg) 
								drawPixel(x+j,y+i,bg); }
						}
						for(j = 0; j < 8; j++) { //显示当前行右半部分像素
							if(hz16[k].Msk[i*2+1]&(0x80>>j))
								drawPixel(x+j+8,y+i,color);
							else if (color != bg)
								drawPixel(x+j+8,y+i,bg);
						}
						cursor_x = x+j+8*2; cursor_y = y+i;//更新光标位置
					}
				}
			}
			s += 2; x += 16;	//中文字符数组索引+2，横坐标+16
		}
		else s++;				//否则为英文半角字符，索引+1，忽略
	}
}