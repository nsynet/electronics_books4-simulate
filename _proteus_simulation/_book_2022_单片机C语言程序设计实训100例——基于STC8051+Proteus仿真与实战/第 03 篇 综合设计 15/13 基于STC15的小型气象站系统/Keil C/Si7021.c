//-----------------------------------------------------------------
// 名称：Si7021温湿度传感器驱动程序
//-----------------------------------------------------------------
#include "Si7021.h"
extern void delay_ms(u8);
//-----------------------------------------------------------------
// 获取相对湿度
//-----------------------------------------------------------------
float getRH() {
	// Measure the relative humidity
	u16 RH_Code = makeMeasurment(HUMD_MEASURE_NOHOLD);
	float result = (125.0*RH_Code/65536)-6;
	return result;
}
//-----------------------------------------------------------------
// 读取温度
//-----------------------------------------------------------------
float readsi7021_Temp(){
	// Read temperature from previous RH measurement.
	u16 temp_Code = makeMeasurment(TEMP_PREV);
	float result = (175.72*temp_Code/65536)-46.85;
	return result;
}
//-----------------------------------------------------------------
// 测量温度
//-----------------------------------------------------------------
float getTemp() {
	// Measure temperature
	u16 temp_Code = makeMeasurment(TEMP_MEASURE_NOHOLD);
	float result = (175.72*temp_Code/65536)-46.85;
	return result;
}
//-----------------------------------------------------------------
// 读取华氏温度
//-----------------------------------------------------------------
float readsi7021_TempF() { 
	return((readsi7021_Temp() * 1.8) + 32.0); 
}
//-----------------------------------------------------------------
// 读取华氏温度
//-----------------------------------------------------------------
float getTempF() {
	return((getTemp() * 1.8) + 32.0);
}

//-----------------------------------------------------------------
// 加热器打开
//-----------------------------------------------------------------
void heaterOn() {
	// Turns on the ADDRESS heater
	u8 regVal = readReg();
	regVal |= (1<<HTRE);
	//turn on the heater
	writeReg(regVal);
}
//-----------------------------------------------------------------
// 加热器关闭
//-----------------------------------------------------------------
void heaterOff() {
	// Turns off the ADDRESS heater
	u8 regVal = readReg();
	regVal &= ~(1<<HTRE);
	writeReg(regVal);
}
//-----------------------------------------------------------------
// 改变精度
//-----------------------------------------------------------------
void changeResolution(u8 i){
	// Changes to resolution of ADDRESS measurements.
	// Set i to:
	//      RH         Temp
	// 0: 12 bit       14 bit (default)
	// 1:  8 bit       12 bit
	// 2: 10 bit       13 bit
	// 3: 11 bit       11 bit
	u8 regVal = readReg(); 
	regVal &= 0x00FE; 
	switch (i) {
		case 1:		regVal |= 0x0001;	break;
		case 2:		regVal |= 0x0080;	break;
		case 3:		regVal |= 0x0081;	break;
		default:	regVal |= 0x0000;	break;
	}
	writeReg(regVal);
}
//-----------------------------------------------------------------
// 复位
//-----------------------------------------------------------------
void reset_Si7201(){
	writeReg(SOFT_RESET);
}
//-----------------------------------------------------------------
// 检测ID
//-----------------------------------------------------------------
u8 checkID() {
	u8 ID_1;
	IIC_Start(); 
	IIC_WriteByte(ADDRESS); 	//Wire.beginTransmission(ADDRESS);
	IIC_WriteByte(0xFC);			//Wire.write(0xFC);
	IIC_WriteByte(0xC9); 			//Wire.write(0xC9);
	IIC_Start();							//Wire.endTransmission();
	IIC_WriteByte(ADDRESS); 	//Wire.requestFrom(ADDRESS,1);
	ID_1 = IIC_ReadByte(); 		//Wire.read();
	IIC_NAck(); IIC_Stop();
	return ID_1;
}
//-----------------------------------------------------------------
// 进行测量
//-----------------------------------------------------------------
u16 makeMeasurment(u8 command) {
	u16 msb,lsb,mesurment;
	// Take one ADDRESS measurement given by command.
	// It can be either temperature or relative humidity
	// TODO: implement checksum checking
	u16 nBytes = 3;
	// if we are only reading old temperature, read olny msb and lsb
	if (command == 0xE0) nBytes = 2;
	IIC_Start(); 
	IIC_WriteByte(ADDRESS);//Wire.beginTransmission(ADDRESS);
	IIC_WriteByte(command)  ;//Wire.write(command);
	IIC_Start();  //Wire.endTransmission();
	// When not using clock stretching (*_NOHOLD commands) delay here
	// is needed to wait for the measurement.
	// According to datasheet the max. conversion time is ~22ms
	delay_ms(30);
	//delay(100);	
	IIC_WriteByte(ADDRESS | 0x01) ;//Wire.requestFrom(ADDRESS,nBytes);
	//if(Wire.available() != nBytes) return 100;
	msb = IIC_ReadByte(); IIC_Ack();//Wire.read();
	lsb = IIC_ReadByte(); IIC_NAck();//Wire.read();
	IIC_Stop();
	lsb &= 0x00FC;
	mesurment = msb << 8 | lsb;
	return mesurment;
}
//-----------------------------------------------------------------
// 获取温湿度
//-----------------------------------------------------------------
void writeReg(u8 value) {
	IIC_Start(); 
	IIC_WriteByte(WRITE_USER_REG); 
	IIC_WriteByte(value); 
	IIC_Stop();	
	delay_ms(2);
}
//-----------------------------------------------------------------
// 获取温湿度
//-----------------------------------------------------------------
u8 readReg(){
	u8 d;
	// Read from user register on ADDRESS
	IIC_Start(); 
	IIC_WriteByte(READ_USER_REG); 
	IIC_Start(); 
	IIC_WriteByte(ADDRESS | 0x01); 
	d = IIC_ReadByte(); IIC_NAck(); IIC_Stop();
	return d;
}