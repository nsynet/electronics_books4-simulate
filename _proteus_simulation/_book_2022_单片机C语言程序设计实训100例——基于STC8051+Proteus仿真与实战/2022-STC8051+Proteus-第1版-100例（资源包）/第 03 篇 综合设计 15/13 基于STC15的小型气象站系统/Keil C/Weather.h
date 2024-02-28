//-----------------------------------------------------------------
// 名称：风速、雨量、光照测量程序头文件
//-----------------------------------------------------------------
#ifndef ___WEATHER___
#define ___WEATHER___

#include "STC15xxx.h"
#define u8  unsigned char
#define u16 unsigned int
#define u32 unsigned long
	
u8 wdout, wsout, lsref, lsout, rgout;
float rainTotal;

u32 lastpoll, nextpoll;
u8 second; //When it hits 60, increase the current minute
u8 minute; //Keeps track of where we are in various arrays of data
u8 hour;

u8 windspeedavg[60]; //60 u8s to keep track of 1 minute average
int winddiravg[60]; //60 ints to keep track of 1 minute average
u8 windgust_10m[10]; //10 values to keep track of 10 minute max
int windgustdir_10m[10]; //10 ints to keep track of 10 minute max
float raintenminutes;
int rainhour[6]; //6  numbers to keep track of 6x10 minutes of rain
int rainday[24]; //24 floating numbers to keep track of 24 hours of rain.

float getDaylight();
float getWindSpeed();
float getWindDirection();
float getGustSpeed();
float getGustDirection();
float getRainHour();
float getRainDay();

static volatile u32 rainlastIRQ, rainticks;
static volatile u32 windlastIRQ, windticks;

float rawWindSpeed();
float rawWindDirection();
#endif