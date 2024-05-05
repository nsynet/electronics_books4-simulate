//------------------------- HX711.h -------------------------------
//  ����: HX711��������ͷ�ļ�
//-----------------------------------------------------------------
#ifndef __HX711_H__
#define __HX711_H__

#define u8  unsigned char
#define u16 unsigned int
#define u32 unsigned long
#include "STC15xxx.h"
#include <intrins.h>
//HX711�������� 
sbit HX711_DOUT = P2^0;	//HX711�����������
sbit HX711_SCK  = P2^1;	//HX711ʱ������
//��غ�������
extern void delay_ms(u8);
extern long HX711_Read();

#endif