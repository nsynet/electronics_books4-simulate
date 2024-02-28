/*
 * DS1302RTC.h - library for DS1302 RTC
 * This library is intended to be uses with Arduino Time.h library functions
 */
#ifndef DS1302RTC_h
#define DS1302RTC_h
#include "TimeLib.h"
class DS1302RTC {
   public:
      DS1302RTC(byte io, byte sclk, byte rst);
      static time_t get();
      static bool set(time_t t);
      static bool read(tmElements_t &tm);
      static bool write(tmElements_t &tm);   
      static void halt();
      static bool chipPresent() { return exists; }
   private:
      static void clock_burst_read(byte *p);
      static void clock_burst_write(byte *p);
      static byte read(int address);
      static void write(int address, byte data);
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
