//-----------------------------------------------------------------
// 名称：Si702温湿度传感器驱动程序头文件
//-----------------------------------------------------------------
#ifndef ___Si702L___
#define ___Si702L___

#include "STC15xxx.h"
#include "I2C.h"
#define u8  unsigned char
#define u16 unsigned int

#define ADDRESS								0x80

#define TEMP_MEASURE_HOLD			0xE3
#define HUMD_MEASURE_HOLD			0xE5
#define TEMP_MEASURE_NOHOLD		0xF3
#define HUMD_MEASURE_NOHOLD		0xF5
#define TEMP_PREV							0xE0
#define WRITE_USER_REG				0xE6
#define READ_USER_REG					0xE7
#define SOFT_RESET						0xFE
#define HTRE									0x02
#define CRC_POLY							0x988000 // Shifted Polynomial for CRC check
// Error codes
#define I2C_TIMEOUT 	998
#define BAD_CRC		999

float getRH();
float getTemp();
float getTempF();
float readsi7021_Temp();
float readsi7021_TempF();
void  heaterOn();
void  heaterOff();
void  changeResolution(u8 i);
void  writeReg(u8 value);
u16   makeMeasurment(u8 command);
u8    checkID();
u8    readReg();
#endif