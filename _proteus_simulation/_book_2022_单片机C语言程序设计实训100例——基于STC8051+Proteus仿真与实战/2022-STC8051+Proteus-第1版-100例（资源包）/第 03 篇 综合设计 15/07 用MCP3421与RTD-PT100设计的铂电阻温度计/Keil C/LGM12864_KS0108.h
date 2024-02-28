//-----------------------------------------------------------------
//  ����: LGM12864Һ��ͷ�ļ�
//-----------------------------------------------------------------
#define u8   unsigned char
#define u16  unsigned int
//LCD��ʼ��/ҳ/��ָ���
#define LCD_START_ROW	0xC0		//��ʼ��
#define LCD_PAGE			0xB8		//ҳָ��
#define LCD_COL				0x40		//��ָ��
//Һ����������
sbit E 	=  P3^0;							//ʹ�ܿ�����
sbit R_W = P3^1;							//��д������
sbit D_I = P3^2;							//����/ָ��ѡ����
sbit CS1 = P3^3;							//�Ұ���ѡ��
sbit CS2 = P3^4;							//�Ұ���ѡ��
sbit RST = P3^5;							//��λ
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
void LCD_Write_Command(u8 cmd);
void LCD_Write_Data(u8 dat);
void Common_Show(u8 P,u8 L,u8 W,u8 *r);
void Display_A_Char_8X16(u8 P,u8 L,u8 *M);
void Display_A_WORD(u8 P,u8 L,u8 *M);
void Display_A_WORD_String(u8 P,u8 L,u8 C,u8 *M);