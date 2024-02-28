//-----------------------------------------------------------------
//  名称: I2C接口时钟日历芯片DS1307应用
//-----------------------------------------------------------------
//  说明: 从DS1307中读取日历时钟数据,在1602 LCD上刷新显示.
//        注意：将Time-master及DS1307RTC两个库文件夹复制到
//        Arduino的库文件夹Libraries下.
//
//-----------------------------------------------------------------
#include <LiquidCrystal.h>						//液晶库
//创建液晶对象，8~10对应：RS,RW引脚,E,4~7对应D4~D7引脚
LiquidCrystal lcd(8, 9, 10, 4, 5, 6, 7);
#include <Wire.h>								//总线库
#include <TimeLib.h>							//时间库
#include <DS1307RTC.h>							//DS1307器件库
//0~6分别对应周日,周一至周六
char *WEEK[] = {"SUN","MON","TUS","WEN","THU","FRI","SAT"};
//LCD显示缓冲
char LCD_DSY_BUFFER1[] = {"DATE 00-00-00   "};
char LCD_DSY_BUFFER2[] = {"TIME 00:00:00   "};
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
// 日期与时间值转换为数字字符
//-----------------------------------------------------------------
void Format_DateTime(uint8_t d, uint8_t *a) {

}
/* 
//-----------------------------------------------------------------
// 关于tmElements_t类型，定义在TimeLib.h中。
//-----------------------------------------------------------------
typedef struct  {
	uint8_t Second;
	uint8_t Minute;
	uint8_t Hour;
	uint8_t Wday;   // day of week, sunday is day 1
	uint8_t Day;
	uint8_t Month;
	uint8_t Year;   // offset from 1970;
} 	tmElements_t, TimeElements, *tmElementsPtr_t;
//-----------------------------------------------------------------
//从DS1307读取日期时间的函数(BCD码)，在DS1307RTC.c中。
//-----------------------------------------------------------------
bool DS1307RTC::read(tmElements_t &tm) {
	uint8_t sec;
	Wire.beginTransmission(DS1307_CTRL_ID);			//启动I2C总线
	#if ARDUINO >= 100
	Wire.write((uint8_t)0x00);
	#else
	Wire.send(0x00);
	#endif
	if (Wire.endTransmission() != 0) {
		exists = false;
		return false;
	}
	exists = true;
	// request the 7 data fields   (secs, min, hr, dow, date, mth, yr)
	Wire.requestFrom(DS1307_CTRL_ID, tmNbrFields);
	if (Wire.available() < tmNbrFields) return false;
	#if ARDUINO >= 100
	sec = Wire.read();
	tm.Second =	bcd2dec(sec & 0x7f);
	tm.Minute =	bcd2dec(Wire.read() );
	tm.Hour =	bcd2dec(Wire.read() & 0x3f);  // mask assumes 24hr clock
	tm.Wday =	bcd2dec(Wire.read() );
	tm.Day =	bcd2dec(Wire.read() );
	tm.Month =	bcd2dec(Wire.read() );
	tm.Year =	y2kYearToTm((bcd2dec(Wire.read())));
	#else
	sec = Wire.receive();
	tm.Second =	bcd2dec(sec & 0x7f);
	tm.Minute =	bcd2dec(Wire.receive() );
	tm.Hour =	bcd2dec(Wire.receive() & 0x3f);  // mask assumes 24hr clock
	tm.Wday =	bcd2dec(Wire.receive() );
	tm.Day =	bcd2dec(Wire.receive() );
	tm.Month =	bcd2dec(Wire.receive() );
	tm.Year =	y2kYearToTm((bcd2dec(Wire.receive())));
	#endif
	if (sec & 0x80) return false; // clock is halted
	return true;
}
//-----------------------------------------------------------------
// 将BCD码转换为十进制编码
//-----------------------------------------------------------------
uint8_t DS1307RTC::bcd2dec(uint8_t num)
{
	return ((num/16 * 10) + (num % 16));
}
*/