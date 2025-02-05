//-----------------------------------------------------------------
//  名称: 红外遥控器接收程序
//-----------------------------------------------------------------
//  说明: 程序运行时,根据NEC红外协议接收数据并解码,然后将32位编码
//		以16进制形式显示LCD上.编译时需将IR库复制到Arduino的库文件夹下.
//
//-----------------------------------------------------------------
#include <LiquidCrystal.h>				//字符液晶库
#include <IRremote.h>					//红外遥控库
LiquidCrystal lcd(8, 9, 10, 4, 5, 6, 7);	//创建液晶实例
int RECV_PIN = 11;						//红外接收引脚
IRrecv irrecv(RECV_PIN);					//红外接收对象（实例）
decode_results results;					//解码结果
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