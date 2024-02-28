//---------------------------- main.c -----------------------------
//  ����: PG160128A(T6963C)Һ��ͼ����ʾ
//  ˵��: ��������ʾһ��ͼ��,�ɿ���ͼ�����,����,����"ͼ��"����ʱ,
//        ��������ʾһ������ͳ��ͼ.
//
//-----------------------------------------------------------------
#define	u8 	unsigned char
#define	u16	unsigned int
#define	MAIN_Fosc  12000000L		//������ʱ��
#include "STC15xxx.h"
#include "T6963C.h"
#include "PictureDots.h"
#include <intrins.h>
//���ض���
#define S1_ON() ((P0 & (1<<0)) == 0)	//������ʾ
#define S2_ON() ((P0 & (1<<1)) == 0)	//����
#define S3_ON() ((P0 & (1<<2)) == 0)	//����
#define S4_ON() ((P0 & (1<<3)) == 0)	//ͼ��
//��ǰ�������
u8 Current_Operation = 0;
//����ʾ��ͳ������
u8 Statistics_Data[] = {20,70,80,40,90,65,30};
extern const u8 LCD_WIDTH;
extern const u8 LCD_HEIGHT;
//-----------------------------------------------------------------
// ��������ͼ
//-----------------------------------------------------------------
void Draw_Bar_Graph(u8 d[]) {


}
extern u8 Read_LCD_Status();
//-----------------------------------------------------------------
// ������
//-----------------------------------------------------------------
void main() {
	u8 i,j,m,c = 0;  u16 k;
	P0M1 = 0xFF; P0M0 = 0x00;		//P0����Ϊ��������
	P2M1 = 0x00; P2M0 = 0x00;		//P2��P3����Ϊ׼˫���
	P3M1 = 0x00; P3M0 = 0x00;
	P2 = 0xFF; P3 = 0xFF;			//P2��P3��ʼ����ߵ�ƽ
	LCD_Initialise();				//��ʼ��LCD
	while(1) {
		if		(S1_ON()) Current_Operation = 1;	//����
		else if	(S2_ON()) Current_Operation = 2;	//����
		else if	(S3_ON()) Current_Operation = 3;	//����
		else if	(S4_ON()) Current_Operation = 4;	//ͼ��
		//�����������δ�ı����ִ����ʱ.
		if ( c == Current_Operation) { delay_ms(200); continue; }
		c = Current_Operation; 
		switch (Current_Operation) {
			case 1://�����򷴰���ʾ(��160x128Һ������ʾ160x80BMPͼ��,
			case 2://�����沿���ü���������. 

			
			case 3://������ʾ

			
			case 4://ͼ����ʾ
					Clear_Screen();
					LCD_Write_Command_P2(LCD_GRH_STP,0x00,0x00);
					Set_LCD_POS(0,0); 
					//����ͳ������������ʾ����ͼ
					Draw_Bar_Graph(Statistics_Data); 
					//��ʾͳ��ͼLabel(2011 B2Bͳ��ͼ��ʾ)
					Display_Str_at_xy(3,110, 
					(u8*)" 2021 B2B .\xCD\xB3\xBC\xC6\xCD\xBC\xCF\xD4\xCA\xBE.",0);
					//�����:\xCD\xB3\xBC\xC6\xCD\xBC\xCF\xD4\xCA\xBE�ֱ���:
					//"ͳ��ͼ��ʾ"������ֵ�����,�����ȡ�����ɲο�����˵��.
					break;
		}
	}
}
