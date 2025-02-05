//-------------------------- main.c -------------------------------
//  名称:射击训练游戏
//-----------------------------------------------------------------
//  说明:程序启动时液晶屏显示游戏封面,然后显示游戏区,默认弹药为20发,
//		K1,K2键用于向上或向下移动枪支,跟踪目标,K3用于发射并模拟枪声,
//		在每次发射时,如果击中则加1分,在击中后如果目标物体尚未移动时,
//		程序不重复加分.弹药用完后可按下K4重新开始.
//-----------------------------------------------------------------
#define u8  unsigned char
#define u16 unsigned int
#define MAIN_Fosc 12000000L	//定义主时钟
#include "STC15xxx.h"
#include "T6963C.h"
#include <intrins.h>
#include <stdlib.h>
extern void Cls();
void Show_Score_and_Bullet();
sbit K1 = P0^0;		//上移
sbit K2 = P0^1;		//下移
sbit K3 = P0^2;		//发射
sbit K4 = P0^3;		//重新开始
sbit BEEP = P1^0;	//蜂鸣器
code u8 const Game_Surface[] = { 160,110, //游戏封面:160x110
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xFC,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x0E,0x1F,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x7F,0xDF,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0xFF,0xFC,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0xFF,0xFC,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x1F,0xFF,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x03,0xFF,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x7F,0xFF,0x80,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x78,0xFF,0xFF,0xE0,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x7F,0xFF,0xFF,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x7F,0xFF,0x7F,0xFF,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0xFE,0x7F,0xFF,0xF0,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0xFF,0xFC,0xFF,
0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x0F,0xFF,0xFC,0x3F,0xFF,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x01,0xFF,0xFC,0x07,0xFF,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0xFF,0x80,0xFF,0xFF,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xFF,0xF0,
0x1F,0xFF,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xFF,0xFE,0x03,0xFF,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0xFF,0xC0,0x7F,0xFF,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xFF,0xF8,0x0F,0xFF,0xE0,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,
0xFF,0x01,0xFF,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x1F,0xFF,0xE0,0x3F,0xFF,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xFF,0xFC,0x0F,0xFF,0xF0,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0xFF,0x01,0xFF,
0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x0F,0xFF,0xE0,0x3F,0xFF,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x01,0xFF,0xFC,0x07,0xFF,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0xFF,0x80,0xFF,0xFE,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xFF,0xF0,
0x1F,0xFF,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x01,0xFF,0xFE,0x03,0xFF,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0xFF,0xC0,0x7F,0xFF,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xFF,0xF8,0x0F,0xFF,0xC0,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,
0xFE,0x03,0xFF,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x1F,0xFF,0xC0,0x7F,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xFF,0xF0,0x0F,0xFF,0xE0,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0xFE,0x01,0xFF,
0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x0F,0xFF,0xC0,0x7F,0xFF,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x03,0xFF,0xF8,0x0F,0xFF,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0xFF,0x01,0xFF,0xFE,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xFF,0xE0,
0x3F,0xFF,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x03,0xFF,0xFC,0x07,0xFF,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0xFF,0x83,0xFF,0xFF,0xFC,0x00,0x00,0x00,0x00,
0x00,0x00,0x7F,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xFF,0xE7,0xFF,0xFF,0xFF,
0x07,0x80,0x00,0x00,0x00,0x03,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xFF,
0xFF,0xFF,0xFF,0xFF,0xCF,0xC0,0x00,0x00,0x00,0x07,0xFF,0xFF,0x80,0x00,0x00,0x00,
0x00,0x00,0x00,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xC0,0x00,0x00,0x00,0x1F,0xFF,0xFF,
0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0x00,0x00,
0x00,0x3F,0xFF,0xFF,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFE,0x03,0xFF,
0xFF,0xE0,0x00,0x00,0x00,0x7F,0xC0,0x07,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x3F,0xFF,0xC0,0x7F,0xFF,0xE0,0x00,0x00,0x00,0xFF,0x00,0x03,0xFC,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x0F,0xFF,0xF8,0x0F,0xFF,0xF0,0x00,0x00,0x01,0xFC,0x00,0x00,
0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0xFF,0xFF,0x01,0xFF,0xFE,0x00,0x00,
0x01,0xF8,0x00,0x00,0x7E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x9F,0xFF,0xC0,
0x3F,0xFF,0x80,0x00,0x03,0xF0,0x00,0x00,0x3F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x1F,0x03,0xFF,0xF8,0x0F,0xFF,0xF0,0x00,0x07,0xE0,0x00,0x00,0x1F,0x80,0x00,0x00,
0x00,0x00,0x00,0x00,0x3F,0x00,0x7F,0xFF,0x07,0xFF,0xFE,0x00,0x07,0xE0,0x00,0x00,
0x1F,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x3E,0x00,0x0F,0xFF,0xE7,0xFF,0xFE,0x00,
0x07,0xC0,0x00,0x00,0x0F,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x3E,0x00,0x01,0xFF,
0xFF,0xFF,0xFE,0x00,0x0F,0xC0,0x00,0x00,0x0F,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,
0x3E,0x00,0x00,0x7F,0xFF,0xFF,0xFE,0x00,0x0F,0x80,0x00,0x00,0x07,0xC0,0x00,0x00,
0x00,0x00,0x00,0x00,0x3E,0x00,0x00,0x0F,0xFF,0xFF,0x9E,0x00,0x0F,0x80,0x00,0x00,
0x07,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x3E,0x00,0x00,0x01,0xFF,0xFF,0x82,0x00,
0x0F,0x80,0x00,0x00,0x07,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x1E,0x00,0x00,0x00,
0x3F,0xFF,0xC0,0x00,0x1F,0x80,0x00,0x00,0x07,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,
0x1F,0x00,0x00,0x00,0x0F,0xFF,0xF0,0x00,0x0F,0x00,0x00,0x00,0x07,0xC0,0x00,0x00,
0x00,0x00,0x00,0x00,0x1F,0x80,0x00,0x00,0x1F,0xFF,0xFE,0x00,0x0F,0x80,0x00,0x00,
0x07,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0xC0,0x00,0x00,0x3F,0xFF,0xFE,0x00,
0x0F,0x80,0x00,0x00,0x07,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xE0,0x00,0x00,
0x7F,0xFB,0xFE,0x00,0x0F,0x80,0x00,0x00,0x07,0xC0,0x03,0xFF,0xC0,0x00,0x00,0x00,
0x07,0xF8,0x00,0x01,0xFE,0xFF,0xFE,0x00,0x07,0x80,0x00,0x00,0x07,0x80,0x1F,0xFF,
0xF8,0x00,0x00,0x00,0x03,0xFE,0x00,0x07,0xFC,0xFF,0xFE,0x00,0x07,0xC0,0x00,0x00,
0x0F,0x80,0x3F,0xFF,0xFC,0x00,0x00,0x00,0x01,0xFF,0xFF,0xFF,0xF8,0xFF,0xFE,0x00,
0x07,0xE0,0x00,0x00,0x1F,0x80,0x7F,0xFF,0xFE,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,
0xF0,0xFF,0xFE,0x00,0x07,0xE0,0x00,0x00,0x1F,0x80,0xFF,0xFF,0xFF,0x00,0x00,0x00,
0x00,0x3F,0xFF,0xFF,0xC0,0xFF,0xFE,0x00,0x03,0xF0,0x00,0x00,0x3F,0x01,0xFE,0x00,
0x7F,0x00,0x00,0x00,0x00,0x0F,0xFF,0xFF,0x00,0xFF,0xFF,0x00,0x01,0xF8,0x00,0x00,
0x7E,0x01,0xF8,0x00,0x1F,0x00,0x00,0x00,0x00,0x03,0xFF,0xF8,0x00,0xFF,0xFF,0x00,
0x01,0xFC,0x00,0x00,0xFE,0x01,0xF0,0x00,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x7F,0xFF,0x80,0x00,0xFF,0x00,0x03,0xFC,0x01,0xF0,0x00,0x0F,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x7F,0xFF,0xC0,0x00,0x7F,0xC0,0x07,0xF8,0x01,0xF8,0x00,
0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0xFF,0xC0,0x00,0x3F,0xFF,0xFF,
0xF0,0x01,0xFE,0x00,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0xFF,0xE0,
0x00,0x1F,0xFF,0xFF,0xE0,0x00,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x7F,0xFF,0xE0,0x00,0x07,0xFF,0xFF,0x80,0x00,0x7F,0xFF,0xFE,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x7F,0xFF,0xF0,0x00,0x03,0xFF,0xFF,0x00,0x00,0x3F,0xFF,
0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0xFF,0xF8,0x00,0x00,0x7F,0xF0,
0x00,0x00,0x1F,0xFF,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0xFF,0xF8,
0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xFF,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x7F,0xFF,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x3F,0xFF,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0xFF,0xFC,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xFF,0xFC,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x01,0xFF,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0xFC,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0xF8,
0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x03,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x30,0x00,0x30,0x00,0x30,0xC1,0x80,0x20,0x30,
0x00,0x21,0x80,0x00,0x0C,0xC0,0x00,0x00,0x00,0x00,0x40,0x30,0x00,0x30,0x00,0x38,
0xC9,0x80,0x33,0xFF,0x06,0x31,0x80,0x00,0x0D,0xC0,0x00,0x00,0x00,0x01,0xFC,0x30,
0x07,0xFF,0x00,0x06,0xC9,0x80,0x63,0xFE,0x03,0x89,0xF8,0x0F,0xCE,0x00,0x00,0x00,
0x00,0x01,0xFB,0xF8,0x07,0xB0,0x00,0x00,0xC9,0x80,0x88,0x40,0x00,0x7E,0x80,0x18,
0xDF,0xE0,0x00,0x00,0x00,0x01,0x8F,0x3E,0x00,0x30,0x00,0xF8,0xC9,0x81,0xFB,0xF0,
0x08,0x35,0xF8,0x0C,0xBE,0x00,0x00,0x00,0x00,0x01,0xF9,0x30,0x3F,0xFF,0xF8,0xC8,
0xC9,0x81,0x25,0xB0,0x0F,0x3C,0x70,0x0F,0xAC,0xC0,0x00,0x00,0x00,0x07,0xF9,0xB0,
0x3C,0x33,0xF8,0x08,0xC9,0x80,0xCB,0xFE,0x00,0x24,0x60,0x03,0x8D,0x80,0x00,0x00,
0x00,0x07,0xB8,0xB0,0x02,0x31,0x30,0x18,0xC9,0x81,0xF3,0x30,0x00,0x6F,0xFE,0x03,
0x87,0x80,0x00,0x00,0x00,0x00,0xE8,0x30,0x02,0x30,0x80,0x1E,0xC9,0x80,0x01,0xB4,
0x07,0x48,0x20,0x0E,0x47,0x00,0x00,0x00,0x00,0x03,0x88,0x30,0x06,0x30,0x80,0x1D,
0xC9,0x80,0xFB,0xB3,0x0E,0xC8,0x20,0x3C,0x1F,0x80,0x00,0x00,0x00,0x0F,0x58,0x70,
0x07,0xFF,0x80,0x3B,0x89,0x83,0xC6,0x31,0xC1,0x98,0x60,0x10,0xFB,0xF8,0x00,0x00,
0x00,0x00,0x79,0xE0,0x07,0xFF,0xC0,0x37,0x09,0x82,0x19,0xF1,0x82,0x77,0xE0,0x00,
0x00,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0xE0,
0x00,0x00,0xC0,0x00,0x00,0x20,0x00,0x00	
};
u8 code Gun_Image[] = { 24,12,  //枪支图像,数据前2字节表示: W/H:24*12
 0x03,0x00,0x00,0x07,0x80,0x00,0x07,0x80,0x00,0x7F,0xFF,0xFE,
 0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x7F,0xFF,0xFC,0x00,0x01,0xFC,
 0x00,0x01,0xFC,0x00,0x00,0x7F,0x00,0x00,0x7F,0x00,0x00,0x1F
};
volatile u8 Score = 0, Bullet_Count = 20;	//得分,剩余弹药数 
volatile u8 Target_x = 0, Target_y = 0;	//目标物体位置
volatile u8 Pre_Target_y = 0;				//目标物体上次所在纵坐标位置
volatile u8 gun_y = 20;						//枪支纵坐标,横坐标固定为16*8
volatile u8 flag = 1;						//T0中断执行分支标识变量
//-----------------------------------------------------------------
// 定时器0初始配置(分别用于控制目标移动及枪声模拟输出)
//-----------------------------------------------------------------
void Timer0Init() {


}
//-----------------------------------------------------------------
// 键盘中断函数(INT2)
//-----------------------------------------------------------------
void EX_INT2() interrupt 10 {
	delay_ms(10);
	if (K1 == 0)	{		//枪支位置上移(擦除原位置枪枝时输出3个空格)
		if (gun_y != 0) Display_Str_at_xy(16*8,gun_y,"   ",0);
		gun_y -= 8;
		if (gun_y < 20 ) gun_y = 20; Draw_Image(Gun_Image,gun_y,16);
	}
	else if (K2 == 0)	{	//枪支位置下移(擦除原位置枪枝时输出3个空格)
		if (gun_y != 0) Display_Str_at_xy(16*8,gun_y,"   ",0);
		gun_y += 8; 
		if (gun_y > 100 ) gun_y = 100;	Draw_Image(Gun_Image,gun_y,16);
	}
	else if (K3 == 0)	{	//发射,模拟枪声,判断成绩
		//如果有剩余弹药则将flag标识置为2，使用T0应用于枪声模拟输出
		if (Bullet_Count != 0) flag = 2; else return;
		//绘制弹道线条
		Line(10 , gun_y + 4 , 125 , gun_y + 4 , 1); delay_ms(220);
		Line(10 , gun_y + 4 , 125 , gun_y + 4 , 0);
		if (Bullet_Count != 0 ) { //弹药非0则递减
			Bullet_Count--;
			//判断成绩,其中Pre_Target_y用于保存目标物体上次所在纵坐标位置,
			//避免物体在同一位置被反复多次击中而多次得分
			if ((gun_y + 4) > Target_y  && 
					(gun_y + 4) < Target_y + 11 && 
					Pre_Target_y != Target_y ) {
					Score++;  Pre_Target_y = Target_y ; 
			}
		}
		Show_Score_and_Bullet();	//刷新显示成绩与弹药数
	}
	else if (K4 == 0)	{			//成绩与弹药数复位
		Score = 0; Bullet_Count = 20; Show_Score_and_Bullet(); 
	}
}
//-----------------------------------------------------------------
// 定时器0中断服务程序
// 分别用于控制:（flag=>1）目标物体随机移动 （flag=>2）枪声模拟输出
//-----------------------------------------------------------------
void Timer0_ISR() interrupt 1 {
	static u8  tTime = 0;			//延时累加控制变量
	static u16 tSound = 0xFFF0;		//枪声频率控制变量
	if (flag == 1) {				//控制物体随机移动
		TL0 = 0xB0;	TH0 = 0x3C;		//重装定时初值(50ms)
		if (++tTime < 30) return;	//未累积到30*50=1500ms时不向下执行
		tTime = 0;
		//清除原位置目标（输出2个空格）
		if (Target_x != 0 && Target_y != 0) 
			Display_Str_at_xy(Target_x,Target_y,"  ",0);
		//计算新的随机位置,如果纵标变化不超过4像素时重新获取随机纵标
		Target_x = rand() % 60 + 8 ;
		Target_y = rand() % 80 + 20;
		while (abs(Pre_Target_y-Target_y)<4) Target_y=rand()%80+20;
		//在新获取的随机位置绘制物体特号"■"
		Display_Str_at_xy(Target_x,Target_y,"■",0);
	}
	else if (flag == 2) {			//控制蜂鸣器模拟枪声输出
		if (--tSound >= 0xFE00) {	//每次中断时控制变量递减（截止:0xFE00）
			TL0=tSound; TH0=tSound>>8;//更新T0定时计数寄存器(TL0/TH0)
			BEEP ^= 1;				//蜂鸣器振荡输出
		}
		else {
			tSound = 0xFFF0;		//一次枪声模块输出结束后频率控制变量还原
			BEEP = 0;				//蜂鸣器引脚置低电平
			flag = 1;				//T0重新应用于控制目标物体随机移动
		}
	}
}
//-----------------------------------------------------------------
// 显示成绩与剩余弹药
//-----------------------------------------------------------------
void Show_Score_and_Bullet() {
	char disp_buff[4] = {' ',0,0,0};
	disp_buff[1] = Score / 10 + '0';			//成绩数位分解
	disp_buff[2] = Score % 10 + '0';
	Display_Str_at_xy(37,117,disp_buff,1);		//显示当前成绩
	disp_buff[1] = Bullet_Count / 10 + '0';	//剩余弹药数位分解
	disp_buff[2] = Bullet_Count % 10 + '0';
	Display_Str_at_xy(134,117,disp_buff,1);	//显示剩余弹药
}
//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------
void main() {
	u8 i;
	P0M1 = 0x00; P0M0 = 0x00;			//P0~P3为准双向口
	P1M1 = 0x00; P0M0 = 0x00;
	P2M1 = 0x00; P2M0 = 0x00;
	P3M1 = 0x00; P3M0 = 0x00;

	
	
	
	
	
	
	
	
}