//-------------------------- main.c -------------------------------
//  ����: ����HX711����ش������ĵ��ӳӷ������
//-----------------------------------------------------------------
//  ˵��: ��������ʱ,ͨ�����̿����뵥��,����LoadCell�����ش�������
//        ���¼�ͷ��ģ��Ӽ�����,LCD����ˢ����ʾ��ǰ����������,
//        ������ĵ����������ĳ˻�������,��ˢ����ʾLCD����.
//
//-----------------------------------------------------------------
#define u8  unsigned char
#define u16 unsigned int
#define u32 unsigned long
#include "STC15xxx.h"
#include "HX711.h"
#include <stdio.h>
#define MAIN_Fosc 12000000L				//ʱ��Ƶ�ʶ���
//У׼������0x3FBCB5ΪLoadCell��Ϊ100%ʱProteus��ʾ�������Ϣ,
//���磺[HX711 SAMPLING] Converted A input = 0x3FBCB5, 
//      Voltage = 9.959 mV, Rate = 0.1000s [HXADC1_U1]
#define GapValue (((long)(0x3FBCB5))/200.0) //����20885.385
extern void delay_ms(u8);
extern void KeyBoard_Handle();			//���̴�������������ʾ����
extern void Compute_and_show_sum();	//���㲢��ʾ���
//Һ����غ���
extern void Initialize_LCD();
extern void LCD_ShowString(u8 r, u8 c, u8 *str);
extern char disp_buffer_W[];			//Һ����ʾ����(������calc.c)
//ë�ء����ء�ǰ�ν��ֵ
long Tare = 0, NetWeight = 0, PreResult = 0;
bit Flag_Error = 0;						//�����ʶ����
//-----------------------------------------------------------------
// ��ȡ����ֵ
//-----------------------------------------------------------------
void Get_Weight() {


}
//-----------------------------------------------------------------
// ������
//-----------------------------------------------------------------
void main() {
	P0M1 = 0xFF; P0M0 = 0x00;		//P0����Ϊ����,����Ϊ׼˫���
	P1M1 = 0x00; P1M0 = 0x00;
	P2M1 = 0x00; P3M0 = 0x00;
	P3M1 = 0x00; P3M0 = 0x00; P3 = 0x00;
	Initialize_LCD();				//��ʼ��LCD
	//��ʾ��ʼ��Ϣ
	LCD_ShowString(0,0,(char*)"  HX711 Scale Test  ");
	LCD_ShowString(1,0,(char*)"--------------------");
	LCD_ShowString(2,0,(char*)"P:        W:");	//��2����ʾ����������
	LCD_ShowString(3,0,(char*)"SUM($):");		//��3����ʾSUM��־(���)
//	Tare = HX711_Read();						//��ȡδ��ʼ����ǰ��ëƤ����
	while(1) {

	
	}
}