//-----------------------------------------------------------------
//  ����: LM041L-4bitҺ����������ͷ�ļ���4λģʽ��
//-----------------------------------------------------------------
#ifndef __LM041L_4BIT__
#define __LM041L_4BIT__
#include "STC15xxx.h"
#include <intrins.h>
#define u8  unsigned char
#define u16 unsigned int
//LCD���Ŷ���
sbit RS = P0^0;  			//�Ĵ���ѡ����
sbit RW = P0^1;	 			//��/д������
sbit EN = P0^2;	 			//ʹ�ܿ�����
//Һ���˿ڶ���
#define LCD_PORT P0							//Һ���˿�(P0��4λ)
//LCD��غ���
void delay_ms(u8 x);						//��ʱ����
void Initialize_LCD();					//LCD��ʼ��
void LCD_Busy_Wait();						//æ�ȴ�
void Write_LCD_Dat(u8 dat);			//дLCD����
void Write_LCD_Cmd(u8 cmd);			//дLCDָ��
void LCD_ShowString(u8,u8,char*);//LCD��ʾ�ַ���
#endif