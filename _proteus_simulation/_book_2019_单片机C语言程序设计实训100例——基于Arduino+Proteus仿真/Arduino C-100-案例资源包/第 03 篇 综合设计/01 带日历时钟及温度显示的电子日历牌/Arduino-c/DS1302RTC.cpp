// DS1302 RTC
// ----------
// The DS1302 uses a 3-wire interface:
//    - bidirectional data.
//    - clock
//    - chip select
// It is not I2C, not OneWire, and not SPI.
// So the standard libraries can not be used.
// Even the shiftOut() function is not used, since it
// could be too fast (it might be slow enough,
// but that's not certain).
//      seconds : 00-59
//      minutes : 00-59
//      hour    : 1-12 or 0-23
//      date    : 1-31
//      month   : 1-12
//      day     : 1-7
//      year    : 00-99
//
//
// Burst mode
// ----------
// In burst mode, all the clock data is read at once.
// This is to prevent a rollover of a digit during reading.
// The read data is from an internal buffer.
//
// The burst registers are commands, rather than addresses.
// Clock Data Read in Burst Mode
//    Start by writing 0xBF (as the address),
//    after that: read clock data
// Clock Data Write in Burst Mode
//    Start by writing 0xBE (as the address),
//    after that: write clock data
// Ram Data Read in Burst Mode
//    Start by writing 0xFF (as the address),
//    after that: read ram data
// Ram Data Write in Burst Mode
//    Start by writing 0xFE (as the address),
//    after that: write ram data
//
//
// Ram
// ---
// The DS1302 has 31 of ram, which can be used to store data.
// The contents will be lost if the Arduino is off,
// and the backup battery gets empty.
// It is better to store data in the EEPROM of the Arduino.
// The burst read or burst write for ram is not implemented
// in this code.
//
//
// Trickle charge
// --------------
// The DS1302 has a build-in trickle charger.
// That can be used for example with a lithium battery
// or a supercap.
// Using the trickle charger has not been implemented
// in this code.
//

#include <Arduino.h>
#include "DS1302RTC.h"
//-----------------------------------------------------------------
// Static variables
//-----------------------------------------------------------------
bool DS1302RTC::exists = false;
byte DS1302RTC::io = 0;
byte DS1302RTC::sclk = 0;
byte DS1302RTC::rst = 0; 
//-----------------------------------------------------------------
// DS1302RTC¹¹Ôìº¯Êý
//-----------------------------------------------------------------
 DS1302RTC::DS1302RTC(byte _io, byte _sclk, byte _rst) { 
	io = _io;
	sclk = _sclk;
	rst = _rst;
	exists = true;
 }
time_t DS1302RTC::get() { 
	tmElements_t tm;
	read(tm);
	return makeTime(tm);
 }
//-----------------------------------------------------------------
// DS1302RTC Constructor
//-----------------------------------------------------------------
bool DS1302RTC::set(time_t t) { 
	tmElements_t tm;
	breakTime(t, tm);
	return write(tm);
 }
bool DS1302RTC::read(tmElements_t &tm) { 
	ds1302_struct rtc;
	clock_burst_read((byte *) &rtc);
	tm.Second = bcd2bin(rtc.Seconds10, rtc.Seconds);
	tm.Minute = bcd2bin(rtc.Minutes10, rtc.Minutes);
	if (rtc.h24.hour_12_24 == 0)
		tm.Hour = bcd2bin(rtc.h24.Hour10, rtc.h24.Hour);
	else
		tm.Hour = bcd2bin(rtc.h12.Hour10, rtc.h12.Hour) + rtc.h12.AM_PM?12:0;
	tm.Wday = rtc.Day;
	tm.Day = bcd2bin(rtc.Date10, rtc.Date);
	tm.Month = bcd2bin(rtc.Month10, rtc.Month);
	tm.Year = bcd2bin(rtc.Year10, rtc.Year) + (2000 - 1970);
	return true;
 }
bool DS1302RTC::write(tmElements_t &tm) { 
	// Start by clearing the Write Protect bit
   // Otherwise the clock data cannot be written
   // The whole register is written, 
   // but the WP-bit is the only bit in that register.
   write (DS1302_ENABLE, 0);
   // Disable Trickle Charger.
   write (DS1302_TRICKLE, 0x00); 
   ds1302_struct rtc;
   // Fill the structure with zeros to make 
   // any unused bits zero
   memset ((char *) &rtc, 0, sizeof(rtc));
   rtc.Seconds = bin2bcd_l(tm.Second);
   rtc.Seconds10 = bin2bcd_h(tm.Second);
   rtc.Minutes = bin2bcd_l(tm.Minute);
   rtc.Minutes10 = bin2bcd_h(tm.Minute);
   rtc.h24.hour_12_24 = 0;
   rtc.h24.Hour = bin2bcd_l(tm.Hour);
   rtc.h24.Hour10 = bin2bcd_h(tm.Hour);
   rtc.Day = bin2bcd_l(tm.Wday);
   rtc.Date = bin2bcd_l(tm.Day);
   rtc.Date10 = bin2bcd_h(tm.Day);
   rtc.Month = bin2bcd_l(tm.Month);
   rtc.Month10 = bin2bcd_h(tm.Month);
   rtc.Year = bin2bcd_l(tm.Year - (2000 - 1970));
   rtc.Year10 = bin2bcd_h(tm.Year - (2000 - 1970));
   clock_burst_write((byte *) &rtc);
   return true;
 }
