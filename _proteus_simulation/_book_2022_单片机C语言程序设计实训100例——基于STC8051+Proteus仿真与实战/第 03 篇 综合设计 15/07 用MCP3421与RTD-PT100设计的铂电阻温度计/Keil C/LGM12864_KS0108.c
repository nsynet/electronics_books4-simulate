//-----------------------------------------------------------------
//  名称: LGM12864LCD显示驱动程序 (不带字库)
//-----------------------------------------------------------------
#include "STC15xxx.h"
#include <intrins.h>
#include <stdio.h>
#include <string.h>
#include "LGM12864_KS0108.h"
extern void delay_ms(u16);
//-----------------------------------------------------------------
// 向LCD发送命令
//-----------------------------------------------------------------
void LCD_Write_Command(u8 cmd) {

} 
//-----------------------------------------------------------------
// 向LCD发送数据
//-----------------------------------------------------------------
void LCD_Write_Data(u8 dat) {

} 
//-----------------------------------------------------------------
// LCD初始化函数
//-----------------------------------------------------------------
void LCD_Initialize() {
	RST = 0; delay_ms(1);					//复位LCD
	RST = 1;								//恢复LCD正常工作
	LCD_Write_Command(0x30); delay_ms(15);	//基本指令操作
	LCD_Write_Command(0x01); delay_ms(15);	//清除显示
	LCD_Write_Command(0x06); delay_ms(15);	//光标移动方向
	LCD_Write_Command(0x0c); delay_ms(15);	//开显示,关光标,不闪烁
}
//-----------------------------------------------------------------
//
// 通用显示函数
// 
// 从第P页第L列开始显示W个字节数据,数据在r所指向的缓冲
// 每字节8位是垂直显示的,高位在下,低位在上
// 每个8*128的矩形区域为一页
// 整个LCD又由64x64的左半屏和64x64的右半屏构成
//-----------------------------------------------------------------
void Common_Show(u8 P,u8 L,u8 W,u8 *r) {
	u8 i;
	//显示在左半屏或左右半屏
	if( L < 64 ) {
		CS1 = 1; CS2 = 0;
		LCD_Write_Command( LCD_PAGE + P );
		LCD_Write_Command( LCD_COL  + L );
		//全部显示在左半屏
		if( L + W < 64 ) {
			for(i = 0;i < W;i++) LCD_Write_Data(r[i]);
		}	
		//如果越界则跨越左右半屏显示
		else {
			//左半屏显示
			for(i = 0;i< 64 - L;i++) LCD_Write_Data(r[i]);
			//右半屏显示
			CS1 = 0; CS2 = 1;
			LCD_Write_Command( LCD_PAGE + P );
			LCD_Write_Command( LCD_COL );
			for(i = 64 - L;i < W;i++) LCD_Write_Data(r[i]);
		}
	}
	//全部显示在右半屏
	else {
		CS1 = 0; CS2 = 1;
		LCD_Write_Command( LCD_PAGE + P );
		LCD_Write_Command( LCD_COL + L - 64 );
		for( i = 0;i < W; i++) LCD_Write_Data(r[i]);
	}
} 
//-----------------------------------------------------------------
// 显示一个8×16点阵字符
//-----------------------------------------------------------------
void Display_A_Char_8x16(u8 P,u8 L,u8 *M) {
	Common_Show( P,	 L, 8, M );			//显示上半部分8*8
	Common_Show( P + 1, L, 8, M + 8 );	//显示下半部分8*8
}
//-----------------------------------------------------------------
// 显示一个16×16点阵汉字
//-----------------------------------------------------------------
void Display_A_WORD(u8 P,u8 L,u8 *M){
	Common_Show( P,	L, 16, M );			//显示汉字上半部分16*8
	Common_Show( P + 1,L, 16, M + 16);	//显示汉字下半部分16*8
}
//-----------------------------------------------------------------
// 显示一串16×16点阵汉字
//-----------------------------------------------------------------
void Display_A_WORD_String(u8 P,u8 L,u8 C,u8 *M) {
	u8 i;
	for (i = 0; i < C; i++) Display_A_WORD(P, L + i * 16, M + i * 32);
}