#include <At89x52.h>
#include <intrins.h>
#include <stdarg.h>
#include <stdio.h>
#include <math.h>
#include <absacc.h>
#include <string.h>

#define ulong unsigned long
#define uint unsigned int
#define uchar unsigned char

sbit ce=P2^7;
sbit reset=P3^3;

//��8*8�ַ�����,��ʾ���������������ʾ���ַ�����
//��240*128Ϊ��:
#define LineChar 30 //һ��16���ַ�(8*8)
#define ColumnChar 16 //�ܹ�16��

#define STX 0x02
#define ETX 0x03
#define EOT 0x04
#define ENQ 0x05
#define BS 0x08
#define CR 0x0D
#define LF 0x0A
#define DLE 0x10
#define ETB 0x17
#define SPACE 0x20
#define COMMA 0x2C

#define TRUE 1
#define FALSE 0

#define HIGH 1
#define LOW 0

// T6963C �˿ڶ���
#define LCMDW XBYTE[0x8000] // ���ݿ�
#define LCMCW XBYTE[0x8100] // �����

//��ʾ�ڴ����
//0000h-67ffh �ı���
//6800h-77ffh 4K ͼ����
//7800h-7fffh 2k CGRAM��
#define DISRAM_SIZE 0X7FFF  //������ʾram�Ĵ�С
#define TXTSTART 0x0000      //�����ı�������ʼ��ַ
#define GRSTART 0x6800       //����ͼ��������ʼ��ַ
#define CGRAMSTART 0x7800  //����CGRAM����ʼ��ַ

// T6963C �����
#define LC_CUR_POS 0x21 // ���λ������
#define LC_CGR_POS 0x22 // CGRAMƫ�õ�ַ����
#define LC_ADD_POS 0x24 // ��ַָ��λ��
#define LC_TXT_STP 0x40 // �ı�����ַ
#define LC_TXT_WID 0x41 // �ı������
#define LC_GRH_STP 0x42 // ͼ������ַ
#define LC_GRH_WID 0x43 // ͼ�������
#define LC_MOD_OR 0x80 // ��ʾ��ʽ���߼�����
#define LC_MOD_XOR 0x81 // ��ʾ��ʽ���߼������
#define LC_MOD_AND 0x82 // ��ʾ��ʽ���߼����롱
#define LC_MOD_TCH 0x83 // ��ʾ��ʽ���ı�����
#define LC_DIS_SW 0x90 	// ��ʾ���أ�
                        // D0=1/0:�����˸����/����;
						// D1=1/0:�����ʾ����/���ã�
						// D2=1/0:�ı���ʾ����/���ã�
						// D3=1/0:ͼ����ʾ����/���ã�
#define LC_CUR_SHP 0xA0 // �����״ѡ��0xA0-0xA7��ʾ���ռ������
#define LC_AUT_WR 0xB0 // �Զ�д����
#define LC_AUT_RD 0xB1 // �Զ�������
#define LC_AUT_OVR 0xB2 // �Զ���/д����
#define LC_INC_WR 0xC0 // ����һ��д����ַ��1
#define LC_INC_RD 0xC1 // ����һ�ζ�����ַ��1
#define LC_DEC_WR 0xC2 // ����һ��д����ַ��1
#define LC_DEC_RD 0xC3 // ����һ�ζ�����ַ��1
#define LC_NOC_WR 0xC4 // ����һ��д����ַ����
#define LC_NOC_RD 0xC5 // ����һ�ζ�����ַ����
#define LC_SCN_RD 0xE0 // ����
#define LC_SCN_CP 0xE8 // ������
#define LC_BIT_OP 0xF0 // λ������D0-D2������D0-D7λ��D3��1��λ��0�����