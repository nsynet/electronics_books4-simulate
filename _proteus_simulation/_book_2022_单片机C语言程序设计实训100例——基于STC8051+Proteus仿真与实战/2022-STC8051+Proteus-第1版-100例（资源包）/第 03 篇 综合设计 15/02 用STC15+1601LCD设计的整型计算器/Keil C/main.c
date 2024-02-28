//----------------------------- main.c --------------------------------
//  ����: ��STC15+1601LCD��Ƶ����ͼ�����
//---------------------------------------------------------------------
//  ˵��: �������������LABCENTER ELECTRONICS�ṩ����C�����������Ի�ϱ�д
//	      ��ԭʼ����ıࡣ���������˼���Ʋ���ԭʼ�������ȫ����ΪC���Գ������
//	      
//---------------------------------------------------------------------
#define u8  unsigned char
#define u16 unsigned int
#include "STC15xxx.h"
#include <intrins.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "calc.h"
static long a,b;			//��ǰ�������ǰ������������
static char CurrKeyChar;	//��ǰ�����ַ�
static char Last_OP;		//�������Ĳ�����
static char Last_Char;		//�������ǰһ���ַ�
static char result;			//��ǰ����Ľ��״̬
//��ʾ���������������뻺�������������뻺������������
static char xdata outputbuffer[MAX_DISPLAY_CHAR+1];
static char xdata NumberStr[MAX_DISPLAY_CHAR+1];
static char xdata NumberIdx;
extern void Initialize_LCD();
extern void LCD_Disp_String(char*);
extern void delay_ms(u8);
//---------------------------------------------------------------------
// ������ʾ�����Ƿ�Խ��
//---------------------------------------------------------------------
int calc_chkerror(long num) { return labs(num) <= 9999999? OK : ERROR;}
//---------------------------------------------------------------------
// ������
//---------------------------------------------------------------------
void main() { 
	P0M1 = 0x00; P0M0 = 0x00;		//P0,P1����Ϊ׼˫���
	P1M1 = 0x00; P1M0 = 0x00;
	a = 0; b = 0;					//������������ʼΪ0
	CurrKeyChar = '='; Last_OP = '0';	//��ʼ����ǰ�����ַ�������Ĳ�����
	NumberStr[0] = '\0'; NumberIdx = 0; //����������뻺����,����������
	Initialize_LCD();				//��ʼ��LCD
	LCD_Disp_String("0");			//��ʼʱ��ʾ0
	while(1) {						//ѭ��ɨ����̲��������㴦������ʾ
		//���þ������ɨ�����,�а���������ʱ���ذ����ַ�,�ް���������ʱѭ��ɨ��
		do { CurrKeyChar = GetKeyChar();} while (!CurrKeyChar);
		if ( isdigit(CurrKeyChar) ) {	//��������ּ�

		
		}
		else {//��������ְ���(����+,-,*,/,=,C)

		
		}
		//��ɵ�ǰ�������ֻ�������ַ������,Last_Char�����������������ַ�
		Last_Char = CurrKeyChar;
	}
}
//---------------------------------------------------------------------
// ��������������������㴦��
//---------------------------------------------------------------------
void Operator_Process(char OP) { 
	switch(OP) { 
		//����+,-,*,/
		case '+' : if ( CurrKeyChar == '=' || isdigit(Last_Char)){
						a += b;	result = calc_chkerror(a); 
					}	else result = SLEEP; 	break;
		case '-' : if ( CurrKeyChar == '=' || isdigit(Last_Char)){
						a -= b; result = calc_chkerror(a);
					}	else result = SLEEP; 	break;
		case '*' : if ( CurrKeyChar == '=' || isdigit(Last_Char)){
						a *= b; result =  calc_chkerror(a);
					}	else result = SLEEP; 	break;
		case '/' : if ( CurrKeyChar == '=' || isdigit(Last_Char)){
						if (b) {
							a /= b;	result = calc_chkerror(a);
						}	else result = SLEEP;
					}	else result = SLEEP; 	break;
		//ȡ��,����ر����������Ϊ'0',״̬��ΪOK,�Ա���ʾ���0
 		case 'C' :	a = b = 0; CurrKeyChar = Last_OP = '0';
					result = OK; break;
		default :	result = SLEEP;  
	}
	//�����ʾ���
	switch (result) {
		//���Ϸ��ĳ��������ת��Ϊ�ַ����������ʾ
		case OK	:	sprintf(outputbuffer,"%ld",a);
					LCD_Disp_String(outputbuffer);	break;
		//��ǰ�в���ִ��һ������,�ʲ�ˢ����ʾ
		case SLEEP :								break;
		//�����������ʾ�쳣��Exception��
		case ERROR: default: a = b = 0; CurrKeyChar = Last_OP = '0';
					LCD_Disp_String("Exception ");	break;
	}
}