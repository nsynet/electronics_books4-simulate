//-----------------------------------------------------------------
// ����: 1602Һ����������
//-----------------------------------------------------------------
#ifndef ___LCD1602___
#define ___LCD1602___
#define u8  unsigned char
#define u16 unsigned int
#include "STC15xxx.h"
#include <intrins.h>
sbit RS = P2^0;			//�Ĵ���ѡ����
sbit RW = P2^1;			//��/д������
sbit EN = P2^2;			//ʹ�ܿ�����
void Write_LCD_Command(u8);
void Write_LCD_Data(u8);
void Initialize_LCD();
void LCD_ShowString(u8,u8,char*);
void DisplayOneChar(u8 r, u8 c, char d);
#endif