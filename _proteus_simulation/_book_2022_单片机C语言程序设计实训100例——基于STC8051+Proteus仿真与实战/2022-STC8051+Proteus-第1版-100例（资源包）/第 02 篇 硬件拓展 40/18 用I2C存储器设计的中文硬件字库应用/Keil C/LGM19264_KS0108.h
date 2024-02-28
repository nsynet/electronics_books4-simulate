//-----------------------------------------------------------------
//  ����: LGM19264(KS0109)Һ��ͷ�ļ�
//-----------------------------------------------------------------
#ifndef ___LGM19264_KS0108___
#define ___LGM19264_KS0108___
#define u8   unsigned char
#define u16  unsigned int
//LCD��ʼ��/ҳ/��ָ���
#define LCD_PAGE			0xB8		//ҳָ��(X)
#define LCD_START_ROW	0xC0		//��ʼ��(XF)
#define LCD_COL				0x40		//��ָ��(Y)
//Һ����������
sbit D_I = P3^0;							//����/ָ��ѡ����
sbit R_W = P3^1;							//��д������
sbit E 	=  P3^2;							//ʹ�ܿ�����
sbit CS1 = P3^3;							//����ѡ��
sbit CS2 = P3^4;							//����ѡ��
sbit CS3 = P3^5;							//����ѡ��
sbit RST = P3^6;							//��λ
//æ��־λ
sbit BUSY_STATUS =	P0^7;			//æ��־λ
//Һ���˿�
#define LCD_PORT  	P0				//Һ�����ݶ˿�
//-----------------------------------------------------------------
// ��������
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