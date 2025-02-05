//-----------------------------------------------------------------
//  名称: 数码管BCD解码驱动器CD4511与DM7447应用
//-----------------------------------------------------------------
//  说明: BCD码经CD4511或DM7447译码后输出数码管段码，实现数码管显示
//		（7447驱动共阳数码管,本例用的是共阴数码管,用4511直接驱动）
//
//-----------------------------------------------------------------
#include "STC15xxx.h"
#include <intrins.h>
#define MAIN_Fosc 12000000L
#define u8	unsigned char
#define u16	unsigned int
//待显示的数字串"95 16 37",其中0xFF不显示
code u8 BCD_CODE[] = {9,5,0xFF,1,6,0xFF,3,7,};
//-----------------------------------------------------------------
// 延时函数(参数范围：1~255)
//-----------------------------------------------------------------
void delay_ms(u8 x) {
	u16 i;
	do{
		i = MAIN_Fosc / 13000;
		while(--i);
	}while(--x);
}
//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------
void main() {
	u8 i;
	P1M1 = 0; P1M0 = 0;			//配置为准双向口
	P2M1 = 0; P2M0 = 0;
	while(1) {

	
	
	}
}