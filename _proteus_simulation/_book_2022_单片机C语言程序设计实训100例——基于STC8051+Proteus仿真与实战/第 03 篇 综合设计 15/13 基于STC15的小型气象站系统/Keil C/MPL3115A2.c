//-----------------------------------------------------------------
// 名称：MPL3115A2气压计驱动程序
//-----------------------------------------------------------------
/*
 MPL3115A2 Barometric Pressure Sensor Library
 .readAltitude() Returns float with meters above sealevel. Ex: 1638.94
 .readAltitudeFt() Returns float with feet above sealevel. Ex: 5376.68
 .readPressure() Returns float with barometric pressure in Pa. Ex: 83351.25
 .readTemp() Returns float with current temperature in Celsius. Ex: 23.37
 .readTempF() Returns float with current temperature in Fahrenheit. Ex: 73.96
 .setModeBarometer() Puts the sensor into Pascal measurement mode.
 .setModeAltimeter() Puts the sensor into altimetery mode.
 .setModeStandy() Puts the sensor into Standby mode. Required when changing CTRL1 register.
 .setModeActive() Start taking measurements!
 .setOversampleRate(u8) Sets the # of samples from 1 to 128. See datasheet.
 .enableEventFlags() Sets the fundamental event flags. Required during setup.
 */

