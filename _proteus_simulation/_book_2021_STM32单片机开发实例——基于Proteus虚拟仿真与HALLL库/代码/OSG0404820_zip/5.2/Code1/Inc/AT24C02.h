/*
 * AT24C02.h
 *
 *  Created on: 2019年10月29日
 *      Author: Administrator
 */

#ifndef AT24C02_H_
#define AT24C02_H_
#define AT24C02_ADDR 0xa0
//写入1个字节
void AT24C02_Write(uint8_t DatAddr, uint8_t Dat)
{
	I2C_Start();
	I2C_WtByte(AT24C02_ADDR + 0);
	I2C_Ack();
	I2C_WtByte(DatAddr);
	I2C_Ack();
	I2C_WtByte(Dat);
	I2C_Ack();
	I2C_Stop();
}

//读取1个字节
uint8_t AT24C02_Read(uint8_t DatAddr)
{
    uint8_t Dat;
    I2C_Start();
    I2C_WtByte(AT24C02_ADDR + 0);
    I2C_Ack();
    I2C_WtByte(DatAddr);
    I2C_Ack();
    I2C_Start();
    I2C_WtByte(AT24C02_ADDR + 1);
    I2C_Ack();
    Dat = I2C_RdByte();
    I2C_Stop();
    return Dat;
}


#endif /* AT24C02_H_ */
