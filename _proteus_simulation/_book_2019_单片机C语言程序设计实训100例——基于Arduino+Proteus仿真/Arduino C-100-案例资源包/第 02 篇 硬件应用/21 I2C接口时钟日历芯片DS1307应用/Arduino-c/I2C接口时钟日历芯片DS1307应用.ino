//-----------------------------------------------------------------
//  ����: I2C�ӿ�ʱ������оƬDS1307Ӧ��
//-----------------------------------------------------------------
//  ˵��: ��DS1307�ж�ȡ����ʱ������,��1602 LCD��ˢ����ʾ.
//        ע�⣺��Time-master��DS1307RTC�������ļ��и��Ƶ�
//        Arduino�Ŀ��ļ���Libraries��.
//
//-----------------------------------------------------------------
#include <LiquidCrystal.h>						//Һ����
//����Һ������8~10��Ӧ��RS,RW����,E,4~7��ӦD4~D7����
LiquidCrystal lcd(8, 9, 10, 4, 5, 6, 7);
#include <Wire.h>								//���߿�
#include <TimeLib.h>							//ʱ���
#include <DS1307RTC.h>							//DS1307������
//0~6�ֱ��Ӧ����,��һ������
char *WEEK[] = {"SUN","MON","TUS","WEN","THU","FRI","SAT"};
//LCD��ʾ����
char LCD_DSY_BUFFER1[] = {"DATE 00-00-00   "};
char LCD_DSY_BUFFER2[] = {"TIME 00:00:00   "};
//-----------------------------------------------------------------
// ��ʼ����
//-----------------------------------------------------------------
void setup() {

}
//-----------------------------------------------------------------
// ��ѭ��
//-----------------------------------------------------------------
void loop() {


}
//-----------------------------------------------------------------
// ������ʱ��ֵת��Ϊ�����ַ�
//-----------------------------------------------------------------
void Format_DateTime(uint8_t d, uint8_t *a) {

}
/* 
//-----------------------------------------------------------------
// ����tmElements_t���ͣ�������TimeLib.h�С�
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
//��DS1307��ȡ����ʱ��ĺ���(BCD��)����DS1307RTC.c�С�
//-----------------------------------------------------------------
bool DS1307RTC::read(tmElements_t &tm) {
	uint8_t sec;
	Wire.beginTransmission(DS1307_CTRL_ID);			//����I2C����
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
// ��BCD��ת��Ϊʮ���Ʊ���
//-----------------------------------------------------------------
uint8_t DS1307RTC::bcd2dec(uint8_t num)
{
	return ((num/16 * 10) + (num % 16));
}
*/