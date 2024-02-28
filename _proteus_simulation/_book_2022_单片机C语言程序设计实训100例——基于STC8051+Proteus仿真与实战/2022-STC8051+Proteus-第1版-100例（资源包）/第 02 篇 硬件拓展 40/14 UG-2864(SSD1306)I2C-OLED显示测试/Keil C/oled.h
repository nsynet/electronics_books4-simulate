//------------------------- oled.h --------------------------------
//  ����: OLED��ʾ��������4�ߣ�
//-----------------------------------------------------------------
#ifndef __OLED_H
#define __OLED_H
#include "STC15xxx.h"
#include "intrins.h"
#define u8 	unsigned char 
#define u16 unsigned int
#define u32 unsigned long
//-----------------------------------------------------------------
#define Max_Column	128		//�������
#define Max_Row		64		//�������
#define OLED_CMD 	0		//����
#define OLED_DATA	1		//����
#define OLED_MODE	0		//ģʽ
sbit SCL =	P0^0;			//ʱ����D0��SCLK��
sbit SDA =	P0^1;			//������D1��MOSI��
//-----------------------------------------------------------------
// OLED�˿ڶ���
//-----------------------------------------------------------------
void delay_ms(u16 ms);
void OLED_Init();
void OLED_Clear();
void OLED_Display_On();
void OLED_Display_Off();
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 font);
void OLED_ShowNum(u8 x,u8 y,u32 n,u8 w,u8 font);
void OLED_ShowStr(u8 x,u8 y,u8 *s,u8 font); 
void OLED_Set_Pos(u8 x, u8 y);
void OLED_ShowHZ(u8 x,u8 y,u8 no);
void OLED_DrawBMP(u8 x0, u8 y0,u8 x1, u8 y1,u8 BMP[]);
void Fill_picture(u8 fill_Data);
void Write_IIC_Com(u8 IIC_Command);
void Write_IIC_Dat(u8 IIC_Data);
#endif