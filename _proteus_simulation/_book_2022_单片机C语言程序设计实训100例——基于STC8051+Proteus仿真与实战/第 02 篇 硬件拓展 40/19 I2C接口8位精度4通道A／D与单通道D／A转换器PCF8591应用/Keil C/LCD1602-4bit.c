//-----------------------------------------------------------------
//	����: LCD1602Һ����������
//-----------------------------------------------------------------
#include "LCD1602-4bit.h"
//-----------------------------------------------------------------
// ��ʱ����
//-----------------------------------------------------------------
void Delay100us()		//@12.000MHz
{
	u8 i = 2, j = 39;
	do {
		while (--j);
	} while (--i);
}
//-----------------------------------------------------------------
void Delay1ms()		//@12.000MHz
{
	u8 i = 12, j = 169;
	do {
		while (--j);
	} while (--i);
}
//-----------------------------------------------------------------
void delay_ms(u8 x) {
	while(x--) Delay1ms();
}
//-----------------------------------------------------------------
// дҺ������
//-----------------------------------------------------------------
void Write_LCD_Cmd(u8 cmd) {

}
//-----------------------------------------------------------------
// ��Һ��д����
//-----------------------------------------------------------------
void Write_LCD_Dat(u8 dat) {

} 
//-----------------------------------------------------------------
// Һ����ʼ��
//-----------------------------------------------------------------
void Initialize_LCD() {

}
//-----------------------------------------------------------------
// ��ָ��λ����ʾ�ַ���
//-----------------------------------------------------------------
void LCD_ShowString(u8 r, u8 c,char *str) {

}