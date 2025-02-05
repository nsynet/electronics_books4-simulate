//-----------------------------------------------------------------
//  名称: PC机与Arduino双向串口通信
//-----------------------------------------------------------------
//  说明: Arduino可接收PC机发送的数字字符,按下Arduino的K1按键时,
//		Arduino可向PC发送字符串.在Proteus环境下完成本实验时,需要
//		先安装Virtual Serial Port Driver和串口调试助手软件.
//		建议在VSPD中将COM3和COM4设为对联端口.Proteus中设COMPIM
//		为COM3,在串口助手中选择COM4,完成配置后即可实现Arduino程序
//		与Windows下串口助手软件之间的双向通信.
//		本例缓冲为4个数字字符,缓冲满后新接收的字符从缓冲前面存放
//		（环形缓冲）,覆盖原来放入的字符.
//		如果发送的数字串中遇到"#"号则从缓冲起始位置开始存放.
//
//-----------------------------------------------------------------
//本例按键按下后，将向上位主机发送下面含有中文的字符串：
//"这是由Arduino发送来的字符串!!!\r\n";
//为确保该字符串能正常发送，可选择方法如下：
//-----------------------------------------------------------------
//方法 1：直接提供字符串编码（本例所需编码为ANSI，可用UltraEdit提取）
//注意：当前编码较长，写在一行中可读性比较差，以下拆成以了三行，前两行
//末尾注意既无分号，也无逗号，仅最后一行末尾有分号“;”
//另注：其末尾的\r\n还可以写成\x0D\x0A,表示回车换行（return,newline)
char *str=	"\xD5\xE2\xCA\xC7\xD3\xC9\x41\x72\x64\x75\x69\x6E\x6F"
			"\xB7\xA2\xCB\xCD\xC0\xB4\xB5\xC4\xD7\xD6\xB7\xFB\xB4"
			"\xAE\x21\x21\x21\r\n";
//-----------------------------------------------------------------
//方法 2：将本例源程序文件（*.ino）另存为ANSI-GB2312编码格式，
//然后在源程序中直接使用下面的中英文字符串原文
//char *str= "这是由Arduino发送来的字符串!!!\r\n";
//经测试，该方法在本例失败，按下按键后，上位机串口助手窗口
//出现乱码。经跟踪发现，虽然本例源程序文件（*.ino）被切换成了ANSI-GB2312编码
//但源程序下面随后又引入了几个头文件，这些头文件是UTF-8编码
//可见编译器不能很好的适应因#include头文件而出现的混合编码情况
//-----------------------------------------------------------------
//方法 3：将待发送中英文字符串保存于独立文件，且编码确保为ANSI-GB2312(GBK）
//#include "LEDStr.h"				//待发送字符串（必须为ANSI格式）
//-----------------------------------------------------------------
#include <TimerOne.h>				//Timer1定时器头文件
#include <SoftwareSerial.h>			//软件模拟串口头文件
SoftwareSerial mySerial(10, 11);		//模拟串口RXD,TXD定义在10,11脚
#define K1 12						//按键引脚定义
//共阴数码管数字段码表,最后一位为"-"的段码
const uint8_t CA_SEGCODE[] =
{ 0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0xBF};
volatile uint8_t R[] = {10,10,10,10};	//4位数字接收缓冲(初始时为4个"-")
uint8_t Prekey = 0xFF;				//按键状态
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
// mySerial串口接收事件处理
//-----------------------------------------------------------------
void myserialEvent() {

}
//-----------------------------------------------------------------
// TIMER1定时中断服务(每4ms调用一次）
//-----------------------------------------------------------------
void Refresh_DSY() {

}