//-----------------------------------------------------------------
// ���ƣ����١����������ղ�������
//-----------------------------------------------------------------
#include "Weather.h"
#include <intrins.h>
#include <stdio.h>
volatile u32 rainlastIRQ;
volatile u32 rainticks;
extern volatile u32 Millis;
extern void delay_ms(u8);
#define ADC_POWER 	0x80 	//ADC��Դ����λ
#define ADC_FLAG 		0x10 	//ADC��ɱ�־
#define ADC_START 	0x08 	//ADC��ʼ����λ
#define ADC_SPEEDLL	0x00 	//540��ʱ��
#define ADC_SPEEDL 	0x20 	//360��ʱ��
#define ADC_SPEEDH 	0x40 	//180��ʱ��
#define ADC_SPEEDHH	0x60 	//90��ʱ��
#define lsout 0						//����ģ������ͨ��
#define lsref 1						//����3.3V�ο���ѹ����ͨ��
#define wdout 2						//����ģ���ź�����ͨ��
//-----------------------------------------------------------------
// ��ʼ��ADC
//-----------------------------------------------------------------
void InitADC() {


}
//-----------------------------------------------------------------
// ��ȡADC������ֽ⵽�������ʾ����
//-----------------------------------------------------------------
float GetADCResult(u8 ch) {


}
//-----------------------------------------------------------------
// ��ѯ���
//-----------------------------------------------------------------
void poll() {
	u8 minute_10;
	u32 now = Millis;		//��ȡ��ǰ������
	if (now > nextpoll) { 
		EA = 0;
		windspeedavg[second] = rawWindSpeed();
		winddiravg[second] = rawWindDirection();
		windticks = 0;
		raintenminutes += rainticks * 0.2794;
		rainticks = 0;
		EA = 1;
		//Capture the any higher wind gust for this minute.
		minute_10 = minute % 10;
		if (windspeedavg[second] > windgust_10m[minute_10])	{
			windgust_10m[minute_10] = windspeedavg[second];
			windgustdir_10m[minute_10] = winddiravg[second];
		}
		//Clock the time counters, and reset
		lastpoll = now, nextpoll += 1000;
		if (++second == 60) { 
			//Update the rainfall numbers for the current hour and day:
			if (minute % 10 == 0)	{
				rainhour[minute/10] = raintenminutes*100;
				raintenminutes = 0;
			}
			rainday[hour] = getRainHour()*10; 
			//����60����ʱСʱ����
			if (++minute == 60) {
				//����24Сʱ��hour��0
				if (++hour == 24)	hour = 0;
				minute = 0;//���ӹ�0
			}
			second = 0;
			//Reset the peak wind gust and rainfall for the new minute
			windgust_10m[minute % 10] = 0; 
		}
	}
}
//-----------------------------------------------------------------
// ��λ���ж�ʱ��������
//-----------------------------------------------------------------
void reset_WSx() {
	int i;
	lastpoll = Millis;
	nextpoll = lastpoll+1000;
	second = minute = hour = 0;
	//��λ��������
	for (i = 0; i < 60; ++i) {
		windspeedavg[i] = 0;	winddiravg[i] = 0;
	}
	//��λ�������
	for (i = 0; i < 10; ++i) {
		windgust_10m[i] = 0; 	windgustdir_10m[i] = 0;
	}
	//��λ��������
	raintenminutes = 0; 
	for (i = 0; i < 6; ++i)		rainhour[i] = 0;
	for (i = 0; i < 24; ++i)	rainday[i] = 0;
	//��λ�ж�������������������
	EA = 0; windticks = 0; rainticks = 0; EA = 1;
}
//-----------------------------------------------------------------
// ��ȡ��������(0->1)
//-----------------------------------------------------------------
float getDaylight() {
	//ģ��ת�����ο���ѹ��3.3V��
	float operatingVoltage = GetADCResult(lsref);
	float lightSensor = GetADCResult(lsout);
	return lightSensor / operatingVoltage;
}
//-----------------------------------------------------------------
// ��ȡ��������
//-----------------------------------------------------------------
float getWindSpeed() {
	//�������1���ӵ�ƽ������
	float temp = 0; int i,j = 0;
	for (i = 0 ; i < 60 ; i++) {
		if (windspeedavg[i] != 0) {
			temp += windspeedavg[i]; j++;
		}
	}
	if (j !=0) return temp / j; else return 0;
	//ע��ԭʼ�ⷵ�ش���Ϊ��return temp / 60.0;
	//����Ϊ������ʾ��Ч���ݣ��ݸ�Ϊ����ʾ���60���ɼ��������з�0ֵ�ľ�ֵ��
}
//-----------------------------------------------------------------
// ��ȡ��������
//-----------------------------------------------------------------
float getWindDirection() {
	int i,delta; float winddir_avg;
	long sum = winddiravg[0];
	int D = winddiravg[0];
	for (i = 1 ; i < 60; i++) {
		delta = winddiravg[i] - D;
		if (delta < -180)			D += delta + 360;
		else if (delta > 180)	D += delta - 360;
		else									D += delta;
		sum += D;
	}
	winddir_avg = sum / 60.0;
	if(winddir_avg >= 360) winddir_avg -= 360;
	if(winddir_avg < 0) winddir_avg += 360;
	return winddir_avg;
}
//-----------------------------------------------------------------
// ��ȡ�������
//-----------------------------------------------------------------
float getGustSpeed() {
	float gust = 0; int i;
	for (i = 0; i < 10 ; i++)//��ȡ���10���ӵ�������ֵ
		if (windgust_10m[i] > gust) gust = windgust_10m[i];
	return gust;
}
//-----------------------------------------------------------------
// ��ȡ������
//-----------------------------------------------------------------
float getGustDirection() {
	int i;
	//��ȡ���10���ӵ�������ֵ�����������
	float gust = 0, dir = 0;
	for (i = 0; i < 10 ; i++) {
		if (windgust_10m[i] > gust) {
			gust = windgust_10m[i];
			dir = windgustdir_10m[i];
		}
	}
	return dir;
}
//-----------------------------------------------------------------
// ��ȡ���1Сʱ����
//-----------------------------------------------------------------
float getRainHour() {
	float rain = 0; int i;
	for (i = 0; i < 6; ++i) rain += rainhour[i];
	return rain/100;   
}
//-----------------------------------------------------------------
// ��ȡ���콵��
//-----------------------------------------------------------------
float getRainDay() {
	//Compute rainfall for the last hour (rolling value).
	float rain = 0; int i;
	for (i = 0; i < 24; ++i) rain += rainday[i];
	return rain/10;   
}
//-----------------------------------------------------------------
// ��ȡԭʼ��������
//-----------------------------------------------------------------
float rawWindSpeed() {
	//Return the wind speed based on the number of wind ticks since the last poll.
	//1.492 mph is equivalent to 1 click per second.
	float deltaTime = (Millis - lastpoll) / 1000.0;
	float windSpeed = 1.492 * windticks / deltaTime;
	return windSpeed;
}
//-----------------------------------------------------------------
// ��ȡԭʼ��������
//-----------------------------------------------------------------
float rawWindDirection() {
	int i; u16 adc;
	for (i = 0; i < 3; ++i) {
		adc = GetADCResult(wdout);
		// The following table is ADC readings for the wind direction sensor output, sorted from low to high.
		// Each threshold is the midpoint between adjacent headings. The output is degrees for that ADC reading.
		// Note that these are not in compass degree order! See Weather Meters datasheet for more information.
		if (adc < 380) return (113);
		if (adc < 393) return (68);
		if (adc < 414) return (90);
		if (adc < 456) return (158);
		if (adc < 508) return (135);
		if (adc < 551) return (203);
		if (adc < 615) return (180);
		if (adc < 680) return (23);
		if (adc < 746) return (45);
		if (adc < 801) return (248);
		if (adc < 833) return (225);
		if (adc < 878) return (338);
		if (adc < 913) return (0);
		if (adc < 940) return (293);
		if (adc < 967) return (315);
		if (adc < 990) return (270);
	}
	return (-1); //���ش���ֵ
}
//-----------------------------------------------------------------
// INT0�ж�(P3.2)
//-----------------------------------------------------------------
void INT0_rainIRQ() interrupt 0 {
	//Count rain gauge bucket tips as they occur
	//Activated by the magnet and reed switch in the rain gauge
	u32 now = Millis;			//��ȡ��ǰ����ֵ
	//ignore switch-bounce glitches less than 10mS after initial edge
	if (now - rainlastIRQ > 10) {
		rainlastIRQ = now; rainticks++;
	}
}
//-----------------------------------------------------------------
// INT1�ж�(P3.3)
//-----------------------------------------------------------------
void INT1_wspeedIRQ() interrupt 2 {
	u32 now = Millis;			//��ȡ��ǰ����ֵ
	//Ignore switch-bounce glitches less than 10ms (142MPH max reading) after the reed switch closes
	if (now - windlastIRQ > 10) {
		windlastIRQ = now;
		windticks++;				//There is 1.492MPH for each click per second.
	}
}