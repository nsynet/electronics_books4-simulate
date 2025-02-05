﻿//-----------------------------------------------------------------
//  名称:UG-2864(SSD1306)OLED显示测试
//-----------------------------------------------------------------
//	说明: 本例程序基于U8g2lib库驱动SSD1306液晶图文演示
//        程序运行时通过切换开关，可分别演示：位图、中英文显示1（内置字体）、
//        中英文显示2（自定义字体）、统计图显示（模拟）.
//        注意1：如果要在源程序中直接使用中文字符串，则必须将源程序文件由
//        “Chinese Simplified-GB2312”编码格式转换为“Unicode(UTF-8)”
//        编码格式，然后再重新编译. 如果源程序中直接提供了中文字符串的
//        “Unicode或UTF-8”编码，则可以直接编译。
//        注意2：编译本例时还要将U8g2库文件夹复制到Arduino库文件夹libraries下.
//
//-----------------------------------------------------------------
#include <Arduino.h>
#include <U8g2lib.h>							//U8g2库
#include "MyU8g2fonts.c"						//自定义字模文件
#include "picture.h"							//位图数据文件
//按键定义
#define S1	0	//位图显示
#define S2  1	//中英文显示1（内置字体）
#define S3	2	//中英文显示2（自定义字体）
#define S4	3	//统计图显示（模拟）
#define S1_ON()  (digitalRead(S1) == 0)
#define S2_ON()  (digitalRead(S2) == 0)
#define S3_ON()  (digitalRead(S3) == 0)
#define S4_ON()  (digitalRead(S4) == 0)
//-----------------------------------------------------------------
//页缓冲模式1定义（配置为SPI接口，用firstPage与nextPage配合显示）
U8G2_SSD1306_128X64_NONAME_1_4W_SW_SPI u8g2(U8G2_R0,
/* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
//-----------------------------------------------------------------
// 初始配置
//-----------------------------------------------------------------
void setup() {

}
//-----------------------------------------------------------------
// 主循环
//-----------------------------------------------------------------
void loop() {


}
//-----------------------------------------------------------------
// 绘制统计图（仅为静态模拟显示）
//-----------------------------------------------------------------
void Draw_statisticsGraph() {

}