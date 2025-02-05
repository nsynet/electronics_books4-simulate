#ifndef DHT_H
#define DHT_H
#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

/* DHT library written by Adafruit Industries */
// how many timing transitions we need to keep track of. 2 * number bits + extra
#define MAXTIMINGS 83
#define DHT11 11
#define DHT22 22
#define DHT21 21
#define AM2301 21

class DHT {
	private:
		uint8_t data[6];
		uint8_t _pin, _type, _count;
		unsigned long _lastreadtime;
		boolean firstreading;
	public:
		DHT(uint8_t pin, uint8_t type, uint8_t count=6);
		void begin(void);
		float readTemperature(bool S=false);
		float convertCtoF(float);
		float convertFtoC(float);
		float computeHeatIndex(float tempFahrenheit, float percentHumidity);
		float readHumidity(void);
		boolean read(void);
};
#endif