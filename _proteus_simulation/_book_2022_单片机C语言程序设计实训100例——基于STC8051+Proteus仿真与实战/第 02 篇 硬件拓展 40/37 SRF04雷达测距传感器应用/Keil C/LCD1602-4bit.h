//-----------------------------------------------------------------
//  ����: LCD1602Һ����������ͷ�ļ���4λģʽ��
//-----------------------------------------------------------------
#include "STC15xxx.h"
#include <intrins.h>
#define u8  unsigned char
#define u16 unsigned int
//LCD���Ŷ���
sbit RS = P1^0;									//LCD�Ĵ���ѡ��
sbit RW = P1^1;									//LCD��д����
sbit EN = P1^2;									//LCDʹ�ܿ���
//Һ���˿ڶ���
#define LCD_PORT P1							//Һ���˿�(P1��4λ)
//LCD��غ���
void delay_ms(u8 x);						//��ʱ����
void Initialize_LCD();					//LCD��ʼ��
void LCD_Busy_Wait();						//æ�ȴ�
void Write_LCD_Dat(u8 dat);			//дLCD����
void Write_LCD_Cmd(u8 cmd);			//дLCDָ��
void LCD_ShowString(u8,u8,char*);//LCD��ʾ�ַ���