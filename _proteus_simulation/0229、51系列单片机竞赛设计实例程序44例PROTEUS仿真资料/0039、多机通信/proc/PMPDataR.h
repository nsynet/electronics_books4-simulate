
/*****************************************/

#ifndef	_PMPDATAR_H 		// ��ֹPMPDataT.h���ظ�����

#define	_PMPDATAR_H

#include <reg51.h>
#include <string.h>

#define uchar unsigned char
#define uint unsigned int

/* �����źź궨�� */
#define SUCC 0x2A		// ���ճɹ�
#define ERR 0xF0		// ���մ���

#define MAXLEN 64    	// ��������󳤶�

uchar buf;
uchar addr;

sbit P23 = P2^3;		// �����ſ��Ʒ����

#endif