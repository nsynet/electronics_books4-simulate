//-----------------------------------------------------------------
// 名称：MPL3115A2气压计驱动程序头文件
//-----------------------------------------------------------------
/* 
 MPL3115A2 Barometric Pressure Sensor Library
 By: Nathan Seidle
 SparkFun Electronics
 Date: September 24th, 2013
 License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).
 Get pressure, altitude and temperature from the MPL3115A2 sensor.
 */
#ifndef ___MPL3115A2___
#define ___MPL3115A2___

#include "STC15xxx.h"
#include "I2C.h"
#define u8  unsigned char
#define u16 unsigned int

#define MPL3115A2_ADDRESS 0xC0

#define STATUS     0x00
#define OUT_P_MSB  0x01
#define OUT_P_CSB  0x02
#define OUT_P_LSB  0x03
#define OUT_T_MSB  0x04
#define OUT_T_LSB  0x05
#define DR_STATUS  0x06
#define OUT_P_DELTA_MSB  0x07
#define OUT_P_DELTA_CSB  0x08
#define OUT_P_DELTA_LSB  0x09
#define OUT_T_DELTA_MSB  0x0A
#define OUT_T_DELTA_LSB  0x0B
#define WHO_AM_I   0x0C
#define F_STATUS   0x0D
#define F_DATA     0x0E
#define F_SETUP    0x0F
#define TIME_DLY   0x10
#define SYSMOD     0x11
#define INT_SOURCE 0x12
#define PT_DATA_CFG 0x13
#define BAR_IN_MSB 0x14
#define BAR_IN_LSB 0x15
#define P_TGT_MSB  0x16
#define P_TGT_LSB  0x17
#define T_TGT      0x18
#define P_WND_MSB  0x19
#define P_WND_LSB  0x1A
#define T_WND      0x1B
#define P_MIN_MSB  0x1C
#define P_MIN_CSB  0x1D
#define P_MIN_LSB  0x1E
#define T_MIN_MSB  0x1F
#define T_MIN_LSB  0x20
#define P_MAX_MSB  0x21
#define P_MAX_CSB  0x22
#define P_MAX_LSB  0x23
#define T_MAX_MSB  0x24
#define T_MAX_LSB  0x25
#define CTRL_REG1  0x26
#define CTRL_REG2  0x27
#define CTRL_REG3  0x28
#define CTRL_REG4  0x29
#define CTRL_REG5  0x2A
#define OFF_P      0x2B
#define OFF_T      0x2C
#define OFF_H      0x2D

float readAltitude(); // Returns float with meters above sealevel. Ex: 1638.94
float readAltitudeFt(); // Returns float with feet above sealevel. Ex: 5376.68
float readPressure(); // Returns float with barometric pressure in Pa. Ex: 83351.25
float readMPL3115A2_Temp(); // Returns float with current temperature in Celsius. Ex: 23.37
float readMPL3115A2_TempF(); // Returns float with current temperature in Fahrenheit. Ex: 73.96
void setModeBarometer(); // Puts the sensor into Pascal measurement mode.
void setModeAltimeter(); // Puts the sensor into altimetery mode.
void setModeStandby(); // Puts the sensor into Standby mode. Required when changing CTRL1 register.
void setModeActive(); // Start taking measurements!
void setOversampleRate(u8); // Sets the # of samples from 1 to 128. See datasheet.
void enableEventFlags(); // Sets the fundamental event flags. Required during setup.

void toggleOneShot();
u8 IIC_Read(u8 regAddr);
void IIC_Write(u8 regAddr, u8 value);

#endif