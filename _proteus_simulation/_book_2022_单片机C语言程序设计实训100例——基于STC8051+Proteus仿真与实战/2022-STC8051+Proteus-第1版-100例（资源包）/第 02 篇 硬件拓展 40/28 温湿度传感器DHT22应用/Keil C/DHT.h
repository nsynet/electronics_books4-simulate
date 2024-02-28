//-------------------------- DHT22.h ------------------------------
//  ����: DHT��ʪ�ȴ�������������
//-----------------------------------------------------------------
#ifndef DHT_H
#define DHT_H

#define NAN 1000000.0
#include "STC15xxx.h"
#include <intrins.h>
#define u8  unsigned char
#define u16 unsigned int
#define u32 unsigned long
//���ų�������
#define MAXTIMINGS	83
#define DHT11		11
#define DHT22		22
#define DHT21		21
#define AM2301		21
//�����뺯������
u8 First_Reading;
u8 DHT_data[6];
u8 _pin, _type, _count;
u32 _Last_ReadTime;
float readTemperature(bit s);
float convertCtoF(float);
float convertFtoC(float);
float computeHeatIndex(float tempFahrenheit, float percentHumidity);
float readHumidity();
bit read();
#endif