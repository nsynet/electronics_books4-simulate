//---------------------------- main.c -----------------------------
//  ����: IIC�洢����Ƶ�����Ӳ���ֿ�Ӧ��
//-----------------------------------------------------------------
//  ˵��: ������262K��16*16���������ֿ��ļ�HZK16���Ϊ����128K�ļ�,
//		�ֱ𱣴浽��Ƭ24C1024��,������6KB���س�,���б���ʱ,����
//		��������ĺ��ֻ����ı������,�����ֱ�Ӵ�24C1024�������
//		�ֿ�����ȡ����ת��ΪҺ����ʽ,��ʾ������Һ������.
//
//-----------------------------------------------------------------
#include "STC15xxx.h"
#include <intrins.h>
#include <string.h>	
#define u8	unsigned char
#define u16	unsigned int
#define u32	unsigned long
//LCD��غ�������
void LCD_Initialize();
void Disp_A_Char(u8,u8,u8 *);
void Disp_CHN_String(u8,u8,u8,u8 *); 
void Disp_Image(u8,u8,u8,u8,u8 * );
//I2C��غ���
void IIC_Init();
u8 IIC_ReadBytes(u8 Slave,u32 Mem_address,u8 *Buf,u8 N);
void delay_ms(u8 x);
//�Ӻ��ֿ�ȡ�õ�һ�����ֵĵ�������
u8 Word_Dot_Matrix[32];
//ת��ΪLCD��ʾ��ʽ�ĺ��ֵ�������
u8 LCD_Dot_Matrix[32];
//���������������ʫ��,ע��������ʹ������ȫ�Ƿ�ʽ����
//����ʱ�����ַ������ܳ������룬��ʱ�ɽ��������ݻ򲿷�������"����"��ϱ�ʾ
//��������ʫ���е����һ�䣺"�������󾡿��ա�"
code char Poem[9][17] = {
	"�������Զ���ѣ�","��ˮǧɽֻ���С�","����������ϸ�ˣ�","���ɰ��������衣",
	"��ɳˮ������ů��","����ź���������","��ϲ�ɽǧ��ѩ��",//"�������󾡿��ա�"
	"\xC8\xFD\xBE\xFC\xB9\xFD\xBA\xF3\xBE\xA1\xBF\xAA\xD1\xD5\xA1\xA3"
};
//������Ϣ���������������ʽ��ʾ������������һ�״ʣ�
//ע����ǰ������������֧�ֲ����ã����ܳ��ָ������룬
//������������������ѡ��ֱ��ʹ���������飬��������ȶ���
//code char Poem[][17] = {
//	"����º�δ������","��������Ҷ���ơ�","��ʮһ�껹�ɹ���","�仨ʱ�ڶ����¡�",
//	"��ɧ̫ʢ�����ϣ�","���ﳤ�˷�������","Ī��������ˮǳ��","����ʤ����������"
//};
//char code Poem[][17] = {
//"\xD2\xFB\xB2\xE8\xD4\xC1\xBA\xA3\xCE\xB4\xC4\xDC\xCD\xFC\xA3\xAC",
//"\xCB\xF7\xBE\xE4\xD3\xE5\xD6\xDD\xD2\xB6\xD5\xFD\xBB\xC6\xA1\xA3",
//"\xC8\xFD\xCA\xAE\xD2\xBB\xC4\xEA\xBB\xB9\xBE\xC9\xB9\xFA\xA3\xAC",
//"\xC2\xE4\xBB\xA8\xCA\xB1\xBD\xDA\xB6\xC1\xBB\xAA\xD5\xC2\xA1\xA3",
//"\xC0\xCE\xC9\xA7\xCC\xAB\xCA\xA2\xB7\xC0\xB3\xA6\xB6\xCF\xA3\xAC",
//"\xB7\xE7\xCE\xEF\xB3\xA4\xD2\xCB\xB7\xC5\xD1\xDB\xC1\xBF\xA1\xA3",
//"\xC4\xAA\xB5\xC0\xC0\xA5\xC3\xF7\xB3\xD8\xCB\xAE\xC7\xB3\xA3\xAC",
//"\xB9\xDB\xD3\xE3\xCA\xA4\xB9\xFD\xB8\xBB\xB4\xBA\xBD\xAD\xA1\xA3"};
//�����������ֽ�������ʽ
//char code Poem[][17] = {
//{0xD2,0xFB,0xB2,0xE8,0xD4,0xC1,0xBA,0xA3,0xCE,0xB4,0xC4,0xDC,0xCD,0xFC,0xA3,0xAC,0x00},
//{0xCB,0xF7,0xBE,0xE4,0xD3,0xE5,0xD6,0xDD,0xD2,0xB6,0xD5,0xFD,0xBB,0xC6,0xA1,0xA3,0x00},
//{0xC8,0xFD,0xCA,0xAE,0xD2,0xBB,0xC4,0xEA,0xBB,0xB9,0xBE,0xC9,0xB9,0xFA,0xA3,0xAC,0x00},
//{0xC2,0xE4,0xBB,0xA8,0xCA,0xB1,0xBD,0xDA,0xB6,0xC1,0xBB,0xAA,0xD5,0xC2,0xA1,0xA3,0x00},
//{0xC0,0xCE,0xC9,0xA7,0xCC,0xAB,0xCA,0xA2,0xB7,0xC0,0xB3,0xA6,0xB6,0xCF,0xA3,0xAC,0x00},
//{0xB7,0xE7,0xCE,0xEF,0xB3,0xA4,0xD2,0xCB,0xB7,0xC5,0xD1,0xDB,0xC1,0xBF,0xA1,0xA3,0x00},
//{0xC4,0xAA,0xB5,0xC0,0xC0,0xA5,0xC3,0xF7,0xB3,0xD8,0xCB,0xAE,0xC7,0xB3,0xA3,0xAC,0x00},
//{0xB9,0xDB,0xD3,0xE3,0xCA,0xA4,0xB9,0xFD,0xB8,0xBB,0xB4,0xBA,0xBD,0xAD,0xA1,0xA3,0x00}};
//-----------------------------------------------------------------
// 5000ms��ʱ@12MHz
//-----------------------------------------------------------------
void Delay5000ms() { 
	u8 i = 228, j = 253, k = 219;
	_nop_(); _nop_();
	do {
		do {
			while (--k);
		} while (--j);
	} while (--i);
}
//-----------------------------------------------------------------
// ��ȡ���ֵ��󲢽��ֿ�����ʽת��Ϊ������Һ��������ȡģ��ʽ
//-----------------------------------------------------------------
void Read_HZ_dot_Matrix_AND_Convert_TO_LCD_Fmt(u8 c[]) {  
	u32 Offset;							//�����ڵ�����е�ƫ��λ��
	u8 SectionCode, PlaceCode;			//����������λ��
	u8 AT24C1024_A1;					//��ʶ24C1024оƬ���0,1
	u8 i,j,LCD_Byte,Block;				//��ʽת������
	u8 Idx[4] = {0,1,16,17};			//�ĸ����ת������ʼ�ֽ�����
	SectionCode	= c[0] - 0xA0;			//ȡ�ú�����λ��
	PlaceCode	= c[1] - 0xA0;
	Offset = (94L*(SectionCode-1)+(PlaceCode-1))*32L;	//����ƫ��
	//ȡ��ƫ�Ƶ�ַOffset�ĵ�18λ, AT24C1024_A1Ϊ0ʱ��ʾ
	//�ú��ֵ������ֿ�ǰ���,�����ڵ�һƬ24C1024,
	//�����ʾ�ú��ֵ������ֿ����,���ڵڶ�Ƭ24C1024��.
	AT24C1024_A1 = Offset >> 17; 
	Offset &= 0x0001FFFF;
	//��Offset��ʼ��ȡ�ú���32���ֽڵĵ�������
	if (AT24C1024_A1==0)IIC_ReadBytes(0xA0,Offset,Word_Dot_Matrix,32);
	else				 IIC_ReadBytes(0xA4,Offset,Word_Dot_Matrix,32);
	//��16*16�����Ϊ�ĸ�8*8�����������ת��
	//�������ϰ벿�����°벿��ռ��������
	for (Block = 0; Block < 4; Block++) {
		for (i = 0; i < 8; i++) {
			LCD_Byte = 0x00; 
			for( j = 0; j < 8; j++) {
				if ((Word_Dot_Matrix[Idx[Block] + 2*j]&(0x80>>i))!=0x00)
				LCD_Byte |= 0x01 << j;
			}
			LCD_Dot_Matrix[i + Block * 8] = LCD_Byte;
		}
	}
}
//-----------------------------------------------------------------
// ������
//-----------------------------------------------------------------
void main() {
	u8 i,j;
	P0M1 = 0; P0M0 = 0;	//����Ϊ׼˫���
	P2M1 = 0; P2M0 = 0;
	P3M1 = 0; P3M0 = 0;
	LCD_Initialize();		//��ʼ��LCD
	while (1) {

	
	}
}