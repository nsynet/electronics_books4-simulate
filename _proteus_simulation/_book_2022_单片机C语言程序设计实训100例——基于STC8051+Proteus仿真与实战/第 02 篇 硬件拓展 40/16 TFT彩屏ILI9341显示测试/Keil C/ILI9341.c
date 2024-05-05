//-------------------------- ILI9341.c ----------------------------
//  ����: TFT����ILI9341��������
//-----------------------------------------------------------------
#include "ILI9341.h"
#define u8 unsigned char
struct typFNT_HZ16 {				//����16x16����ṹ
	u8 inner_CODE[2];				//��������
	u8 Msk[32];						//32�ֽڵ���(����),16��/ÿ��2�ֽ�
};
int cursor_x, cursor_y = 0;			//���λ�ñ���
#define MAIN_Fosc 24000000L			//ʱ��Ƶ�ʶ���
//-----------------------------------------------------------------
// ��ʱ����(����ȡֵ����1~255)
//-----------------------------------------------------------------
void delay_ms(u8 ms) {
	u16 i;
	do{
		i = MAIN_Fosc / 13000;
		while(--i);
	}while(--ms);
}
//-----------------------------------------------------------------
// �궨��:�ֱ�Ϊ����ֵ����Сֵ������
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
// SPIд����
//-----------------------------------------------------------------
u8 SPI_WR(u8 dat) {
	u8 i;
	for(i = 0; i < 8; i++) {// ���1�ֽڣ�8λ��
		dat <<= 1;		LCD_SDI = CY;	//���ݷŵ�����
		LCD_SCL = 1;	LCD_SCL = 0;	//����ʱ�����
	}
	return 0xFF;
}
//-----------------------------------------------------------------
// дҺ������
//-----------------------------------------------------------------
void LCD_WR_DATA(u8 val) {
	LCD_CS = 0;	LCD_DC = 1;	SPI_WR(val);	LCD_CS = 1;
}
//-----------------------------------------------------------------
// дҺ������
//-----------------------------------------------------------------
void LCD_WR_REG(u8 reg) {
	LCD_CS = 0;	LCD_DC = 0;	SPI_WR(reg);	LCD_CS = 1;
}
//-----------------------------------------------------------------
// Һ����ʼ��
//-----------------------------------------------------------------
void LCD_Init() {
	P0 = 0x00; LCD_RST = 0;	delay_ms(10); LCD_RST = 1; delay_ms(120);
	LCD_WR_REG(0xCF);	//���Ŀ������3�ֽڲ����� 
	LCD_WR_DATA(0x00);	LCD_WR_DATA(0xC1);	LCD_WR_DATA(0x30);
	LCD_WR_REG(0xED);	//��Դ���п��ƣ�4�ֽڲ����� 
	LCD_WR_DATA(0x64);	LCD_WR_DATA(0x03);	LCD_WR_DATA(0x12);
	LCD_WR_DATA(0x81);
	LCD_WR_REG(0xE8);	//����ʱ�����A��3�ֽڲ�����
	LCD_WR_DATA(0x85);	LCD_WR_DATA(0x10);	LCD_WR_DATA(0x7A);
	LCD_WR_REG(0xCB);	//���Ŀ���A��5�ֽڲ����� 
	LCD_WR_DATA(0x39);	LCD_WR_DATA(0x2C);	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x34);	LCD_WR_DATA(0x02); 
	LCD_WR_REG(0xF7);	//�ñȿ��ƣ�1�ֽڲ�����
	LCD_WR_DATA(0x20); 
	LCD_WR_REG(0xEA);	//����ʱ�����B��2�ֽڲ����� 
	LCD_WR_DATA(0x00); 	LCD_WR_DATA(0x00);
	LCD_WR_REG(0xC0);	//���Ŀ���1��1�ֽڲ�����
	LCD_WR_DATA(0x1B);	//VRH[5:0] 
	LCD_WR_REG(0xC1); 	//���Ŀ���2��1�ֽڲ�����
	LCD_WR_DATA(0x01);	//SAP[2:0];BT[3:0] 
	LCD_WR_REG(0xC5); 	//VCOM����1��1�ֽڲ�����
	LCD_WR_DATA(0x30);	LCD_WR_DATA(0x30);
	LCD_WR_REG(0xC7); 	//VCOM����2��1�ֽڲ�����
	LCD_WR_DATA(0XB7);
	LCD_WR_REG(0x36); 	//�洢�����ʿ��ƣ�1�ֽڲ�����
	LCD_WR_DATA(0x48); 
	LCD_WR_REG(0x3A); 	//COLMOD���ظ�ʽ���ã�1�ֽڲ�����
	LCD_WR_DATA(0x55);	//Ĭ��Ϊ18λ(0x66),�˴�����Ϊ16λ(0x55)
	LCD_WR_REG(0xB1);	//֡���ʿ��ƣ�2�ֽڲ�����
	LCD_WR_DATA(0x00);	LCD_WR_DATA(0x1A); 
	LCD_WR_REG(0xB6); 	//��ʾ���ܿ��ƣ�2�ֽڲ�����
	LCD_WR_DATA(0x0A);	LCD_WR_DATA(0xA2);
	LCD_WR_REG(0xF2); 	//3٤����ƣ�1�ֽڲ�����
	LCD_WR_DATA(0x00);
	LCD_WR_REG(0x26); 	//٤�����ã�1�ֽڲ�����
	LCD_WR_DATA(0x01);	
	LCD_WR_REG(0xE0); 	//����٤��У׼��15�ֽڲ�����
	LCD_WR_DATA(0x0F);	LCD_WR_DATA(0x2A); 	LCD_WR_DATA(0x28);
	LCD_WR_DATA(0x08);	LCD_WR_DATA(0x0E);	LCD_WR_DATA(0x08);
	LCD_WR_DATA(0x54);	LCD_WR_DATA(0XA9);	LCD_WR_DATA(0x43);
	LCD_WR_DATA(0x0A);	LCD_WR_DATA(0x0F);	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);	LCD_WR_DATA(0x00);	LCD_WR_DATA(0x00);
	LCD_WR_REG(0xE1);	//����٤��У׼��15�ֽڲ�����
	LCD_WR_DATA(0x00);	LCD_WR_DATA(0x15);	LCD_WR_DATA(0x17);
	LCD_WR_DATA(0x07);	LCD_WR_DATA(0x11);	LCD_WR_DATA(0x06);
	LCD_WR_DATA(0x2B);	LCD_WR_DATA(0x56);	LCD_WR_DATA(0x3C);
	LCD_WR_DATA(0x05);	LCD_WR_DATA(0x10);	LCD_WR_DATA(0x0F);
	LCD_WR_DATA(0x3F);	LCD_WR_DATA(0x3F);	LCD_WR_DATA(0x0F);
	LCD_WR_REG(0x2B);	//ҳ��ַ���ã�4�ֽڲ�����
	LCD_WR_DATA(0x00);	LCD_WR_DATA(0x00);	LCD_WR_DATA(0x01);
	LCD_WR_DATA(0x3F);	LCD_WR_REG(0x2A); 	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);	LCD_WR_DATA(0x00);	LCD_WR_DATA(0xef); 
	LCD_WR_REG(0x11);	//�˳�˯��ģʽ���޲�����
	delay_ms(120);
	LCD_WR_REG(0x29);	//����ʾ���޲�����
}
//-----------------------------------------------------------------
// ����
//-----------------------------------------------------------------
void LCD_Clear(u16 color) {  





}
//-----------------------------------------------------------------
// ���ô������ʾ���ݵĴ���
//-----------------------------------------------------------------
void LCD_SetArea(u16 x0, u16 y0, u16 x1, u16 y1) {
	LCD_WR_REG(ILI9341_CASET);	//�е�ַ����2A
	LCD_WR_DATA(x0 >> 8);	LCD_WR_DATA(x0 & 0xFF);
	LCD_WR_DATA(x1 >> 8);	LCD_WR_DATA(x1 & 0xFF);
	LCD_WR_REG(ILI9341_PASET);	//ҳ��ַ����2B
	LCD_WR_DATA(y0>>8);		LCD_WR_DATA(y0);
	LCD_WR_DATA(y1>>8);		LCD_WR_DATA(y1);
	LCD_WR_REG(ILI9341_RAMWR);	//дRAM
}
//-----------------------------------------------------------------
// �������ص�
//-----------------------------------------------------------------
void drawPixel(int x, int y, u16 color) {
	//Խ�緵��
	if(	(x < 0) ||( x >= ILI9341_TFTWIDTH) || 
		(y < 0) || (y >= ILI9341_TFTHEIGHT)) return;
	LCD_SetArea(x,y,x+1,y+1);			//������ʾ����
	LCD_DC = 1; LCD_CS = 0;
	SPI_WR(color >> 8); SPI_WR(color);	//SPI���������ɫ��16λ˫�ֽڣ�
	LCD_CS = 1;
}
//-----------------------------------------------------------------
// ��������
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
	for (; x0<=x1; x0++) {				//ͨ���������ص㺯������ֱ��
		if (steep) 	drawPixel(y0, x0, color);
		else 				drawPixel(x0, y0, color);
		err -= dy;
		if (err < 0) { y0 += ystep; err += dx; }
	}
}
//-----------------------------------------------------------------
// ���ƴ�ֱ��
//-----------------------------------------------------------------
void drawFastVLine(int x, int y,int h, u16 color) {
	drawLine(x, y, x, y+h-1, color);
}
//-----------------------------------------------------------------
// ����ˮƽ��
//-----------------------------------------------------------------
void drawFastHLine(int x, int y, int w, u16 color) {
	drawLine(x, y, x+w-1, y, color);
}
//-----------------------------------------------------------------
// ����Բ��
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
// ����Բ�θ�������
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
// ����ʵ��Բ��
//-----------------------------------------------------------------
void fillCircle(int x0, int y0, int r, u16 color) {
	drawFastVLine(x0, y0-r, 2*r+1, color);
	fillCircleHelper(x0, y0, r, 3, 0, color);
}
//-----------------------------------------------------------------
// ����ʵ��Բ�θ�������
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
// ���ƾ���
//-----------------------------------------------------------------
void drawRect(int x, int y, int w, int h, u16 color) {
	drawFastHLine(x, y, w, color);
	drawFastHLine(x, y+h-1, w, color);
	drawFastVLine(x, y, h, color);
	drawFastVLine(x+w-1, y, h, color);
}
//-----------------------------------------------------------------
// ����ʵ�ľ���
//-----------------------------------------------------------------
void fillRect(int x, int y, int w, int h, u16 color) {
	int i;
	for (i = x; i<x+w; i++) {
		drawFastVLine(i, y, h, color);
	}
}
//-----------------------------------------------------------------
// ����Բ�Ǿ���
//-----------------------------------------------------------------
void drawRoundRect(int x, int y, int w, int h, int r, u16 color) {
	drawFastHLine(x+r  , y    , w-2*r, color);	//�ϱ�
	drawFastHLine(x+r  , y+h-1, w-2*r, color);	//�±�
	drawFastVLine(x    , y+r  , h-2*r, color);	//���
	drawFastVLine(x+w-1, y+r  , h-2*r, color);	//�ұ�
	// �����ĸ�Բ��
	drawCircleHelper(x+r    , y+r    , r, 1, color);
	drawCircleHelper(x+w-r-1, y+r    , r, 2, color);
	drawCircleHelper(x+w-r-1, y+h-r-1, r, 4, color);
	drawCircleHelper(x+r    , y+h-r-1, r, 8, color);
}
//-----------------------------------------------------------------
// ����ʵ��Բ�Ǿ���
//-----------------------------------------------------------------
void fillRoundRect(int x, int y, int w, int h, int r, u16 color) {
	fillRect(x+r, y, w-2*r, h, color);
	fillCircleHelper(x+w-r-1, y+r, r, 1, h-2*r-1, color);
	fillCircleHelper(x+r    , y+r, r, 2, h-2*r-1, color);
}
//-----------------------------------------------------------------
// ����������
//-----------------------------------------------------------------
void drawTriangle(int x0,int y0,int x1,int y1,int x2,int y2,u16 color){
	drawLine(x0, y0, x1, y1, color);
	drawLine(x1, y1, x2, y2, color);
	drawLine(x2, y2, x0, y0, color);
}
//-----------------------------------------------------------------
// ����ʵ��������
//-----------------------------------------------------------------
void fillTriangle(int x0,int y0,int x1,int y1,int x2,int y2,u16 color){
	int a, b, y, last;
	int dx01,dx02,dy01,dy02,dx12,dy12;
	long sa,sb;
	//��Y�����������(y2-y1-y0)
	if (y0 > y1) { swap(y0, y1); swap(x0, x1); }
	if (y1 > y2) { swap(y2, y1); swap(x2, x1); }
	if (y0 > y1) { swap(y0, y1); swap(x0, x1); }
	if(y0 == y2) { //������������һ��ˮƽ����
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
// ���Ƶ�ɫλͼ
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
// ����16λ��ͼ
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
// ���õ�ǰ���λ��
//-----------------------------------------------------------------
void setCursor(int x, int y) {
	cursor_x = x; cursor_y = y;//���¹��λ��
	LCD_SetArea(x,y,x,y);
}
//-----------------------------------------------------------------
// ����һ���ַ�
//-----------------------------------------------------------------
void drawChar(int x, int y, u8 c, u16 color, u16 bg, u8 sz) {
	char i,j;	u8 line;
	if((x >= ILI9341_TFTWIDTH)		||	//�����ҡ��¡�����Խ������
		 (y >= ILI9341_TFTHEIGHT)	||
		 ((x + 6 * sz - 1) < 0)		||
		 ((y + 8 * sz - 1) < 0))
			return;
	for(i = 0; i < 5; i++ ) { //ÿ���ַ���5�е����ֽڹ���(5*8)
		line = font[c * 5 + i];	//ȡ��i�е����ֽ�
		for(j = 0; j < 8; j++, line >>= 1) { //���Ƶ�i��8�����ص�
			if(line & 1) {			//Ϊ1��colorɫ����
				if(sz == 1)	drawPixel(x+i, y+j, color);//��������
				else fillRect(x+i*sz, y+j*sz, sz, sz, color);//�Ŵ����
			} else 	
			if(bg != color) {		//���Ϊ0�Ҳ�͸�����򰴱���ɫ����
				if(sz == 1)	drawPixel(x+i, y+j, bg);//��������
				else	fillRect(x+i*sz, y+j*sz, sz, sz, bg);//�Ŵ����
			}
		}
	}
	//���Ϊ��͸��ɫ�������1�а�����ɫ��1����ֱ��,�����γ��ַ���϶
	if(bg != color) {
		if(sz == 1)	drawFastVLine(x+5, y, 8, bg);//��������
		else		fillRect(x+5*sz, y, sz, 8*sz, bg);//�Ŵ����
	}
}
//-----------------------------------------------------------------
// �ڵ�ǰ���λ��дһ���ַ�
//-----------------------------------------------------------------
void write(u8 c, u16 color, u16 bg, u8 sz) {
	if(c == '\n') {
		cursor_x  = 0; cursor_y += sz * 8;		//���¹��λ��
	} 
	else if(c != '\r') {
		if((cursor_x + sz * 6) > ILI9341_TFTWIDTH) {
			cursor_x  = 0; cursor_y += sz * 8;	//���¹��λ��
		}
		drawChar(cursor_x, cursor_y, c, color, bg, sz);
		cursor_x += sz * 6;						//���¹��λ��
	}
}
//-----------------------------------------------------------------
// ��ʾ�����ַ���
//-----------------------------------------------------------------
void DrawChineseString(u16 x,u16 y,u16 color,u16 bg,u8 *s,u16 count) {
	u8 i,j,k;
	while(*s) {
		if((*s) >= 128) {	//����>=128����ʾ��������
			for (k = 0; k < count; k++) {
				//�����������ֿ���������в��ҵ�������
				if(	(hz16[k].inner_CODE[0] == *(s))&&	
					(hz16[k].inner_CODE[1] == *(s+1))) { 
					for(i = 0; i < 16; i++){	//��16��
						for(j = 0; j < 8; j++) { //��ʾ��ǰ����벿������
							if(hz16[k].Msk[i*2]&(0x80>>j))	
								drawPixel(x+j,y+i,color);
							else { if (color != bg) 
								drawPixel(x+j,y+i,bg); }
						}
						for(j = 0; j < 8; j++) { //��ʾ��ǰ���Ұ벿������
							if(hz16[k].Msk[i*2+1]&(0x80>>j))
								drawPixel(x+j+8,y+i,color);
							else if (color != bg)
								drawPixel(x+j+8,y+i,bg);
						}
						cursor_x = x+j+8*2; cursor_y = y+i;//���¹��λ��
					}
				}
			}
			s += 2; x += 16;	//�����ַ���������+2��������+16
		}
		else s++;				//����ΪӢ�İ���ַ�������+1������
	}
}