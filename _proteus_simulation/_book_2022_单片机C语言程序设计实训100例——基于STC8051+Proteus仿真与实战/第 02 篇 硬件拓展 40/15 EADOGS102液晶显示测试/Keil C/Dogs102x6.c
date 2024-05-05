//------------------------ Dogs102x6.c ----------------------------
//  ���ƣ�EADOGS102Һ����������
//-----------------------------------------------------------------
#include "STC15xxx.h"
#include "Dogs102x6.h"
#include <intrins.h>
#ifndef abs
# define abs(n) (((n) < 0) ? -(n) : (n))
#endif
extern void delay_ms(u16);
//EADOGS�����CD����Ϊ0��
#define SET_COLUMN_ADDRESS_MSB		0x10	//�����е�ַ��4λ
#define SET_COLUMN_ADDRESS_LSB		0x00	//�����е�ַ��4λ
#define SET_POWER_CONTROL			0x2F	//��Դ���ƣ�����
#define SET_SCROLL_LINE				0x40	//ͼ���Ϲ���0��63��
#define SET_PAGE_ADDRESS			0xB0	//����ҳ��ַ��0��7��
#define SET_VLCD_RESISTOR_RATIO		0x27	//���õ����ʵ��ڶԱȶ�
#define SET_ELECTRONIC_VOLUME_MSB	0x81	//���öԱȶ�����(��1�ֽ�)
#define SET_ELECTRONIC_VOLUME_LSB	0x0F	//���öԱȶȲ���(��2�ֽ�)
#define SET_ALL_PIXEL_ON			0xA4	//��ֹ����������ʾ����Ӱ���ڴ棩
#define SET_INVERSE_DISPLAY			0xA6	//������ʾ
#define SET_DISPLAY_ENABLE			0xAF	//ʹ����ʾ
#define SET_SEG_DIRECTION 			0xA1	//�ξ�����ʾ
#define SET_COM_DIRECTION 			0xC8	//�о�����ʾ
#define SYSTEM_RESET				0xE2	//��λϵͳ
#define NOP							0xE3	//�޲���
#define SET_LCD_BIAS_RATIO			0xA2	//���õ�ѹб��
#define SET_CURSOR_UPDATE_MODE		0xE0	//�е�ַ����
#define RESET_CURSOR_UPDATE_MODE	0xEE	//��֮ǰ�Ĺ��λ���Ƶ��е�ַλ��
#define SET_ADV_PROGRAM_CONTROL0_MSB	0xFA	//�¶Ȳ�������(��1�ֽ�)
#define SET_ADV_PROGRAM_CONTROL0_LSB	0x90	//�¶Ȳ�������(��2�ֽ�)
//-----------------------------------------------------------------
// EADOGS���Ŷ���
sbit SI	= P0^0;
sbit SCK= P0^1;
sbit CD	= P0^2;
sbit CS	= P0^3;
sbit RST= P0^4;
//-----------------------------------------------------------------
const u8 FONT6x8[] = { //ASCII�ַ���ģ
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
	//96�ֽ�
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
	//96*2=192�ֽ�
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
	//96*3=288�ֽ�
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
	//96*4=384�ֽ�
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
	//96*5=480�ֽ�
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
	//96*6=576�ֽ�
	//����Ϊ�����ַ�����ASCII�ַ�
	0x00, 0x00, 0xFE, 0x82, 0x82, 0x82, // [
	0x82, 0x82, 0x82, 0xFE, 0x00, 0x00  //  ]
};
u8 dogs102x6Memory[816 + 2];			//Һ���ڴ渱��
u8 currentPage = 0, currentColumn = 0;	//��ǰҳ����ǰ��
u8 backlight  = 8;						//��������
u8 contrast = 0x0F;						//�Աȶ�
// Dog102-6��ʼ������
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
// ͨ��SPI�ӿ���ǰ��ַд��һ�ֽ�����
//-----------------------------------------------------------------
void WriteByte(u8 dat) {
	u8 i;
	for(i = 0; i < 8; i++) {		//����д��8λ����
		dat <<= 1;	SI = CY;		//dat����λ,��λ������CY,���͸�λ
		SCK = 0;	SCK = 1;		//ʱ����������д������
	}
}
//-----------------------------------------------------------------
// Һ����ʼ��
//-----------------------------------------------------------------
void Dogs102x6_init() {
	RST = 0; RST = 1; CS = 0; CD = 0;
	Dogs102x6_writeCommand(Dogs102x6_initMacro, 13); 
	CS = 1;	//��ֹƬѡ
	dogs102x6Memory[0] = 102;
	dogs102x6Memory[1] = 8;
}
//-----------------------------------------------------------------
// ��ֹ��ʾ
//-----------------------------------------------------------------
void Dogs102x6_disable() {
	u8 cmd[1] = { SYSTEM_RESET };
	Dogs102x6_writeCommand(cmd, 1);
	cmd[0] = SET_DISPLAY_ENABLE & 0xFE;
	Dogs102x6_writeCommand(cmd, 1);
}
//-----------------------------------------------------------------
// дҺ������
//-----------------------------------------------------------------
void Dogs102x6_writeCommand(u8 *sCmd, u8 i) {
	CS = 0; CD = 0;
	while (i--) { WriteByte(*sCmd++); delay_ms(2); }
	CS = 1;
}
//-----------------------------------------------------------------
// дҺ������
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
// ����Һ����ַ������Ϊ0,0,paΪ0~7ҳ,caΪ0-101��
//-----------------------------------------------------------------
void Dogs102x6_setAddress(u8 pa, u8 ca) {
	u8 cmd[1],H = 0x00,L = 0x00;
	u8 ColumnAddress[]={SET_COLUMN_ADDRESS_MSB, SET_COLUMN_ADDRESS_LSB };
	if (pa > 7) 	pa = 7; 					//ҳ�߽����
	if (ca > 101)	ca = 101;					//�б߽����
	//����ҳ��ַ����
	cmd[0] = SET_PAGE_ADDRESS + (7 - pa);
	currentPage 	= pa;
	currentColumn	= ca;
	//�ֱ�����Ϊ���ֽ�����ֽ�
	L = (ca & 0x0F);
	H = (ca & 0xF0);
	H = (H >> 4);
	ColumnAddress[0] = SET_COLUMN_ADDRESS_LSB + L;
	ColumnAddress[1] = SET_COLUMN_ADDRESS_MSB + H; 
	Dogs102x6_writeCommand(cmd, 1);				//����ҳ��ַ
	Dogs102x6_writeCommand(ColumnAddress, 2);	//�����е�ַ
}
//-----------------------------------------------------------------
// ������ʾ
//-----------------------------------------------------------------
void Dogs102x6_setInverseDisplay() {
	u8 cmd[] = {SET_INVERSE_DISPLAY + 0x01};
	Dogs102x6_writeCommand(cmd, 1);
}
//-----------------------------------------------------------------
// ���������ʾ
//-----------------------------------------------------------------
void Dogs102x6_clearInverseDisplay() {
	u8 cmd[] = {SET_INVERSE_DISPLAY};
	Dogs102x6_writeCommand(cmd, 1);
}
//-----------------------------------------------------------------
// ��������
//-----------------------------------------------------------------
void Dogs102x6_scrollLine(u8 lines) {
	u8 cmd[] = {SET_SCROLL_LINE}; 
	if (lines > 0x1F) cmd[0] |= 0x1F; else cmd[0] |= lines;
	Dogs102x6_writeCommand(cmd, 1);
}
//-----------------------------------------------------------------
// ��������ȫ��
//-----------------------------------------------------------------
void Dogs102x6_setAllPixelsOn() {
	u8 cmd[] = {SET_ALL_PIXEL_ON + 0x01};
	Dogs102x6_writeCommand(cmd, 1);
}
//-----------------------------------------------------------------
// �����������
//-----------------------------------------------------------------
void Dogs102x6_clearAllPixelsOn() {
	u8 cmd[] = {SET_ALL_PIXEL_ON}; 
	Dogs102x6_writeCommand(cmd, 1);
}
//-----------------------------------------------------------------
// ����
//-----------------------------------------------------------------
void Dogs102x6_clearScreen() {
	u8 LcdData[] = {0x00}, p, c;
	for (p = 0; p < 8; p++) {				//8ҳ��ʾ
			Dogs102x6_setAddress(p, 0);
			for (c = 0; c < 102; c++) {		//ÿҳ102��
				Dogs102x6_writeData(LcdData, 1);
			}
	}
}
//-----------------------------------------------------------------
// ��ָ��ҳ/�����1�ַ�:pageΪ0~7ҳ,colΪ0~101��,fΪ����,styleΪ���
// ע��ÿ���ַ���1ҳ��ռ6��,8��
//-----------------------------------------------------------------
void Dogs102x6_charDraw(u8 page, u8 col, u16 f, u8 style) {
	u8 b, inverted_char[6];	//������ʾ����
	u16 h;
	if (page > 7) 	page	= 7;
	if (col > 101)	col 	= 101; 
	if (f < 32 || f > 129) f = '.';
	h = (f - 32) * 6;		//�������ַ�ASCII����Ϊ32,ÿ���ַ�����Ϊ6�ֽ�
	Dogs102x6_setAddress(page, col);
	if (style == DOGS102x6_DRAW_NORMAL) {	//������ʾ
		Dogs102x6_writeData((u8 *)FONT6x8 + h, 6);
	}
	else {
		for (b = 0; b < 6; b++) {			//������ʾ
			inverted_char[b] = FONT6x8[h + b] ^ 0xFF;
		}
		Dogs102x6_writeData(inverted_char, 6);
	}
}
//-----------------------------------------------------------------
// ��ָ���������1�ַ�:xΪ0~101ҳ,yΪ0~63��,fΪ����,styleΪ���
//-----------------------------------------------------------------
void Dogs102x6_charDrawXY(u8 x, u8 y, u16 f, u8 style) {
	u8 b, page, desired_char[12];
	u16 h;
	if (x >= 102) x = 101;
	if (y >= 64) y = 63;
	if (f < 32 || f > 129) f = '.'; 
	h = (f - 32) * 6;
	page = y / 8;	//��������ת��Ϊҳ
	if (style == DOGS102x6_DRAW_NORMAL) {	//������ʾ
		for (b = 0; b < 6; b++) {
			desired_char[b] =
				(FONT6x8[h + b] >> (y % 8)) | 
				dogs102x6Memory[2 + (page * 102) + x + b];
			desired_char[b + 6] =
				FONT6x8[h + b] << (8 - y % 8) | 
				dogs102x6Memory[2 + ((page + 1) * 102) + x + b];
		}
	}
	else {									//������ʾ
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
// ��ָ��ҳ/������ַ���������row��ʾҳ����Ҫ���Ϊ�У�
//-----------------------------------------------------------------
void Dogs102x6_stringDraw(u8 row, u8 col, char *word, u8 style) {
	u8 a = 0; 
	if (row > 7) row = 7;
	if (col > 101) col = 101;
	while (word[a] != 0) {
		if (word[a] != 0x0A) {				//�ǻس����з�
			if (word[a] != 0x0D) {
				Dogs102x6_charDraw(row, col, word[a], style);
				col += 6;
				if (col >= 102) {
					col = 0; if (row < 7) row++; else row = 0;
				}
			}
		}
		else {								//����س����з�
			if (row < 7) row++; else row = 0;
			col = 0;
		}
		a++;
	}
}
//-----------------------------------------------------------------
// ��ָ����������ַ���
//-----------------------------------------------------------------
void Dogs102x6_stringDrawXY(u8 x, u8 y, char *word, u8 style) {
	u8 a = 0;
	while (word[a] != 0) {
		Dogs102x6_charDrawXY(x, y, word[a], style);
		x += 6;
		if (x >= 102){	//���д���
			x = 0;
			if (y + 8 < 64)	y += 8; else y = 0;
		}
		a++;
	}
}
//-----------------------------------------------------------------
// ���ָ��ҳ
//-----------------------------------------------------------------
void Dogs102x6_clearRow(u8 page){
	u8 cmd[] = {0}, a = 0;
	if (page > 7) page = 7; 
	Dogs102x6_setAddress(page, 0);			//���õ���pageҳ
	for (a = 0; a < 102; a++) {				//�ڸ�ҳ102����ȫ�����0
		Dogs102x6_writeData(cmd, 1);
		dogs102x6Memory[2 + (page * 102) + a] = 0x00;
	}
}
//-----------------------------------------------------------------
// ��ָ������������ص�
//-----------------------------------------------------------------
void Dogs102x6_pixelDraw(u8 x, u8 y, u8 style) {
	u8 p, temp; 
	if (x > 101) x = 101;
	if (y > 63) y = 63;
	p = y / 8; //ת��Ϊҳ
	temp = 0x80 >> (y % 8);	//ȷ��ҳ�����ظ߶�
	if (style == DOGS102x6_DRAW_NORMAL)	//��������
		dogs102x6Memory[2 + (p * 102) + x] |= temp;
	else
		dogs102x6Memory[2 + (p * 102) + x] &= ~temp;
	Dogs102x6_setAddress(p, x);
	//�������ص�
	Dogs102x6_writeData(dogs102x6Memory + (2 + (p * 102) + x), 1);
}
//-----------------------------------------------------------------
// ����ˮƽ��
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
		if (style == DOGS102x6_DRAW_NORMAL){	//׼������������
			dogs102x6Memory[2 + (p * 102) + a] |= temp;
		}
		else 	{								//׼������������
			dogs102x6Memory[2 + (p * 102) + a] &= ~temp;
		}
		a++;
	}
	//��ָ��λ���������
	Dogs102x6_setAddress(p, x1);
	Dogs102x6_writeData(dogs102x6Memory+(2+(p*102)+x1),x2-x1+1);
}
//-----------------------------------------------------------------
// ���ƴ�ֱ��
//-----------------------------------------------------------------
void Dogs102x6_verticalLineDraw(u8 y1, u8 y2, u8 x, u8 style){
	u8 temp1 = 0, temp2 = 0, p1, p2, a; 
	if (y1 > 63) y1 = 63;
	if (y2 > 63) y2 = 63;
	if (x > 101) x = 101;
	if (y1 > y2) { temp1 = y1; y1 = y2;  y2 = temp1; }
	p1 = y1 / 8;
	p2 = y2 / 8;
		temp2 = 8 - (y2 % 8);	//��������
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
// ��������(x1,y1)-(x2,y2)����ֱ��
//-----------------------------------------------------------------
void Dogs102x6_lineDraw(u8 x1, u8 y1, u8 x2, u8 y2, u8 style){
	i8 x, y, deltay, deltax, d;
	i8 x_dir, y_dir;
	if (y1 > 63)	y1 = 63;
	if (y2 > 63)	y2 = 63;
	if (x1 > 101)	x1 = 101;
	if (x2 > 101)	x2 = 101;
	//ָ���߶�Ϊֱ�ߣ���ֱ��ˮƽ��
	if (x1 == x2) Dogs102x6_verticalLineDraw(y1, y2, x1, style);
	else if (y1 == y2) Dogs102x6_horizontalLineDraw(x1, x2, y1, style);
	//����Ϊб��
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
// ����Բ��
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
// ��ָ��λ�����λͼ
//-----------------------------------------------------------------
void Dogs102x6_imageDraw(const u8 IMAGE[], u8 row, u8 col) {
	// height in rows (row = 8 pixels), width in columns
	u8 a, height, width;
	width = IMAGE[0]; //ͼƬ�ߴ籣����ͼƬ�������ݵ���ǰ��2�ֽ�
	height = IMAGE[1] / 8;
	for (a = 0; a < height; a++) {
		Dogs102x6_setAddress(row + a, col);
		// Draw a row of the image
		Dogs102x6_writeData((u8*)IMAGE + 2 + a * width, width);
	}
}
//-----------------------------------------------------------------
// ���ָ�������λ��
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