#include "MPL3115A2.h"
extern void delay_ms(u8);
//-----------------------------------------------------------------
// 读取海拨（单位：米），返回-1表示无可用新数据
//-----------------------------------------------------------------
float readAltitude() {
	u8 msb, csb, lsb;
	float tempcsb, altitude;
	int counter = 0;
	toggleOneShot(); //Toggle the OST bit causing the sensor to immediately take another reading
	//Wait for PDR bit, indicates we have new pressure data
	while( (IIC_Read(STATUS) & (1<<1)) == 0) {
		if(++counter > 600) return(-999); //Error out after max of 512ms for a read
		delay_ms(1);
	}
	// Read pressure registers
	IIC_Start(); 
	IIC_WriteByte(MPL3115A2_ADDRESS); 
	IIC_WriteByte(OUT_P_MSB);
	IIC_Start(); 
	delay_ms(30);
	IIC_WriteByte(MPL3115A2_ADDRESS|0x01);
	msb = IIC_ReadByte(); IIC_Ack();
	csb = IIC_ReadByte(); IIC_Ack();
	lsb = IIC_ReadByte(); IIC_NAck();
	IIC_Stop();
	// The least significant u8s l_altitude and l_temp are 4-bit,
	// fractional values, so you must cast the calulation in (float),
	// shift the value over 4 spots to the right and divide by 16 (since 
	// there are 16 values in 4-bits). 
	tempcsb = (int)(lsb>>4)/16.0;
	altitude = (float)( (msb << 8) | csb) + tempcsb;
	return altitude;
}
//-----------------------------------------------------------------
// 读取海拨高度（单位：英尺）
//-----------------------------------------------------------------
//Returns the number of feet above sea level
float readAltitudeFt() {
	return (readAltitude() * 3.28084);
}
//-----------------------------------------------------------------
// 读取当前气压（单位：Pa）
//-----------------------------------------------------------------
//Reads the current pressure in Pa
//Unit must be set in barometric pressure mode
//Returns -1 if no new data is available
float readPressure(){
	u8 msb, csb, lsb; long pressure_whole;
	float pressure_decimal,pressure;
	int counter = 0;
	//Check PDR bit, if it's not set then toggle OST
	//Toggle the OST bit causing the sensor to immediately take another reading
	if((IIC_Read(STATUS) & (1<<2)) == 0) toggleOneShot(); 
	//Wait for PDR bit, indicates we have new pressure data
	while((IIC_Read(STATUS) & (1<<2)) == 0) {
		if(++counter > 600) return(-999); //Error out after max of 512ms for a read
		delay_ms(1);
	}
	// Read pressure registers
	IIC_Start(); 
	IIC_WriteByte(MPL3115A2_ADDRESS); 
	IIC_WriteByte(OUT_P_MSB);
	IIC_Start();
	delay_ms(30);
	
	IIC_WriteByte(MPL3115A2_ADDRESS|0x01);
	msb = IIC_ReadByte(); IIC_Ack();
	csb = IIC_ReadByte(); IIC_Ack();
	lsb = IIC_ReadByte(); IIC_NAck();
	IIC_Stop();
	toggleOneShot(); //Toggle the OST bit causing the sensor to immediately take another reading 
	// Pressure comes back as a left shifted 20 bit number
	pressure_whole = ((long)msb<<16)|((long)csb<<8)|((long)lsb);
	pressure_whole >>= 6; //Pressure is an 18 bit number with 2 bits of decimal. Get rid of decimal portion.
	lsb &= 0x30; // B0011 0000; //Bits 5/4 represent the fractional component
	lsb >>= 4; //Get it right aligned
	pressure_decimal = (float)lsb/4.0; //Turn it into fraction
	pressure = (float)pressure_whole + pressure_decimal;
	return(pressure);
}
//-----------------------------------------------------------------
// 读取温度
//-----------------------------------------------------------------
float readMPL3115A2_Temp() {
	u8 msb, lsb;
	float templsb,temperature;
	u16 foo = 0;
	bit negSign = 0;
	int counter = 0;
	if((IIC_Read(STATUS) & (1<<1)) == 0) toggleOneShot(); //Toggle the OST bit causing the sensor to immediately take another reading
	//Wait for TDR bit, indicates we have new temp data
	while( (IIC_Read(STATUS) & (1<<1)) == 0)
	{
		if(++counter > 600) return(-999); //Error out after max of 512ms for a read
		delay_ms(1);
	}
	IIC_Start(); 
	IIC_WriteByte(MPL3115A2_ADDRESS);
	IIC_WriteByte(OUT_T_MSB); 
	IIC_Start(); 
	delay_ms(30);
	IIC_WriteByte(MPL3115A2_ADDRESS|0x01);
	msb = IIC_ReadByte(); IIC_Ack();
	lsb = IIC_ReadByte(); IIC_NAck();
	IIC_Stop();
	
	toggleOneShot(); //Toggle the OST bit causing the sensor to immediately take another reading
	//Negative temperature fix by D.D.G.
	foo = 0;
	negSign = 0;
	//Check for 2s compliment
	if(msb > 0x7F) {
		foo = ~((msb << 8) + lsb) + 1;  //2’s complement
		msb = foo >> 8;
		lsb = foo & 0x00F0; 
		negSign = 1;
	}
	// The least significant u8s l_altitude and l_temp are 4-bit,
	// fractional values, so you must cast the calulation in (float),
	// shift the value over 4 spots to the right and divide by 16 (since 
	// there are 16 values in 4-bits). 
	templsb = ((int)(lsb>>4))/16.0; //temp, fraction of a degree
	temperature = (float)(msb + templsb);
	if (negSign) temperature = 0 - temperature;	
	return(temperature);
}
//-----------------------------------------------------------------
// 获取华氏温度
//-----------------------------------------------------------------
//Give me temperature in fahrenheit!
float readMPL3115A2_TempF(){
	return((readMPL3115A2_Temp() * 9.0)/ 5.0 + 32.0); // Convert celsius to fahrenheit
}
//-----------------------------------------------------------------
// 设置模式为气压计
//-----------------------------------------------------------------
//Sets the mode to Barometer CTRL_REG1, ALT bit
void setModeBarometer() {
	u8 tempSetting = IIC_Read(CTRL_REG1); //Read current settings
	tempSetting &= ~(1<<7); //Clear ALT bit
	IIC_Write(CTRL_REG1, tempSetting);
}
//-----------------------------------------------------------------
// 设置模式为高度仪
//-----------------------------------------------------------------
//Sets the mode to Altimeter
//CTRL_REG1, ALT bit
void setModeAltimeter(){
	u8 tempSetting = IIC_Read(CTRL_REG1); //Read current settings
	tempSetting |= (1<<7); //Set ALT bit
	IIC_Write(CTRL_REG1, tempSetting);
}
//-----------------------------------------------------------------
// 将传感器设置为待机模式
//-----------------------------------------------------------------
//Puts the sensor in standby mode
//This is needed so that we can modify the major control registers
void setModeStandby(){
	u8 tempSetting = IIC_Read(CTRL_REG1); //Read current settings
	tempSetting &= ~(1<<0); //Clear SBYB bit for Standby mode
	IIC_Write(CTRL_REG1, tempSetting);
}
//-----------------------------------------------------------------
// 将传感器设置为活动模式
//-----------------------------------------------------------------
//Puts the sensor in active mode
//This is needed so that we can modify the major control registers
void setModeActive()  {
	u8 tempSetting = IIC_Read(CTRL_REG1); //Read current settings
	tempSetting |= (1<<0); //Set SBYB bit for Active mode
	IIC_Write(CTRL_REG1, tempSetting);
}
//-----------------------------------------------------------------
//Call with a rate from 0 to 7. See page 33 for table of ratios.
//Sets the over sample rate. Datasheet calls for 128 but you can set it 
//from 1 to 128 samples. The higher the oversample rate the greater
//the time between data samples.
//-----------------------------------------------------------------
void setOversampleRate(u8 sampleRate) {
	u8 tempSetting;
	if(sampleRate > 7) sampleRate = 7; //OS cannot be larger than 0b.0111
	sampleRate <<= 3; //Align it for the CTRL_REG1 register
	tempSetting = IIC_Read(CTRL_REG1); //Read current settings
	tempSetting &= 0xC7;  //B11000111; //Clear out old OS bits
	tempSetting |= sampleRate; //Mask in new OS bits
	IIC_Write(CTRL_REG1, tempSetting);
}
//-----------------------------------------------------------------
// 使能事件标志
//-----------------------------------------------------------------
//Enables the pressure and temp measurement event flags so that we can
//test against them. This is recommended in datasheet during setup.
void enableEventFlags() {
	IIC_Write(PT_DATA_CFG, 0x07); // Enable all three pressure and temp event flags 
}
//-----------------------------------------------------------------
// 触发1次快照
//-----------------------------------------------------------------
//Clears then sets the OST bit which causes the sensor to immediately take another reading
//Needed to sample faster than 1Hz
void toggleOneShot() {
	u8 tempSetting = IIC_Read(CTRL_REG1); //Read current settings
	tempSetting &= ~(1<<1); //Clear OST bit
	IIC_Write(CTRL_REG1, tempSetting);
	tempSetting = IIC_Read(CTRL_REG1); //Read current settings to be safe
	tempSetting |= (1<<1); //Set OST bit
	IIC_Write(CTRL_REG1, tempSetting);
}
//-----------------------------------------------------------------
// 读IIC接口
//-----------------------------------------------------------------
// These are the two I2C functions in this sketch.
u8 IIC_Read(u8 regAddr){
	u8 dat;
	IIC_Start(); 
	IIC_WriteByte(MPL3115A2_ADDRESS); 
	IIC_WriteByte(regAddr); 
	IIC_Start();
	delay_ms(30);
	IIC_WriteByte(MPL3115A2_ADDRESS | 0x01);
	dat = IIC_ReadByte();
	IIC_NAck(); IIC_Stop();
	return dat ;
}
//-----------------------------------------------------------------
// 写IIC接口
//-----------------------------------------------------------------
void IIC_Write(u8 regAddr, u8 value) {
	IIC_Start(); 
	IIC_WriteByte(MPL3115A2_ADDRESS);
	IIC_WriteByte(regAddr);
	IIC_WriteByte(value);
	IIC_Stop();
}