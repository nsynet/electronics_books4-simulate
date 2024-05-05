//-----------------------------------------------------------------
//  ����: LM044LҺ��4λģʽ��������
//-----------------------------------------------------------------
#ifndef __LM044_4bit__
#define __LM044_4bit__
#include "STC15xxx.h"
#include <intrins.h>
#define u8  unsigned char
#define u16 unsigned int
//LCD���Ŷ���
sbit RS = P2^0;									//LCD�Ĵ���ѡ��
sbit RW = P2^1;									//LCD��д����
sbit EN = P2^2;									//LCDʹ�ܿ���
//Һ���˿ڶ���
#define LCD_PORT P2							//Һ���˿�(P2��4λ)
//LCD��غ���
void delay_ms(u8 x);						//��ʱ����
void Initialize_LCD();					//LCD��ʼ��
void LCD_Busy_Wait();						//æ�ȴ�
void Write_LCD_Dat(u8 dat);			//дLCD����
void Write_LCD_Cmd(u8 cmd);			//дLCDָ��
void LCD_ShowString(u8,u8,char*);//LCD��ʾ�ַ���
#endif