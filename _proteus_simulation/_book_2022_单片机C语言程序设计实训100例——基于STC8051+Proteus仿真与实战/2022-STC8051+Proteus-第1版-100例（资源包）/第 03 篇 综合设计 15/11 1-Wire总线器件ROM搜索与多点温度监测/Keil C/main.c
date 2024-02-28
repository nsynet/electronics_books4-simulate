//--------------------------- main.c ------------------------------
//  ����: 1-Wire��������ROM�������򼰶��DS18B20���
//-----------------------------------------------------------------
//  ˵��: �����Զ���������1-Wire��������,�����¶ȴ�����ʱ��ʾ���¶�ֵ
//        �������ʾ��ROMCODE���뼰��ǰ����������������.
//
//-----------------------------------------------------------------
#define u8  unsigned char
#define u16 unsigned int
#include "STC15xxx.h"
#include "1-Wire.h"
#include <intrins.h>
#include <stdio.h>
extern void LCD_Initialize();
extern void LCD_ShowString(u8 r, u8 c,u8 *str);
extern void Search_ALL_ROM();
//-----------------------------------------------------------------
// ������
//-----------------------------------------------------------------
void main() {
	P0M1 = 0; P0M0 = 0;			//����Ϊ׼˫���
	P1M1 = 0; P1M0 = 0;
	P2M1 = 0; P2M0 = 0;
	P3M1 = 0; P3M0 = 0;
	LCD_Initialize();			//Һ����ʼ��
	LCD_ShowString(0,0,(char*)"1-Wire Device Search");	//��ʾ��������
	while(1) Search_ALL_ROM();	//������������,����DS18B20ʱ��ȡ����ʾ�¶�
}