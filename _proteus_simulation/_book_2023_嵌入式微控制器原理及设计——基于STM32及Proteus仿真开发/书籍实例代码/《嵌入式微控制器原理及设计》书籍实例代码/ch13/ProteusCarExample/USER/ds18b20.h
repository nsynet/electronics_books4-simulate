#ifndef __DS18B20_H__
#define __DS18B20_H__ 
#include "stm32f10x.h"
#define DS18B20_GPIO_NUM				 GPIO_Pin_11
#define DS18B20_GPIO_X					GPIOA
#define RCC_APB2Periph_DS18B20_GPIO_X	RCC_APB2Periph_GPIOA
 
#define DS18B20_DQ_OUT_Low			GPIO_ResetBits(DS18B20_GPIO_X,DS18B20_GPIO_NUM) 
#define DS18B20_DQ_OUT_High			GPIO_SetBits(DS18B20_GPIO_X,DS18B20_GPIO_NUM) 
#define DS18B20_DQ_IN				GPIO_ReadInputDataBit(DS18B20_GPIO_X,DS18B20_GPIO_NUM) 
 
#define MaxSensorNum 8
//u8 DS18B20_Init(void);
u8 DS18B20_Read_Byte(void);
u8 DS18B20_Read_Bit(void);
u8 DS18B20_Answer_Check(void);
void  DS18B20_GPIO_Config(void);
void  DS18B20_Mode_IPU(void);
void  DS18B20_Mode_Out(void);
void  DS18B20_Rst(void);
void  DS18B20_Search_Rom(void);
void  DS18B20_Write_Byte(u8 dat);
float DS18B20_Get_Temp(u8 i);


 
#endif /*DS18B20_H_*/
















