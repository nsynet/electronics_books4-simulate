//-------------------------- calc.c -------------------------------
// ����: ���ӳӼ۸���������������
//-----------------------------------------------------------------
#define u8  unsigned char
#define u16 unsigned int
#include "STC15xxx.h"
#include <intrins.h>
#include <intrins.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
//����������
sbit BEEP = P3^5;
//�����жϼ�������ֵ
#define Key_Pressed	(P0 & (1<<4))	//DA(P1.4)Ϊ�ߵ�ƽʱ�м�����
#define Key_NO		(P0 & 0x0F)		//�����������������P0����λ
//�����ַ���(����ע��2,5,8�������һ���ո�)
code char KEY_CHAR_TABLE[] = "012 345 678 9.C";
//Һ����ʾ�ַ�������
extern void LCD_ShowString(u8 r, u8 c,char *str);
extern void delay_ms(u8);
//LCD��ʾ�������(�۸�/����/���)����󳤶�
//��ΪҪԤ��������־,ʵ�ʴ����ȶ�����1λ
#define PLEN	7
#define WLEN	6
#define SUMLEN  10
//LCD��ʾ�������(�۸�/����/���)
char disp_buffer_P[PLEN];
char disp_buffer_W[WLEN];
char disp_buffer_SUM[SUMLEN];
//�۸����뻺������
u8 NumberPtr = 0;
//-----------------------------------------------------------------
// ���������
//-----------------------------------------------------------------
void Sounder() { 

}
//-----------------------------------------------------------------
// �������㲢��ʾ���
//-----------------------------------------------------------------
void Compute_and_show_sum() { 

}
//-----------------------------------------------------------------
// ������̲���
//-----------------------------------------------------------------
void KeyBoard_Handle() {
	char  KeyChar;
	//�Ƿ��Ѿ������˼۸�P��С����
	static u8 havedot = 0;
	//�ڻ�û������۸��е�С����ʱ�ɼ��������ַ��ĸ���(dtnum��ʼʱĬ��Ϊ7)
	static u8 dtnum = PLEN;
	//����м��������ȡ�����ַ�(���ݽ�����DA�����Ƿ�����ߵ�ƽ���ж�)
	if (Key_Pressed) {
		Sounder();							//ÿ�ΰ���ʱ���������ʾ��
		KeyChar = KEY_CHAR_TABLE[Key_NO];	//���ݼ�ֵ��ȡ�����ַ�
		//���������������ַ���С����(����ǰδ�����С����)
		//----------------------------------------------------------
		if (isdigit(KeyChar) || (KeyChar == '.' && !havedot)) {
			//��Ŀǰ��δ����С����,�ҵ�ǰ����Ĳ���С����,����ʱ������Ϊ3ʱ����
			//(�������뷶ΧΪ0~999.99,������������3λ���ϵ�����)
			if (strlen(disp_buffer_P)==3 && 
				(KeyChar!='.'&&!havedot)) return;
			//����������ַ����뻺��
			if (NumberPtr < dtnum) {
				//�������ĵ�һ���ַ���'0'��"."��ֱ�Ӵ���Ϊ"0."
				//������ƿ������û���û�з�0�ļ۸�����λʱֱ�Ӵ�С���㿪ʼ����
				//����Ҫ����"0.86"ʱ��ֱ������".86"
				if ( NumberPtr==0 && (KeyChar=='0'||KeyChar=='.')) {
					disp_buffer_P[NumberPtr++] = '0'; KeyChar = '.';
					disp_buffer_P[NumberPtr++] = '.';
				}
				else {
					//�������������������ַ�
					disp_buffer_P[NumberPtr++] = KeyChar;
				}
				disp_buffer_P[NumberPtr] = '\0';	//���ַ���������־
				LCD_ShowString(2,3,disp_buffer_P);	//ˢ����ʾ�۸�
			}
			//����С�����Ҵ�ǰδ�����С������ʼ�޶��������С��λ
			if (KeyChar == '.' && !havedot) {
				dtnum = NumberPtr + 2;	havedot = 1;
			}
		}
		//�����ǰ������ļ۸�
		//----------------------------------------------------------
		else if (KeyChar == 'C') {
			NumberPtr = 0;				//disp_buffer_P���ֻ���ָ���0
			havedot = 0;				//С���������־��0
			dtnum = PLEN - 2;			//��λС�����������ַ�����
			disp_buffer_P[0]	= '\0'; //����۸񼰽��LCD�������
			disp_buffer_SUM[0] = '\0';
			LCD_ShowString(2,3,(char*)"      ");	//���6���ո�,����۸�
			LCD_ShowString(3,7,(char*)"         ");	//���9���ո�,������
		}
		if (Key_Pressed) Compute_and_show_sum();	//���㲢��ʾ�ܽ��
		while (Key_Pressed);						//�ȴ������ͷ�
	}
}