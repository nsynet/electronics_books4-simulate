//---------------------------- main.c -----------------------------
//  名称: TFT彩屏ILI9341显示测试
//-----------------------------------------------------------------
//	说明: 切换开关可分别演示全屏颜色切换、图形绘制、单色与彩图显示中英文显示。
//
//-----------------------------------------------------------------
#include "STC15xxx.h"
#include "ILI9341.h"				//ILI9341驱动程序头文件
#include "picture1.h"				//单色位图数据
#include "picture2.h"				//彩色位图数据
#include <intrins.h>
#include <stdlib.h>
#define u8 	unsigned char
#define u16	unsigned int
sbit S1 = P3^0;						//四路切换开关定义
sbit S2 = P3^2;
sbit S3 = P3^4;
sbit S4 = P3^6;
u16 W,H;							//图像宽度与高度
void Demo_Triangles(u16 color);		//函数声明
void Demo_Lines(u16 color);
void Demo_Circles(u16 color);
void Demo_Rects(u16 color);
//-----------------------------------------------------------------
// 主函数
//-----------------------------------------------------------------
void main() {
	u8 CurrKeyStatus = 0xFF; int i;
	W = ILI9341_TFTWIDTH; H = ILI9341_TFTHEIGHT;
	P0M1 = 0x00; P0M0 = 0x00;		//配置为准双向口
	P3M1 = 0xFF; P3M0 = 0x00;		//配置为高阻输入
	delay_ms(100);
	LCD_Init();						//LCD初始化
	while(1) {
		if (S1 == 0) {				//四种颜色逐一刷屏显示（红、白、蓝、绿）

		
		}
		else if (S2 == 0) {			//四种图形逐一绘制显示

		
		}
		else if (S3 == 0) {			//位图输出显示

		
		} else if (S4 == 0) {		//中英文字符输出显示
			LCD_Clear(ILI9341_WHITE);//白底输出一串中文(直接方式或内码方式)
			//DrawChineseString(0,100,ILI9341_BLUE, ILI9341_WHITE, "上海大众汽车公司２０２５", 12);
			setCursor(0,0);
			DrawChineseString(0,10,ILI9341_BLUE, ILI9341_WHITE, 
			"ABC123\xC9\xCF\xBA\xA3\xB4\xF3\xD6\xDA\xC6\xFB\xB3\xB5\xB9\xAB\xCB\xBE\xA3\xB2\xA3\xB0\xA3\xB2\xA3\xB5", 12);
			for (i = 0; i < 0xFF; i++) {	//用字号1输出ASCII字符
				write(' '+i, ILI9341_BLUE, ILI9341_WHITE,1);
			}
			for (i = 0; i < 0xFF; i++) {	//用字号2输出ASCII字符
				write(' '+i, ILI9341_BLUE, ILI9341_WHITE,2);
			}
			delay_ms(200);
		}
	}
}
//-----------------------------------------------------------------
// 绘制三角形(模拟立体形状)
//-----------------------------------------------------------------
void Demo_Triangles(u16 color) {


}
//-----------------------------------------------------------------
// 绘制线条
//-----------------------------------------------------------------
void Demo_Lines(u16 color) {


}
//-----------------------------------------------------------------
// 绘制圆形
//-----------------------------------------------------------------
void Demo_Circles(u16 color) {


}
//-----------------------------------------------------------------
// 绘制矩形
//-----------------------------------------------------------------
void Demo_Rects(u16 color) {


}