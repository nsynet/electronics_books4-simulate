//-------------------------- main.c -------------------------------
//  ����: ������ѹ������BMP180Ӧ��
//-----------------------------------------------------------------
//  ˵��: ��������ʱ,1602Һ��������ˢ����ʾBMP180��ǰ�¶�����ѹ���ݡ�
//
//-----------------------------------------------------------------
#define u8  unsigned char
#define u16 unsigned int
#define u32 unsigned long
#define MAIN_Fosc	12000000L	//ϵͳʱ��Ƶ��12MHz
#include "STC15xxx.h"
#include <intrins.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
extern Init_BMP180();
extern BMP180Convert();
extern Initialize_LCD();
extern void delay_ms(u8);
extern void LCD_ShowString(u8, u8,char*);
extern void DisplayOneChar(u8 r, u8 c, char d);
//-----------------------------------------------------------------
// ������
//-----------------------------------------------------------------
void main() { 
	P1M1 = 0; P1M0 = 0;			//����Ϊ׼˫���
	P2M1 = 0; P2M0 = 0;
	P3M1 = 0; P3M0 = 0;
	delay_ms(50);				//�ϵ���ʱ
	Initialize_LCD();			//Һ����ʼ��
	Init_BMP180();				//��ʼ��BMP180 
	while(1){					//ѭ��

	
	}
}
