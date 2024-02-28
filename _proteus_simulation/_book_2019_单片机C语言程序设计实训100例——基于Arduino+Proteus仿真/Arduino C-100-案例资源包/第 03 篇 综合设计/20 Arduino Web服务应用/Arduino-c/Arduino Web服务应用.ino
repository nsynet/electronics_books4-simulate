//-----------------------------------------------------------------
//  名称: Arduino Web服务应用
//-----------------------------------------------------------------
//  说明: 本例基于Arduino UIP库，建立Arduino Web服务器,在本例运行时，
//        根据提示的IP地址xxx.xxx.xxx.xxx，在PC机浏览器中输入：
//        http://xxx.xxx.xxx.xxx即可远程获取Arduino返回的各路数据.
//        并可对Arduino板上的LED与LCD进行开关与显示控制.
//	      编译本例需要UIP库支持，下载地址为：
//         https://github.com/ntruchsess/arduino_uip
//       另注：本文件要保存为utf-8编码格式再编译，否则将导致网页乱码
//		 说明：调试本例需在本机适配器"配置"中的高级选项内将所有
//        "校验"及"减负"设置关闭。
//
//-----------------------------------------------------------------
//注：ENSerial与ENLCD分别为串口与LCD使能的条件编译控制符
//由于Arduino UNO内存限制，同时许可将使资源占用达93%,运行过程中随时
//可能溢出而导致系统失败。因此对于以下两个控制符，在调试时应仅使能串口
//在调试完成后，则应禁止串口，仅使能LCD.
//#define ENSerial				//条件编译控制：使能串口输出
#define ENLCD					//条件编译控制：使能LCD显示
#ifdef ENLCD						//条件编译：使能LCD
#include <LiquidCrystal.h>
//液晶屏RS、RW、E及D4～D7分别占用3,18,19及4～7
LiquidCrystal lcd(3, 18, 19, 4, 5, 6, 7);
#endif
#include <SPI.h>
#include <UIPEthernet.h>
const uint8_t mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };//MAC地址
IPAddress ip(192,168,0,200);		//本机IP地址（测试1，注意与PC处于同一网段）
//IPAddress ip(125,221,48,3);	//本机IP地址（测试2，注意与PC处于同一网段）
EthernetServer server(80);		//初始化Arduino Ethernet服务器（默认端口为80）
//-----------------------------------------------------------------
//以下<HTML>与</HTML>间是标准WEB页标记语言,用于向客户端返回（utf-8编码）
const char *html_title_head_form = 
//注：以下4行除最后一行以外，各行末尾均无分号
"<html xmlns=\"http://www.w3.org/1999/xhtml\"><head>"
"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />"
"<title>Arduino WEB服务测试</title>"
"</head><body><form>" ;
const char *radio= "<input type=\"radio\" name=\"SWITCH\" value=";
//两个单选框后半部分标记在主循环中根据变量判断补全
//"\"1\" XXXXXXX >ON";	//XXXXXXX->checked
//"\"0\" XXXXXXX >OFF";	//XXXXXXX->checked
const char *textbox_and_button_and_etc = 
//注：以下3行除最后一行以外，各行末尾均无分号
"LCD TEXT:<input type=\"text\" name=\"TEXT\" id=\"LCD\" maxlength=\"16\">"
"<br /><input type=\"submit\" value=\"Submit\">"
"</form></body></html>";
//-----------------------------------------------------------------
#define LEDx 8							//指示灯定义
uint8_t LED_SW = 0;						//LED开关标识
const char *GET =  "GET /?";				//GET标识：6个字符(/?前有一空格)
const char *HTTP = " HTTP/1.1";			//HTTP标识：9个字符(H前有一空格)
boolean GET_OK = false, HTTP_OK = false;	//参数接收成功标识
//-----------------------------------------------------------------
// 初始配置（注：因Arduino RAM有限，启用LCD时应禁用所有Serial）
//-----------------------------------------------------------------
void setup() {

}
//-----------------------------------------------------------------
// 主循环（注：因Arduino RAM有限，启用LCD时应禁用所有Serial）
//-----------------------------------------------------------------
void loop() {	

}