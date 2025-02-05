//----------------------- LCD1602-4bit.c --------------------------
//  名称: LCD1602液晶驱动程序（4位模式）
//-----------------------------------------------------------------
#include "LCD1602-4bit.h"
#define MAIN_Fosc 12000000L			//时钟频率定义
//-----------------------------------------------------------------
// 延时函数(参数取值限于1~255)
//-----------------------------------------------------------------
void delay_ms(u8 ms) {
	u16 i;
	do{
		i = MAIN_Fosc / 13000;
		while(--i);
	}while(--ms);
}
//-----------------------------------------------------------------
// 写液晶命令
//-----------------------------------------------------------------
void Write_LCD_Cmd(u8 cmd) {


}
//-----------------------------------------------------------------
// 向液晶写数据
//-----------------------------------------------------------------
void Write_LCD_Dat(u8 dat) {


} 
//-----------------------------------------------------------------
// 液晶初始化
//-----------------------------------------------------------------
void Initialize_LCD() {


}
//-----------------------------------------------------------------
// 在指定位置显示字符串
//-----------------------------------------------------------------
void LCD_ShowString(u8 r, u8 c,char *str) {


}
