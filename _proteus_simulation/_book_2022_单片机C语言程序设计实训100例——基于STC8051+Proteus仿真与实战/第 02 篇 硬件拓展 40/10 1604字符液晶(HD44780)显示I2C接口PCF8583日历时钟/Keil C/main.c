//---------------------------- main.c -----------------------------
//  ����: PCF8583ʵʱʱ����ʾ����
//-----------------------------------------------------------------
//  ˵��: ��PCF8583�ж�ȡ����ʱ�����ݲ�ˢ����ʾ��LCD.
//
//-----------------------------------------------------------------
#define u8 	unsigned char
#define u16	unsigned int
#include "STC15xxx.h" 
#include "PCF8583.h"
#include <intrins.h>
#include <stdio.h>
#include <string.h> 
extern void LCD_ShowString(u8 r, u8 c,u8 *str);
extern void Initialize_LCD();
extern void delay_ms(u8 ms);
extern u8 DateTime[7];
extern char WEEK[][4];
char buf1[12] = "DATE: 00/00";
char buf2[16] = "TIME: 00:00:00";
char disp_buff[10];
//-----------------------------------------------------------------
// ������ʱ��ֵת��Ϊ�����ַ�
//-----------------------------------------------------------------
void Format_DateTime(u8 d, u8 *a) { 


}
//-----------------------------------------------------------------
// ������
//-----------------------------------------------------------------
void main() {  
	P0M1 = 0; P0M0 = 0;			//����Ϊ׼˫���
	P2M1 = 0; P2M0 = 0;
	Initialize_LCD();
	LCD_ShowString(0,0,(char *)"*PCF8583 Clock**");
	while (1) {

	
	}
}