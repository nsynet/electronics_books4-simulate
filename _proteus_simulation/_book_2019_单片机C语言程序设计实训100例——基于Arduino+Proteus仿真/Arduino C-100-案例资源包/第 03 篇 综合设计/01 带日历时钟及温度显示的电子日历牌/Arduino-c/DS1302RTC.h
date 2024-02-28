/*
 * DS1302RTC.h - library for DS1302 RTC
 * This library is intended to be uses with Arduino Time.h library functions
 */
#ifndef DS1302RTC_h
#define DS1302RTC_h
#include "TimeLib.h"
// Macros to convert the bcd values of the registers to normal
// integer variables.
// The code uses seperate variables for the high byte and the low byte
// of the bcd, so these macros handle both bytes seperately.
#define bcd2bin(h,l)    (((h)*10) + (l))
#define bin2bcd_h(x)	((x)/10)
#define bin2bcd_l(x)    ((x)%10)
// Register names.
// Since the highest bit is always '1',
// the registers start at 0x80
// If the register is read, the lowest bit should be '1'.
#define DS1302_SECONDS           0x80
#define DS1302_MINUTES           0x82
#define DS1302_HOURS             0x84
#define DS1302_DATE              0x86
#define DS1302_MONTH             0x88
#define DS1302_DAY               0x8A
#define DS1302_YEAR              0x8C
#define DS1302_ENABLE            0x8E
#define DS1302_TRICKLE           0x90
#define DS1302_CLOCK_BURST       0xBE
#define DS1302_CLOCK_BURST_WRITE 0xBE
#define DS1302_CLOCK_BURST_READ  0xBF
#define DS1302_RAMSTART          0xC0
#define DS1302_RAMEND            0xFC
#define DS1302_RAM_BURST         0xFE
#define DS1302_RAM_BURST_WRITE   0xFE
#define DS1302_RAM_BURST_READ    0xFF
// Defines for the bits, to be able to change
// between bit number and binary definition.
// By using the bit number, using the DS1302
// is like programming an AVR microcontroller.
// But instead of using "(1<<X)", or "_BV(X)",
// the Arduino "bit(X)" is used.
#define DS1302_D0 0
#define DS1302_D1 1
#define DS1302_D2 2
#define DS1302_D3 3
#define DS1302_D4 4
#define DS1302_D5 5
#define DS1302_D6 6
#define DS1302_D7 7
// Bit for reading (bit in address)
#define DS1302_READBIT DS1302_D0 // READBIT=1: read instruction
// Bit for clock (0) or ram (1) area,
// called R/C-bit (bit in address)
#define DS1302_RC DS1302_D6
// Seconds Register
#define DS1302_CH DS1302_D7   // 1 = Clock Halt, 0 = start
// Hour Register
#define DS1302_AM_PM DS1302_D5 // 0 = AM, 1 = PM
#define DS1302_12_24 DS1302_D7 // 0 = 24 hour, 1 = 12 hour
// Enable Register
#define DS1302_WP DS1302_D7   // 1 = Write Protect, 0 = enabled
// Trickle Register
#define DS1302_ROUT0 DS1302_D0
#define DS1302_ROUT1 DS1302_D1
#define DS1302_DS0   DS1302_D2
#define DS1302_DS1   DS1302_D2
#define DS1302_TCS0  DS1302_D4
#define DS1302_TCS1  DS1302_D5
#define DS1302_TCS2  DS1302_D6
#define DS1302_TCS3  DS1302_D7
// Structure for the first 8 registers.
// These 8 bytes can be read at once with
// the 'clock burst' command.
// Note that this structure contains an anonymous union.
// It might cause a problem on other compilers.
typedef struct  {
	byte Seconds: 4;     //秒的个数：0～9
	byte Seconds10: 3;   //秒的10位：0～5
	byte CH: 1;          //时钟停止位
	byte Minutes: 4;
	byte Minutes10: 3;
	byte reserved1: 1;
	union
	{	struct
		{	byte Hour: 4;
			byte Hour10: 2;
			byte reserved2: 1;
			byte hour_12_24: 1; //1:0->12:24
		} h24;
		struct
		{	byte Hour: 4;
			byte Hour10: 1;
			byte AM_PM: 1;     //0:AM, 1:PM
			byte reserved2: 1;
			byte hour_12_24: 1; //1:0->12:24
		} h12;
	};
	byte Date: 4;          //月
	byte Date10: 2;
	byte reserved3: 2;
	byte Month: 4;         //月
	byte Month10: 1;
	byte reserved4: 3;
	byte Day: 3;           //周
	byte reserved5: 5;
	byte Year: 4;          //年
	byte Year10: 4;
	byte reserved6: 7;
	byte WP: 1;            //写保护位
} ds1302_struct;

class DS1302RTC {
   public:
      DS1302RTC(byte io, byte sclk, byte rst);
      static time_t get();
      static bool set(time_t t);
      static bool read(tmElements_t &tm);
      static bool write(tmElements_t &tm);   
      static void halt();
      static bool chipPresent() { return exists; }
		static byte read(int address);
      static void write(int address, byte data);
   private:
      static void clock_burst_read(byte *p);
      static void clock_burst_write(byte *p);
      //static byte read(int address);
      //static void write(int address, byte data);
      static void start(void);
      static void stop(void);
      static byte toggleread(void);
      static void togglewrite( byte data, byte release);
   private:
      static bool exists;      
      static byte io;
      static byte sclk;
      static byte rst;
 };
#endif