void DS1302RTC::halt() { 
	write (DS1302_ENABLE, 0x00);
 } 
 // --------------------------------------------------------
// DS1302RTC::clock_burst_read
// This function reads 8 bytes clock data in burst mode
// from the DS1302.
// This function may be called as the first function,
// also the pinMode is set.
void DS1302RTC::clock_burst_read(byte *p) { 
	int i;
	start();
	// Instead of the address,
	// the CLOCK_BURST_READ command is issued
	// the I/O-line is released for the data
	togglewrite(DS1302_CLOCK_BURST_READ, true);
	for (i = 0; i < 8; i++)  *p++ = toggleread();
	stop();
 }
// --------------------------------------------------------
// DS1302RTC::clock_burst_write
//-----------------------------------------------------------------
void DS1302RTC::clock_burst_write(byte *p) { 
	int i;
	start();
	// Instead of the address,
	// the CLOCK_BURST_WRITE command is issued.
	// the I/O-line is not released
	togglewrite(DS1302_CLOCK_BURST_WRITE, false);
	for (i = 0; i < 8; i++)   { 
		// the I/O-line is not released
		togglewrite(*p++, false);
	}
	stop();
 }
// --------------------------------------------------------
// DS1302RTC::read
// This function reads a byte from the DS1302
// (clock or ram).
// The address could be like "0x80" or "0x81",
// the lowest bit is set anyway.
// This function may be called as the first function,
// also the pinMode is set.
//-----------------------------------------------------------------
byte DS1302RTC::read(int address) { 
	byte data;
	// set lowest bit (read bit) in address
	bitSet(address, DS1302_READBIT);
	start();
	// the I/O-line is released for the data
	togglewrite(address, true);
	data = toggleread();
	stop();
	return (data);
 }
// --------------------------------------------------------
// DS1302RTC::write
//
// This function writes a byte to the DS1302 (clock or ram).
//
// The address could be like "0x80" or "0x81",
// the lowest bit is cleared anyway.
//
// This function may be called as the first function,
// also the pinMode is set.
void DS1302RTC::write(int address, byte data) { 
	// clear lowest bit (read bit) in address
	bitClear(address, DS1302_READBIT);
	start();
	// don't release the I/O-line
	togglewrite(address, false);
	// don't release the I/O-line
	togglewrite(data, false);
	stop();
 }
// --------------------------------------------------------
// DS1302RTC::start
// A helper function to setup the start condition.
// An 'init' function is not used.
// But now the pinMode is set every time.
// That's not a big deal, and it's valid.
// At startup, the pins of the Arduino are high impedance.
// Since the DS1302 has pull-down resistors,
// the signals are low (inactive) until the DS1302 is used.
void DS1302RTC::start(void) { 
	digitalWrite(rst,  LOW); pinMode(rst, OUTPUT); // default, not enabled
	digitalWrite(sclk, LOW); pinMode(sclk, OUTPUT); // default, clock low
	pinMode(io, OUTPUT);
	digitalWrite(rst, HIGH);  // start the session
	delayMicroseconds(4);            // tCC = 4us
 }
void DS1302RTC::stop(void) { 
	// Set CE low
	digitalWrite(rst, LOW);
	delayMicroseconds(4);            // tCWH = 4us
}
// --------------------------------------------------------
// DS1302RTC::toggleread//
// A helper function for reading a byte with bit toggle//
// This function assumes that the SCLK is still high.
byte DS1302RTC::toggleread(void) { 
	byte i, data;
	data = 0;
	for (i = 0; i <= 7; i++) { 
		// Issue a clock pulse for the next databit.
		// If the 'togglewrite' function was used before
		// this function, the SCLK is already high.
		digitalWrite(sclk, HIGH);
		delayMicroseconds(1);
		// Clock down, data is ready after some time.
		digitalWrite(sclk, LOW);
		delayMicroseconds(1);         // tCL=1000ns, tCDD=800ns
		// read bit, and set it in place in 'data' variable
		bitWrite(data, i, digitalRead(io));
	}
	return (data);
 }
// --------------------------------------------------------
// DS1302RTC::togglewrite
//
// A helper function for writing a byte with bit toggle
//
// The 'release' parameter is for a read after this write.
// It will release the I/O-line and will keep the SCLK high.
void DS1302RTC::togglewrite(byte data, byte release) { 
	int i;
	for (i = 0; i <= 7; i++) {	
		// set a bit of the data on the I/O-line
		digitalWrite(io, bitRead(data, i));
		delayMicroseconds(1);      // tDC = 200ns
		// clock up, data is read by DS1302
		digitalWrite(sclk, HIGH);
		delayMicroseconds(1);      // tCH = 1000ns, tCDH = 800ns
		if (release && i == 7) { 
			// If this write is followed by a read,
			// the I/O-line should be released after
			// the last bit, before the clock line is made low.
			// This is according the datasheet.
			// I have seen other programs that don't release
			// the I/O-line at this moment,
			// and that could cause a shortcut spike
			// on the I/O-line.
			pinMode(io, INPUT);
			// For Arduino 1.0.3, removing the pull-up is no longer needed.
			// Setting the pin as 'INPUT' will already remove the pull-up.
			// digitalWrite (DS1302_IO, LOW); // remove any pull-up
		}
		else {	
			digitalWrite(sclk, LOW);
			delayMicroseconds(1);        // tCL=1000ns, tCDD=800ns
		}
	}
 }