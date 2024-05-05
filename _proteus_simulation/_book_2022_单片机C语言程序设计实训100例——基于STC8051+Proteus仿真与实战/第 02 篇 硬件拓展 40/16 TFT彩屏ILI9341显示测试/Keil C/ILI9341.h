//-------------------------- ILI9341.h ----------------------------
//  ����: TFT����ILI9341��������ͷ�ļ�
//-----------------------------------------------------------------
#ifndef		__ILI9341__
#define		__ILI9341__
#include "STC15xxx.h"
#include "ILI9341.h"
#include <intrins.h>
#define u8 	unsigned char
#define u16	unsigned int
//-----------------------------------------------------------------
// ILI9341���Ŷ���(SPIģʽ)
//-----------------------------------------------------------------
sbit LCD_CS		= P0^0;					//Ƭѡ��ʹ�ܣ�
sbit LCD_SCL	= P0^1;					//ʱ����
sbit LCD_DC		= P0^2;					//�������data/command��
sbit LCD_SDI	= P0^3;					//��������ӻ���LCD������
sbit LCD_SDO	= P0^4;					//��������ӻ���LCD�����
sbit LCD_RST	= P0^5;					//��λ��
//-----------------------------------------------------------------
#define ILI9341_TFTWIDTH		240		//TFT���
#define ILI9341_TFTHEIGHT		320		//TFT�߶�
//-----------------------------------------------------------------
#define ILI9341_NOP				0x00	//NOP����
#define ILI9341_SWRESET			0x01	//�����λ
#define ILI9341_RDDID			0x04	//����ʾID
#define ILI9341_RDDST			0x09	//����ʾ״̬
//-----------------------------------------------------------------
#define ILI9341_SLPIN 			0x10	//����˯��ģʽ
#define ILI9341_SLPOUT			0x11	//�˳�˯��ģʽ
#define ILI9341_PTLON 			0x12	//�ֲ�ģʽ��
#define ILI9341_NORON 			0x13	//��������ʾģʽ
//-----------------------------------------------------------------
#define ILI9341_RDMODE  		0x0A	//����ʾ(��Դ)����ģʽ
#define ILI9341_RDMADCTL		0x0B	//����ʾMADCTL
#define ILI9341_RDPIXFMT		0x0C	//����ʾ���ظ�ʽ
#define ILI9341_RDIMGFMT		0x0D	//����ʾͼ���ʽ
#define ILI9341_RDSELFDIAG		0x0F	//����ʾ����Ͻ��
//-----------------------------------------------------------------
#define ILI9341_INVOFF  		0x20	//�رշ�ת��ʾ
#define ILI9341_INVON   		0x21	//����תģʽ
#define ILI9341_GAMMASET		0x26	//٤������
#define ILI9341_DISPOFF 		0x28	//����ʾ
#define ILI9341_DISPON  		0x29	//����ʾ
//-----------------------------------------------------------------
#define ILI9341_CASET  			0x2A	//�е�ַ����
#define ILI9341_PASET  			0x2B	//ҳ��ַ����
#define ILI9341_RAMWR  			0x2C	//�洢��д
#define ILI9341_RAMRD  			0x2E	//���洢��
//-----------------------------------------------------------------
#define ILI9341_PTLAR  			0x30	//�ֲ�����
#define ILI9341_MADCTL 			0x36	//�洢�����ʿ���
#define ILI9341_PIXFMT 			0x3A	//COLMOD�����ظ�ʽ����
//-----------------------------------------------------------------
#define ILI9341_FRMCTR1			0xB1	//֡���ʿ���1(����/ȫɫ)
#define ILI9341_FRMCTR2			0xB2	//֡���ʿ���2(����/8ɫ)
#define ILI9341_FRMCTR3			0xB3	//֡���ʿ���3(�ֲ�/ȫɫ)
#define ILI9341_INVCTR 			0xB4	//��ʾ��ת����
#define ILI9341_DFUNCTR			0xB6	//��ʾ���ܿ���
//-----------------------------------------------------------------
#define ILI9341_PWCTR1 			0xC0	//���Ŀ���1
#define ILI9341_PWCTR2 			0xC1	//���Ŀ���2
#define ILI9341_PWCTR3 			0xC2	//���Ŀ���3
#define ILI9341_PWCTR4 			0xC3	//���Ŀ���4
#define ILI9341_PWCTR5 			0xC4	//���Ŀ���5
#define ILI9341_VMCTR1 			0xC5	//VCOM����1
#define ILI9341_VMCTR2 			0xC7	//VCOM����2
//-----------------------------------------------------------------
#define ILI9341_RDID1  			0xDA	//��ID1
#define ILI9341_RDID2  			0xDB	//��ID2
#define ILI9341_RDID3  			0xDC	//��ID3
#define ILI9341_RDID4  			0xDD	//��ID4
//-----------------------------------------------------------------
#define ILI9341_GMCTRP1			0xE0	//����٤��У׼
#define ILI9341_GMCTRN1			0xE1	//����٤��У׼
//-----------------------------------------------------------------
// ��ɫ���ų�������
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