//------------------------ T6963C.h -------------------------
//  ����: PG160128��ʾ��������ͷ�ļ�
//-----------------------------------------------------------
#ifndef __T6963C__
#define __T6963C__
//-----------------------------------------------------------
#define u8 	unsigned char
#define u16	unsigned int
#include "STC15xxx.h"
#define  MAIN_Fosc  12000000L   	//������ʱ��
#include <stdio.h>
#include <math.h>
#include <string.h>
void delay_ms(u8);
void Delay10us();
void Delay20us();
//-----------------------------------------------------------
// T6963C �����
//-----------------------------------------------------------
#define LCD_CUR_POS		0x21		//���ù��λ��(����Ļ�ϵ�λ��)
#define LCD_CGR_POS		0x22		//����CGRAMƫ�õ�ַ
#define LCD_ADD_POS		0x24		//����DDRAM��ַ
#define LCD_TXT_STP		0x40		//�ı�����ַ
#define LCD_TXT_WID		0x41		//�ı������
#define LCD_GRH_STP		0x42		//ͼ������ַ
#define LCD_GRH_WID		0x43		//ͼ�������
#define LCD_MOD_OR		0x80		//��ʾ��ʽ:�߼���
#define LCD_MOD_XOR		0x81		//��ʾ��ʽ:�߼����
#define LCD_MOD_AND		0x82		//��ʾ��ʽ:�߼���
#define LCD_MOD_TCH		0x83		//��ʾ��ʽ:�ı�����
#define LCD_DIS_SW		0x90		//��ʾ����
//D0=1/0:�����˸����/����;D1=1/0:�����ʾ����/���ã�
//D2=1/0:�ı���ʾ����/����;D3=1/0:ͼ����ʾ����/���ã�
#define LCD_CUR_SHP		0xA0		//�����״ѡ��(1��,2��,...8��[��״]���)
#define LCD_AUT_WR		0xB0		//�Զ�д����
#define LCD_AUT_RD		0xB1		//�Զ�������
#define LCD_AUT_OVR		0xB2		//�Զ���/д����
#define LCD_INC_WR		0xC0		//����д,��ַ��1
#define LCD_INC_RD		0xC1		//���ݶ�,��ַ��1
#define LCD_DEC_WR		0xC2		//����д,��ַ��1
#define LCD_DEC_RD		0xC3		//���ݶ�,��ַ��1
#define LCD_NOC_WR		0xC4		//����д,��ַ����
#define LCD_NOC_RD		0xC5		//���ݶ�,��ַ����
#define LCD_SCN_RD		0xE0		//����Ļ
#define LCD_SCN_CP		0xE8		//��Ļ����
#define LCD_BIT_OP		0xF0		//λ����
//-----------------------------------------------------------
// ���LCD��MCU������ʱ,ֻ���޸��������ݡ����ƶ˿ڼ��������Ŷ���
//-----------------------------------------------------------
//LCD����(����)�˿ڶ���
#define LCD_DATA_PORT		P2
//LCD�������Ŷ���(��,д,����/���ݼĴ�ѡ��,ʹ��)
sbit WR = P3^0;			//дʹ��
sbit RD = P3^1;			//��ʹ��
sbit CD = P3^2;			//����/���ݼĴ���ѡ���� (Command/Data)
sbit CE = P3^3;			//LCDʹ��
//-----------------------------------------------------------
// LCD������غ���
//-----------------------------------------------------------
u8 Status_BIT_01();//״̬λSTA1,STA0�жϣ�дָ������Ͷ�д���ݾ�����
u8 Status_BIT_3(); //״̬λST3�жϣ������Զ�д״̬��
u8 LCD_Write_Command(u8);								//д�޲���ָ��
u8 LCD_Write_Command_P1(u8,u8);					//д������ָ��
u8 LCD_Write_Command_P2(u8,u8,u8);			//д˫����ָ��
u8 LCD_Write_Data(u8 dat);							//д����
u8 LCD_Read_Data();											//������
void Display_Str_at_xy(u8,u8,char [],u8);	//��ָ��λ����ʾ�ַ���
void LCD_Initialise();									//LCD��ʼ��
void Clear_Screen();										//����
void Set_LCD_POS(u8, u8);								//���õ�ǰ��ַ
void OutToLCD(u8,u8,u8);								//�����Һ��
void Line(u8, u8, u8, u8, u8);					//����ֱ��
void Pixel(u8,u8, u8);									//��� 
void Draw_Image(u8*, u8, u8);						//����λͼ 
//-----------------------------------------------------------
#endif