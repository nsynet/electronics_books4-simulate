//-----------------------------------------------------------------
//  ����: LM044LҺ����������
//-----------------------------------------------------------------
#include "LM044L-4bit.h"
//-----------------------------------------------------------------
// ��ʱ����:1ms,xms @12.000MHz
//-----------------------------------------------------------------
void Delay1ms() {
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
	u8 i = 0;
	//Һ��4�е�DDRAM��ʼ��ַ
	code u8 DDRAM[] = {0x80,0xC0,0x94,0xD4};
	Write_LCD_Cmd(DDRAM[r] + c);				//������ʾ��ʼλ��
	//����ַ���
	for (i = 0; i < 20 && str[i]!= '\0';i++) Write_LCD_Dat(str[i]);
}