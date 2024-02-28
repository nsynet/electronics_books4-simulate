//-------------------------- main.c -------------------------------
//  ����: 1-Wire�����¶ȴ�����DS18B20Ӧ�ò���
//-----------------------------------------------------------------
//  ˵��: ���б���ʱ,����¶Ƚ�ʵʱˢ����ʾ��1602LCD��.
//
//-----------------------------------------------------------------
#include "STC15xxx.h"
#include <intrins.h>
#include <stdio.h>
#define u8  unsigned char
#define u16 unsigned int
u8 Temp_Disp_Buff[17];
extern u8 Temp_Value[];
extern void LCD_Initialise();
extern void LCD_ShowString(u8 r, u8 c,u8 *str);
extern void delay_ms(u16);
extern u8 Read_Temperature();
//-----------------------------------------------------------------
// ������
//-----------------------------------------------------------------
void main() {
	float temp = 0.0;						//�����¶�
	P0M1 = 0; P0M0 = 0;
	P1M1 = 0; P1M0 = 0;
	P2M1 = 0; P2M0 = 0;						//����Ϊ׼˫���
	P3M1 = 0; P3M0 = 0;
	LCD_Initialise(); 						//Һ����ʼ��
	LCD_ShowString(0,0,"  DS18B20 Test  ");	//��ʾ����
	LCD_ShowString(1,0,"  Waiting.....  ");	//��ʾ�ȴ���Ϣ
	while(1) {								//ѭ����ȡ�¶Ȳ���ʾ

	}
}